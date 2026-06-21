/********************************************************************************
** Form generated from reading UI file 'light_editor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIGHT_EDITOR_H
#define UI_LIGHT_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "file_select_widget.h"
#include "light_widget.h"
#include "my_check_box.h"
#include "my_color_button.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"

QT_BEGIN_NAMESPACE

class Ui_cLightEditor
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout_2;
    MyLineEdit *logedit_intensity;
    MyColorButton *colorButton_color;
    QLabel *label_11;
    QLabel *label_14;
    MyLineEdit *logedit_size;
    MyLineEdit *logedit_visibility;
    QLabel *label_13;
    MyComboBox *comboBox_type;
    QLabel *label_15;
    QLabel *label_2;
    QLabel *label_12;
    MyComboBox *comboBox_decayFunction;
    MyLineEdit *logedit_contour_sharpness;
    QLabel *label_16;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    MyLineEdit *vect3_position_z;
    MyLineEdit *vect3_position_y;
    MyLineEdit *vect3_position_x;
    QLabel *label_21;
    QLabel *label;
    QLabel *label_22;
    QLabel *label_23;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout_3;
    MyDoubleSpinBox *spinboxd3_rotation_z;
    MyCheckBox *checkBox_use_target_point;
    MyDoubleSpinBox *spinboxd3_rotation_y;
    QLabel *label_target_y;
    QLabel *label_roll;
    QLabel *label_vertical;
    QLabel *label_horizontal;
    MyDoubleSpinBox *spinboxd3_rotation_x;
    QLabel *label_angle;
    QLabel *label_target_x;
    QLabel *label_target_z;
    QLabel *label_target;
    MyLineEdit *vect3_target_x;
    MyLineEdit *vect3_target_y;
    MyLineEdit *vect3_target_z;
    cLightWidget *widget_angle_preview;
    MyCheckBox *checkBox_relative_position;
    QGroupBox *groupBox_orbit;
    QGridLayout *gridLayout_orbit;
    QLabel *label_orbit_dist;
    MyDoubleSpinBox *spinboxd_orbit_distance;
    QLabel *label_orbit_yaw;
    MyDoubleSpinBox *spinboxd_orbit_yaw;
    QLabel *label_orbit_pitch;
    MyDoubleSpinBox *spinboxd_orbit_pitch;
    QPushButton *pushButton_applyOrbit;
    QGroupBox *groupBox_autoIntensity;
    QGridLayout *gridLayout_autoIntensity;
    MyCheckBox *checkBox_auto_intensity;
    QLabel *label_auto_intensity_factor;
    MyDoubleSpinBox *spinboxd_auto_intensity_factor;
    QPushButton *pushButton_applyAutoIntensity;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_7;
    MyCheckBox *checkBox_cast_shadows;
    MyCheckBox *checkBox_penetrating;
    QLabel *label_30;
    MyDoubleSpinBox *spinbox_soft_shadow_cone;
    MyGroupBox *groupCheck_volumetric;
    QGridLayout *gridLayout_4;
    MyLineEdit *logedit_volumetric_visibility;
    QLabel *label_4;
    QGroupBox *groupBox_cone_options;
    QGridLayout *gridLayout_6;
    MyLineEdit *logedit_cone_angle;
    QLabel *label_62;
    QLabel *label_64;
    MyLineEdit *logedit_cone_soft_angle;
    QGroupBox *groupBox_projection_options;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_5;
    FileSelectWidget *text_file_texture;
    QLabel *label_61;
    FileSelectWidget *text_file_texture_alpha;
    QLabel *label_alpha_texture;
    QGridLayout *gridLayout_8;
    MyLineEdit *logedit_projection_vertical_angle;
    MyLineEdit *logedit_projection_horizonal_angle;
    QLabel *label_63;
    QLabel *label_65;
    QLabel *label_repeat_mode;
    MyComboBox *comboBox_projection_repeat_mode;
    QLabel *label_soft_edge;
    MyLineEdit *logedit_projection_soft_edge;
    QLabel *label_texture_offset_x;
    MyLineEdit *logedit_projection_texture_offset_x;
    QLabel *label_texture_offset_y;
    MyLineEdit *logedit_projection_texture_offset_y;
    QLabel *label_texture_offset_z;
    MyLineEdit *logedit_projection_texture_offset_z;
    QLabel *label_texture_scale_x;
    MyLineEdit *logedit_projection_texture_scale_x;
    QLabel *label_texture_scale_y;
    MyLineEdit *logedit_projection_texture_scale_y;
    QLabel *label_texture_scale_z;
    MyLineEdit *logedit_projection_texture_scale_z;
    QLabel *label_texture_rotation_x;
    MyLineEdit *logedit_projection_texture_rotation_x;
    QLabel *label_texture_rotation_y;
    MyLineEdit *logedit_projection_texture_rotation_y;
    QLabel *label_texture_rotation_z;
    MyLineEdit *logedit_projection_texture_rotation_z;
    MyCheckBox *checkBox_projection_use_as_mask;
    MyCheckBox *checkBox_projection_use_alpha_as_mask;
    MyCheckBox *checkBox_projection_use_texture_alpha_as_mask;
    MyCheckBox *checkBox_projection_invert_alpha_mask;
    QLabel *label_projection_intensity;
    MyLineEdit *logedit_projection_intensity;
    QLabel *label_projection_blend_mode;
    MyComboBox *comboBox_projection_blend_mode;
    QGridLayout *gridLayout_alpha;
    QLabel *label_alpha_offset_x;
    MyLineEdit *logedit_alpha_texture_offset_x;
    QLabel *label_alpha_offset_y;
    MyLineEdit *logedit_alpha_texture_offset_y;
    QLabel *label_alpha_scale_x;
    MyLineEdit *logedit_alpha_texture_scale_x;
    QLabel *label_alpha_scale_y;
    MyLineEdit *logedit_alpha_texture_scale_y;
    QLabel *label_alpha_rotation_z;
    MyLineEdit *logedit_alpha_texture_rotation_z;
    QLabel *label_alpha_repeat_mode;
    MyComboBox *comboBox_alpha_texture_repeat_mode;
    QLabel *label_alpha_soft_edge;
    MyLineEdit *logedit_alpha_texture_soft_edge;
    QGroupBox *groupBox_beam_options;
    QVBoxLayout *verticalLayout_beam;
    QGridLayout *gridLayout_beam;
    QLabel *label_beam_radius;
    MyLineEdit *logedit_beam_radius;
    QLabel *label_beam_soft_edge;
    MyLineEdit *logedit_beam_soft_edge;
    QLabel *label_beam_fade_in;
    MyLineEdit *logedit_beam_fade_in;
    QLabel *label_beam_fade_out;
    MyLineEdit *logedit_beam_fade_out;
    QGroupBox *groupBox_spherical_texture;
    QVBoxLayout *verticalLayout_spherical;
    QGridLayout *gridLayout_spherical;
    QLabel *label_spherical_texture;
    FileSelectWidget *text_file_texture_spherical;
    QLabel *label_spherical_intensity;
    MyLineEdit *logedit_spherical_texture_intensity;

    void setupUi(QWidget *cLightEditor)
    {
        if (cLightEditor->objectName().isEmpty())
            cLightEditor->setObjectName(QString::fromUtf8("cLightEditor"));
        cLightEditor->setEnabled(true);
        cLightEditor->resize(557, 1152);
        verticalLayout = new QVBoxLayout(cLightEditor);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        groupBox = new QGroupBox(cLightEditor);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        logedit_intensity = new MyLineEdit(groupBox);
        logedit_intensity->setObjectName(QString::fromUtf8("logedit_intensity"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(logedit_intensity->sizePolicy().hasHeightForWidth());
        logedit_intensity->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(logedit_intensity, 2, 1, 1, 1);

        colorButton_color = new MyColorButton(groupBox);
        colorButton_color->setObjectName(QString::fromUtf8("colorButton_color"));

        gridLayout_2->addWidget(colorButton_color, 1, 1, 1, 1);

        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        gridLayout_2->addWidget(label_11, 2, 0, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QString::fromUtf8("label_14"));

        gridLayout_2->addWidget(label_14, 4, 0, 1, 1);

        logedit_size = new MyLineEdit(groupBox);
        logedit_size->setObjectName(QString::fromUtf8("logedit_size"));
        sizePolicy.setHeightForWidth(logedit_size->sizePolicy().hasHeightForWidth());
        logedit_size->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(logedit_size, 4, 1, 1, 1);

        logedit_visibility = new MyLineEdit(groupBox);
        logedit_visibility->setObjectName(QString::fromUtf8("logedit_visibility"));
        sizePolicy.setHeightForWidth(logedit_visibility->sizePolicy().hasHeightForWidth());
        logedit_visibility->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(logedit_visibility, 3, 1, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QString::fromUtf8("label_13"));

        gridLayout_2->addWidget(label_13, 3, 0, 1, 1);

        comboBox_type = new MyComboBox(groupBox);
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->addItem(QString());
        comboBox_type->setObjectName(QString::fromUtf8("comboBox_type"));

        gridLayout_2->addWidget(comboBox_type, 0, 1, 1, 1);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QString::fromUtf8("label_15"));

        gridLayout_2->addWidget(label_15, 6, 0, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        gridLayout_2->addWidget(label_12, 1, 0, 1, 1);

        comboBox_decayFunction = new MyComboBox(groupBox);
        comboBox_decayFunction->addItem(QString());
        comboBox_decayFunction->addItem(QString());
        comboBox_decayFunction->addItem(QString());
        comboBox_decayFunction->setObjectName(QString::fromUtf8("comboBox_decayFunction"));

        gridLayout_2->addWidget(comboBox_decayFunction, 6, 1, 1, 1);

        logedit_contour_sharpness = new MyLineEdit(groupBox);
        logedit_contour_sharpness->setObjectName(QString::fromUtf8("logedit_contour_sharpness"));
        sizePolicy.setHeightForWidth(logedit_contour_sharpness->sizePolicy().hasHeightForWidth());
        logedit_contour_sharpness->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(logedit_contour_sharpness, 5, 1, 1, 1);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));

        gridLayout_2->addWidget(label_16, 5, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout_2);


        verticalLayout->addWidget(groupBox);

        groupBox_3 = new QGroupBox(cLightEditor);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        vect3_position_z = new MyLineEdit(groupBox_3);
        vect3_position_z->setObjectName(QString::fromUtf8("vect3_position_z"));
        sizePolicy.setHeightForWidth(vect3_position_z->sizePolicy().hasHeightForWidth());
        vect3_position_z->setSizePolicy(sizePolicy);

        gridLayout->addWidget(vect3_position_z, 2, 2, 1, 1);

        vect3_position_y = new MyLineEdit(groupBox_3);
        vect3_position_y->setObjectName(QString::fromUtf8("vect3_position_y"));
        sizePolicy.setHeightForWidth(vect3_position_y->sizePolicy().hasHeightForWidth());
        vect3_position_y->setSizePolicy(sizePolicy);

        gridLayout->addWidget(vect3_position_y, 1, 2, 1, 1);

        vect3_position_x = new MyLineEdit(groupBox_3);
        vect3_position_x->setObjectName(QString::fromUtf8("vect3_position_x"));
        sizePolicy.setHeightForWidth(vect3_position_x->sizePolicy().hasHeightForWidth());
        vect3_position_x->setSizePolicy(sizePolicy);

        gridLayout->addWidget(vect3_position_x, 0, 2, 1, 1);

        label_21 = new QLabel(groupBox_3);
        label_21->setObjectName(QString::fromUtf8("label_21"));

        gridLayout->addWidget(label_21, 0, 1, 1, 1);

        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_22 = new QLabel(groupBox_3);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        gridLayout->addWidget(label_22, 1, 1, 1, 1);

        label_23 = new QLabel(groupBox_3);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        gridLayout->addWidget(label_23, 2, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        spinboxd3_rotation_z = new MyDoubleSpinBox(groupBox_3);
        spinboxd3_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_rotation_z"));
        sizePolicy.setHeightForWidth(spinboxd3_rotation_z->sizePolicy().hasHeightForWidth());
        spinboxd3_rotation_z->setSizePolicy(sizePolicy);
        spinboxd3_rotation_z->setDecimals(2);
        spinboxd3_rotation_z->setMinimum(-36000.000000000000000);
        spinboxd3_rotation_z->setMaximum(36000.000000000000000);
        spinboxd3_rotation_z->setSingleStep(0.100000000000000);

        gridLayout_3->addWidget(spinboxd3_rotation_z, 3, 2, 1, 1);

        checkBox_use_target_point = new MyCheckBox(groupBox_3);
        checkBox_use_target_point->setObjectName(QString::fromUtf8("checkBox_use_target_point"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBox_use_target_point->sizePolicy().hasHeightForWidth());
        checkBox_use_target_point->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(checkBox_use_target_point, 0, 0, 1, 3);

        spinboxd3_rotation_y = new MyDoubleSpinBox(groupBox_3);
        spinboxd3_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_rotation_y"));
        sizePolicy1.setHeightForWidth(spinboxd3_rotation_y->sizePolicy().hasHeightForWidth());
        spinboxd3_rotation_y->setSizePolicy(sizePolicy1);
        spinboxd3_rotation_y->setDecimals(2);
        spinboxd3_rotation_y->setMinimum(-36000.000000000000000);
        spinboxd3_rotation_y->setMaximum(36000.000000000000000);
        spinboxd3_rotation_y->setSingleStep(0.100000000000000);

        gridLayout_3->addWidget(spinboxd3_rotation_y, 2, 2, 1, 1);

        label_target_y = new QLabel(groupBox_3);
        label_target_y->setObjectName(QString::fromUtf8("label_target_y"));

        gridLayout_3->addWidget(label_target_y, 5, 1, 1, 1);

        label_roll = new QLabel(groupBox_3);
        label_roll->setObjectName(QString::fromUtf8("label_roll"));

        gridLayout_3->addWidget(label_roll, 3, 1, 1, 1);

        label_vertical = new QLabel(groupBox_3);
        label_vertical->setObjectName(QString::fromUtf8("label_vertical"));

        gridLayout_3->addWidget(label_vertical, 2, 1, 1, 1);

        label_horizontal = new QLabel(groupBox_3);
        label_horizontal->setObjectName(QString::fromUtf8("label_horizontal"));

        gridLayout_3->addWidget(label_horizontal, 1, 1, 1, 1);

        spinboxd3_rotation_x = new MyDoubleSpinBox(groupBox_3);
        spinboxd3_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_rotation_x"));
        sizePolicy1.setHeightForWidth(spinboxd3_rotation_x->sizePolicy().hasHeightForWidth());
        spinboxd3_rotation_x->setSizePolicy(sizePolicy1);
        spinboxd3_rotation_x->setDecimals(2);
        spinboxd3_rotation_x->setMinimum(-36000.000000000000000);
        spinboxd3_rotation_x->setMaximum(36000.000000000000000);
        spinboxd3_rotation_x->setSingleStep(0.100000000000000);

        gridLayout_3->addWidget(spinboxd3_rotation_x, 1, 2, 1, 1);

        label_angle = new QLabel(groupBox_3);
        label_angle->setObjectName(QString::fromUtf8("label_angle"));

        gridLayout_3->addWidget(label_angle, 2, 0, 1, 1);

        label_target_x = new QLabel(groupBox_3);
        label_target_x->setObjectName(QString::fromUtf8("label_target_x"));

        gridLayout_3->addWidget(label_target_x, 4, 1, 1, 1);

        label_target_z = new QLabel(groupBox_3);
        label_target_z->setObjectName(QString::fromUtf8("label_target_z"));

        gridLayout_3->addWidget(label_target_z, 6, 1, 1, 1);

        label_target = new QLabel(groupBox_3);
        label_target->setObjectName(QString::fromUtf8("label_target"));

        gridLayout_3->addWidget(label_target, 5, 0, 1, 1);

        vect3_target_x = new MyLineEdit(groupBox_3);
        vect3_target_x->setObjectName(QString::fromUtf8("vect3_target_x"));
        sizePolicy.setHeightForWidth(vect3_target_x->sizePolicy().hasHeightForWidth());
        vect3_target_x->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(vect3_target_x, 4, 2, 1, 1);

        vect3_target_y = new MyLineEdit(groupBox_3);
        vect3_target_y->setObjectName(QString::fromUtf8("vect3_target_y"));
        sizePolicy.setHeightForWidth(vect3_target_y->sizePolicy().hasHeightForWidth());
        vect3_target_y->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(vect3_target_y, 5, 2, 1, 1);

        vect3_target_z = new MyLineEdit(groupBox_3);
        vect3_target_z->setObjectName(QString::fromUtf8("vect3_target_z"));
        sizePolicy.setHeightForWidth(vect3_target_z->sizePolicy().hasHeightForWidth());
        vect3_target_z->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(vect3_target_z, 6, 2, 1, 1);


        horizontalLayout->addLayout(gridLayout_3);

        widget_angle_preview = new cLightWidget(groupBox_3);
        widget_angle_preview->setObjectName(QString::fromUtf8("widget_angle_preview"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(1);
        sizePolicy2.setHeightForWidth(widget_angle_preview->sizePolicy().hasHeightForWidth());
        widget_angle_preview->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(widget_angle_preview);


        verticalLayout_3->addLayout(horizontalLayout);

        checkBox_relative_position = new MyCheckBox(groupBox_3);
        checkBox_relative_position->setObjectName(QString::fromUtf8("checkBox_relative_position"));
        sizePolicy1.setHeightForWidth(checkBox_relative_position->sizePolicy().hasHeightForWidth());
        checkBox_relative_position->setSizePolicy(sizePolicy1);

        verticalLayout_3->addWidget(checkBox_relative_position);


        verticalLayout->addWidget(groupBox_3);

        groupBox_orbit = new QGroupBox(cLightEditor);
        groupBox_orbit->setObjectName(QString::fromUtf8("groupBox_orbit"));
        gridLayout_orbit = new QGridLayout(groupBox_orbit);
        gridLayout_orbit->setSpacing(2);
        gridLayout_orbit->setObjectName(QString::fromUtf8("gridLayout_orbit"));
        gridLayout_orbit->setContentsMargins(2, 2, 2, 2);
        label_orbit_dist = new QLabel(groupBox_orbit);
        label_orbit_dist->setObjectName(QString::fromUtf8("label_orbit_dist"));

        gridLayout_orbit->addWidget(label_orbit_dist, 0, 0, 1, 1);

        spinboxd_orbit_distance = new MyDoubleSpinBox(groupBox_orbit);
        spinboxd_orbit_distance->setObjectName(QString::fromUtf8("spinboxd_orbit_distance"));
        spinboxd_orbit_distance->setDecimals(2);
        spinboxd_orbit_distance->setMinimum(0.000000000000000);
        spinboxd_orbit_distance->setMaximum(100000.000000000000000);
        spinboxd_orbit_distance->setSingleStep(0.100000000000000);

        gridLayout_orbit->addWidget(spinboxd_orbit_distance, 0, 1, 1, 1);

        label_orbit_yaw = new QLabel(groupBox_orbit);
        label_orbit_yaw->setObjectName(QString::fromUtf8("label_orbit_yaw"));

        gridLayout_orbit->addWidget(label_orbit_yaw, 1, 0, 1, 1);

        spinboxd_orbit_yaw = new MyDoubleSpinBox(groupBox_orbit);
        spinboxd_orbit_yaw->setObjectName(QString::fromUtf8("spinboxd_orbit_yaw"));
        spinboxd_orbit_yaw->setDecimals(2);
        spinboxd_orbit_yaw->setMinimum(-360.000000000000000);
        spinboxd_orbit_yaw->setMaximum(360.000000000000000);
        spinboxd_orbit_yaw->setSingleStep(1.000000000000000);

        gridLayout_orbit->addWidget(spinboxd_orbit_yaw, 1, 1, 1, 1);

        label_orbit_pitch = new QLabel(groupBox_orbit);
        label_orbit_pitch->setObjectName(QString::fromUtf8("label_orbit_pitch"));

        gridLayout_orbit->addWidget(label_orbit_pitch, 2, 0, 1, 1);

        spinboxd_orbit_pitch = new MyDoubleSpinBox(groupBox_orbit);
        spinboxd_orbit_pitch->setObjectName(QString::fromUtf8("spinboxd_orbit_pitch"));
        spinboxd_orbit_pitch->setDecimals(2);
        spinboxd_orbit_pitch->setMinimum(-90.000000000000000);
        spinboxd_orbit_pitch->setMaximum(90.000000000000000);
        spinboxd_orbit_pitch->setSingleStep(1.000000000000000);

        gridLayout_orbit->addWidget(spinboxd_orbit_pitch, 2, 1, 1, 1);

        pushButton_applyOrbit = new QPushButton(groupBox_orbit);
        pushButton_applyOrbit->setObjectName(QString::fromUtf8("pushButton_applyOrbit"));

        gridLayout_orbit->addWidget(pushButton_applyOrbit, 3, 0, 1, 2);


        verticalLayout->addWidget(groupBox_orbit);

        groupBox_autoIntensity = new QGroupBox(cLightEditor);
        groupBox_autoIntensity->setObjectName(QString::fromUtf8("groupBox_autoIntensity"));
        gridLayout_autoIntensity = new QGridLayout(groupBox_autoIntensity);
        gridLayout_autoIntensity->setSpacing(2);
        gridLayout_autoIntensity->setObjectName(QString::fromUtf8("gridLayout_autoIntensity"));
        gridLayout_autoIntensity->setContentsMargins(2, 2, 2, 2);
        checkBox_auto_intensity = new MyCheckBox(groupBox_autoIntensity);
        checkBox_auto_intensity->setObjectName(QString::fromUtf8("checkBox_auto_intensity"));

        gridLayout_autoIntensity->addWidget(checkBox_auto_intensity, 0, 0, 1, 2);

        label_auto_intensity_factor = new QLabel(groupBox_autoIntensity);
        label_auto_intensity_factor->setObjectName(QString::fromUtf8("label_auto_intensity_factor"));

        gridLayout_autoIntensity->addWidget(label_auto_intensity_factor, 1, 0, 1, 1);

        spinboxd_auto_intensity_factor = new MyDoubleSpinBox(groupBox_autoIntensity);
        spinboxd_auto_intensity_factor->setObjectName(QString::fromUtf8("spinboxd_auto_intensity_factor"));
        spinboxd_auto_intensity_factor->setDecimals(4);
        spinboxd_auto_intensity_factor->setMinimum(0.000000000000000);
        spinboxd_auto_intensity_factor->setMaximum(1.000000000000000);
        spinboxd_auto_intensity_factor->setSingleStep(0.001000000000000);

        gridLayout_autoIntensity->addWidget(spinboxd_auto_intensity_factor, 1, 1, 1, 1);

        pushButton_applyAutoIntensity = new QPushButton(groupBox_autoIntensity);
        pushButton_applyAutoIntensity->setObjectName(QString::fromUtf8("pushButton_applyAutoIntensity"));

        gridLayout_autoIntensity->addWidget(pushButton_applyAutoIntensity, 2, 0, 1, 2);


        verticalLayout->addWidget(groupBox_autoIntensity);

        groupBox_4 = new QGroupBox(cLightEditor);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_7 = new QGridLayout(groupBox_4);
        gridLayout_7->setSpacing(2);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        gridLayout_7->setContentsMargins(2, 2, 2, 2);
        checkBox_cast_shadows = new MyCheckBox(groupBox_4);
        checkBox_cast_shadows->setObjectName(QString::fromUtf8("checkBox_cast_shadows"));
        sizePolicy1.setHeightForWidth(checkBox_cast_shadows->sizePolicy().hasHeightForWidth());
        checkBox_cast_shadows->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(checkBox_cast_shadows, 1, 0, 1, 1);

        checkBox_penetrating = new MyCheckBox(groupBox_4);
        checkBox_penetrating->setObjectName(QString::fromUtf8("checkBox_penetrating"));
        sizePolicy1.setHeightForWidth(checkBox_penetrating->sizePolicy().hasHeightForWidth());
        checkBox_penetrating->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(checkBox_penetrating, 2, 0, 1, 1);

        label_30 = new QLabel(groupBox_4);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        gridLayout_7->addWidget(label_30, 0, 0, 1, 1);

        spinbox_soft_shadow_cone = new MyDoubleSpinBox(groupBox_4);
        spinbox_soft_shadow_cone->setObjectName(QString::fromUtf8("spinbox_soft_shadow_cone"));
        sizePolicy.setHeightForWidth(spinbox_soft_shadow_cone->sizePolicy().hasHeightForWidth());
        spinbox_soft_shadow_cone->setSizePolicy(sizePolicy);
        spinbox_soft_shadow_cone->setFrame(true);
        spinbox_soft_shadow_cone->setAccelerated(true);
        spinbox_soft_shadow_cone->setDecimals(2);
        spinbox_soft_shadow_cone->setMinimum(-100000.000000000000000);
        spinbox_soft_shadow_cone->setMaximum(100000.000000000000000);
        spinbox_soft_shadow_cone->setSingleStep(1.000000000000000);

        gridLayout_7->addWidget(spinbox_soft_shadow_cone, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBox_4);

        groupCheck_volumetric = new MyGroupBox(cLightEditor);
        groupCheck_volumetric->setObjectName(QString::fromUtf8("groupCheck_volumetric"));
        groupCheck_volumetric->setCheckable(true);
        gridLayout_4 = new QGridLayout(groupCheck_volumetric);
        gridLayout_4->setSpacing(2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(2, 2, 2, 2);
        logedit_volumetric_visibility = new MyLineEdit(groupCheck_volumetric);
        logedit_volumetric_visibility->setObjectName(QString::fromUtf8("logedit_volumetric_visibility"));

        gridLayout_4->addWidget(logedit_volumetric_visibility, 0, 1, 1, 1);

        label_4 = new QLabel(groupCheck_volumetric);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 0, 0, 1, 1);


        verticalLayout->addWidget(groupCheck_volumetric);

        groupBox_cone_options = new QGroupBox(cLightEditor);
        groupBox_cone_options->setObjectName(QString::fromUtf8("groupBox_cone_options"));
        groupBox_cone_options->setEnabled(false);
        gridLayout_6 = new QGridLayout(groupBox_cone_options);
        gridLayout_6->setSpacing(2);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_6->setContentsMargins(2, 2, 2, 2);
        logedit_cone_angle = new MyLineEdit(groupBox_cone_options);
        logedit_cone_angle->setObjectName(QString::fromUtf8("logedit_cone_angle"));

        gridLayout_6->addWidget(logedit_cone_angle, 0, 1, 1, 1);

        label_62 = new QLabel(groupBox_cone_options);
        label_62->setObjectName(QString::fromUtf8("label_62"));
        QSizePolicy sizePolicy3(QSizePolicy::Maximum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_62->sizePolicy().hasHeightForWidth());
        label_62->setSizePolicy(sizePolicy3);

        gridLayout_6->addWidget(label_62, 0, 0, 1, 1);

        label_64 = new QLabel(groupBox_cone_options);
        label_64->setObjectName(QString::fromUtf8("label_64"));
        sizePolicy3.setHeightForWidth(label_64->sizePolicy().hasHeightForWidth());
        label_64->setSizePolicy(sizePolicy3);

        gridLayout_6->addWidget(label_64, 1, 0, 1, 1);

        logedit_cone_soft_angle = new MyLineEdit(groupBox_cone_options);
        logedit_cone_soft_angle->setObjectName(QString::fromUtf8("logedit_cone_soft_angle"));

        gridLayout_6->addWidget(logedit_cone_soft_angle, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox_cone_options);

        groupBox_projection_options = new QGroupBox(cLightEditor);
        groupBox_projection_options->setObjectName(QString::fromUtf8("groupBox_projection_options"));
        groupBox_projection_options->setEnabled(false);
        verticalLayout_4 = new QVBoxLayout(groupBox_projection_options);
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        text_file_texture = new FileSelectWidget(groupBox_projection_options);
        text_file_texture->setObjectName(QString::fromUtf8("text_file_texture"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(text_file_texture->sizePolicy().hasHeightForWidth());
        text_file_texture->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(text_file_texture, 0, 1, 1, 1);

        label_61 = new QLabel(groupBox_projection_options);
        label_61->setObjectName(QString::fromUtf8("label_61"));
        sizePolicy3.setHeightForWidth(label_61->sizePolicy().hasHeightForWidth());
        label_61->setSizePolicy(sizePolicy3);

        gridLayout_5->addWidget(label_61, 0, 0, 1, 1);

        text_file_texture_alpha = new FileSelectWidget(groupBox_projection_options);
        text_file_texture_alpha->setObjectName(QString::fromUtf8("text_file_texture_alpha"));
        sizePolicy4.setHeightForWidth(text_file_texture_alpha->sizePolicy().hasHeightForWidth());
        text_file_texture_alpha->setSizePolicy(sizePolicy4);

        gridLayout_5->addWidget(text_file_texture_alpha, 1, 1, 1, 1);

        label_alpha_texture = new QLabel(groupBox_projection_options);
        label_alpha_texture->setObjectName(QString::fromUtf8("label_alpha_texture"));
        sizePolicy3.setHeightForWidth(label_alpha_texture->sizePolicy().hasHeightForWidth());
        label_alpha_texture->setSizePolicy(sizePolicy3);

        gridLayout_5->addWidget(label_alpha_texture, 1, 0, 1, 1);


        verticalLayout_4->addLayout(gridLayout_5);

        gridLayout_8 = new QGridLayout();
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        logedit_projection_vertical_angle = new MyLineEdit(groupBox_projection_options);
        logedit_projection_vertical_angle->setObjectName(QString::fromUtf8("logedit_projection_vertical_angle"));

        gridLayout_8->addWidget(logedit_projection_vertical_angle, 1, 1, 1, 1);

        logedit_projection_horizonal_angle = new MyLineEdit(groupBox_projection_options);
        logedit_projection_horizonal_angle->setObjectName(QString::fromUtf8("logedit_projection_horizonal_angle"));

        gridLayout_8->addWidget(logedit_projection_horizonal_angle, 0, 1, 1, 1);

        label_63 = new QLabel(groupBox_projection_options);
        label_63->setObjectName(QString::fromUtf8("label_63"));
        sizePolicy3.setHeightForWidth(label_63->sizePolicy().hasHeightForWidth());
        label_63->setSizePolicy(sizePolicy3);
        label_63->setWordWrap(true);

        gridLayout_8->addWidget(label_63, 0, 0, 1, 1);

        label_65 = new QLabel(groupBox_projection_options);
        label_65->setObjectName(QString::fromUtf8("label_65"));
        sizePolicy3.setHeightForWidth(label_65->sizePolicy().hasHeightForWidth());
        label_65->setSizePolicy(sizePolicy3);
        label_65->setWordWrap(true);

        gridLayout_8->addWidget(label_65, 1, 0, 1, 1);

        label_repeat_mode = new QLabel(groupBox_projection_options);
        label_repeat_mode->setObjectName(QString::fromUtf8("label_repeat_mode"));
        sizePolicy3.setHeightForWidth(label_repeat_mode->sizePolicy().hasHeightForWidth());
        label_repeat_mode->setSizePolicy(sizePolicy3);
        label_repeat_mode->setWordWrap(true);

        gridLayout_8->addWidget(label_repeat_mode, 2, 0, 1, 1);

        comboBox_projection_repeat_mode = new MyComboBox(groupBox_projection_options);
        comboBox_projection_repeat_mode->addItem(QString());
        comboBox_projection_repeat_mode->addItem(QString());
        comboBox_projection_repeat_mode->addItem(QString());
        comboBox_projection_repeat_mode->setObjectName(QString::fromUtf8("comboBox_projection_repeat_mode"));

        gridLayout_8->addWidget(comboBox_projection_repeat_mode, 2, 1, 1, 1);

        label_soft_edge = new QLabel(groupBox_projection_options);
        label_soft_edge->setObjectName(QString::fromUtf8("label_soft_edge"));
        sizePolicy3.setHeightForWidth(label_soft_edge->sizePolicy().hasHeightForWidth());
        label_soft_edge->setSizePolicy(sizePolicy3);
        label_soft_edge->setWordWrap(true);

        gridLayout_8->addWidget(label_soft_edge, 3, 0, 1, 1);

        logedit_projection_soft_edge = new MyLineEdit(groupBox_projection_options);
        logedit_projection_soft_edge->setObjectName(QString::fromUtf8("logedit_projection_soft_edge"));

        gridLayout_8->addWidget(logedit_projection_soft_edge, 3, 1, 1, 1);

        label_texture_offset_x = new QLabel(groupBox_projection_options);
        label_texture_offset_x->setObjectName(QString::fromUtf8("label_texture_offset_x"));
        sizePolicy3.setHeightForWidth(label_texture_offset_x->sizePolicy().hasHeightForWidth());
        label_texture_offset_x->setSizePolicy(sizePolicy3);
        label_texture_offset_x->setWordWrap(true);

        gridLayout_8->addWidget(label_texture_offset_x, 4, 0, 1, 1);

        logedit_projection_texture_offset_x = new MyLineEdit(groupBox_projection_options);
        logedit_projection_texture_offset_x->setObjectName(QString::fromUtf8("logedit_projection_texture_offset_x"));

        gridLayout_8->addWidget(logedit_projection_texture_offset_x, 4, 1, 1, 1);

        label_texture_offset_y = new QLabel(groupBox_projection_options);
        label_texture_offset_y->setObjectName(QString::fromUtf8("label_texture_offset_y"));
        sizePolicy3.setHeightForWidth(label_texture_offset_y->sizePolicy().hasHeightForWidth());
        label_texture_offset_y->setSizePolicy(sizePolicy3);
        label_texture_offset_y->setWordWrap(true);

        gridLayout_8->addWidget(label_texture_offset_y, 5, 0, 1, 1);

        logedit_projection_texture_offset_y = new MyLineEdit(groupBox_projection_options);
        logedit_projection_texture_offset_y->setObjectName(QString::fromUtf8("logedit_projection_texture_offset_y"));

        gridLayout_8->addWidget(logedit_projection_texture_offset_y, 5, 1, 1, 1);

        label_texture_offset_z = new QLabel(groupBox_projection_options);
        label_texture_offset_z->setObjectName(QString::fromUtf8("label_texture_offset_z"));
        sizePolicy3.setHeightForWidth(label_texture_offset_z->sizePolicy().hasHeightForWidth());
        label_texture_offset_z->setSizePolicy(sizePolicy3);
        label_texture_offset_z->setWordWrap(true);

        gridLayout_8->addWidget(label_texture_offset_z, 6, 0, 1, 1);

        logedit_projection_texture_offset_z = new MyLineEdit(groupBox_projection_options);
        logedit_projection_texture_offset_z->setObjectName(QString::fromUtf8("logedit_projection_texture_offset_z"));

        gridLayout_8->addWidget(logedit_projection_texture_offset_z, 6, 1, 1, 1);

        label_texture_scale_x = new QLabel(groupBox_projection_options);
        label_texture_scale_x->setObjectName(QString::fromUtf8("label_texture_scale_x"));
        sizePolicy3.setHeightForWidth(label_texture_scale_x->sizePolicy().hasHeightForWidth());
        label_texture_scale_x->setSizePolicy(sizePolicy3);
        label_texture_scale_x->setWordWrap(true);

        gridLayout_8->addWidget(label_texture_scale_x, 7, 0, 1, 1);

        logedit_projection_texture_scale_x = new MyLineEdit(groupBox_projection_options);
        logedit_projection_texture_scale_x->setObjectName(QString::fromUtf8("logedit_projection_texture_scale_x"));

        gridLayout_8->addWidget(logedit_projection_texture_scale_x, 7, 1, 1, 1);

        label_texture_scale_y = new QLabel(groupBox_projection_options);
        label_texture_scale_y->setObjectName(QString::fromUtf8("label_texture_scale_y"));
        sizePolicy3.setHeightForWidth(label_texture_scale_y->sizePolicy().hasHeightForWidth());
        label_texture_scale_y->setSizePolicy(sizePolicy3);
        label_texture_scale_y->setWordWrap(true);

        gridLayout_8->addWidget(label_texture_scale_y, 8, 0, 1, 1);

        logedit_projection_texture_scale_y = new MyLineEdit(groupBox_projection_options);
        logedit_projection_texture_scale_y->setObjectName(QString::fromUtf8("logedit_projection_texture_scale_y"));

        gridLayout_8->addWidget(logedit_projection_texture_scale_y, 8, 1, 1, 1);

        label_texture_scale_z = new QLabel(groupBox_projection_options);
        label_texture_scale_z->setObjectName(QString::fromUtf8("label_texture_scale_z"));
        sizePolicy3.setHeightForWidth(label_texture_scale_z->sizePolicy().hasHeightForWidth());
        label_texture_scale_z->setSizePolicy(sizePolicy3);
        label_texture_scale_z->setWordWrap(true);

        gridLayout_8->addWidget(label_texture_scale_z, 9, 0, 1, 1);

        logedit_projection_texture_scale_z = new MyLineEdit(groupBox_projection_options);
        logedit_projection_texture_scale_z->setObjectName(QString::fromUtf8("logedit_projection_texture_scale_z"));

        gridLayout_8->addWidget(logedit_projection_texture_scale_z, 9, 1, 1, 1);

        label_texture_rotation_x = new QLabel(groupBox_projection_options);
        label_texture_rotation_x->setObjectName(QString::fromUtf8("label_texture_rotation_x"));
        sizePolicy3.setHeightForWidth(label_texture_rotation_x->sizePolicy().hasHeightForWidth());
        label_texture_rotation_x->setSizePolicy(sizePolicy3);
        label_texture_rotation_x->setWordWrap(true);

        gridLayout_8->addWidget(label_texture_rotation_x, 10, 0, 1, 1);

        logedit_projection_texture_rotation_x = new MyLineEdit(groupBox_projection_options);
        logedit_projection_texture_rotation_x->setObjectName(QString::fromUtf8("logedit_projection_texture_rotation_x"));

        gridLayout_8->addWidget(logedit_projection_texture_rotation_x, 10, 1, 1, 1);

        label_texture_rotation_y = new QLabel(groupBox_projection_options);
        label_texture_rotation_y->setObjectName(QString::fromUtf8("label_texture_rotation_y"));
        sizePolicy3.setHeightForWidth(label_texture_rotation_y->sizePolicy().hasHeightForWidth());
        label_texture_rotation_y->setSizePolicy(sizePolicy3);
        label_texture_rotation_y->setWordWrap(true);

        gridLayout_8->addWidget(label_texture_rotation_y, 11, 0, 1, 1);

        logedit_projection_texture_rotation_y = new MyLineEdit(groupBox_projection_options);
        logedit_projection_texture_rotation_y->setObjectName(QString::fromUtf8("logedit_projection_texture_rotation_y"));

        gridLayout_8->addWidget(logedit_projection_texture_rotation_y, 11, 1, 1, 1);

        label_texture_rotation_z = new QLabel(groupBox_projection_options);
        label_texture_rotation_z->setObjectName(QString::fromUtf8("label_texture_rotation_z"));
        sizePolicy3.setHeightForWidth(label_texture_rotation_z->sizePolicy().hasHeightForWidth());
        label_texture_rotation_z->setSizePolicy(sizePolicy3);
        label_texture_rotation_z->setWordWrap(true);

        gridLayout_8->addWidget(label_texture_rotation_z, 12, 0, 1, 1);

        logedit_projection_texture_rotation_z = new MyLineEdit(groupBox_projection_options);
        logedit_projection_texture_rotation_z->setObjectName(QString::fromUtf8("logedit_projection_texture_rotation_z"));

        gridLayout_8->addWidget(logedit_projection_texture_rotation_z, 12, 1, 1, 1);

        checkBox_projection_use_as_mask = new MyCheckBox(groupBox_projection_options);
        checkBox_projection_use_as_mask->setObjectName(QString::fromUtf8("checkBox_projection_use_as_mask"));

        gridLayout_8->addWidget(checkBox_projection_use_as_mask, 13, 0, 1, 2);

        checkBox_projection_use_alpha_as_mask = new MyCheckBox(groupBox_projection_options);
        checkBox_projection_use_alpha_as_mask->setObjectName(QString::fromUtf8("checkBox_projection_use_alpha_as_mask"));

        gridLayout_8->addWidget(checkBox_projection_use_alpha_as_mask, 14, 0, 1, 2);

        checkBox_projection_use_texture_alpha_as_mask = new MyCheckBox(groupBox_projection_options);
        checkBox_projection_use_texture_alpha_as_mask->setObjectName(QString::fromUtf8("checkBox_projection_use_texture_alpha_as_mask"));

        gridLayout_8->addWidget(checkBox_projection_use_texture_alpha_as_mask, 15, 0, 1, 2);

        checkBox_projection_invert_alpha_mask = new MyCheckBox(groupBox_projection_options);
        checkBox_projection_invert_alpha_mask->setObjectName(QString::fromUtf8("checkBox_projection_invert_alpha_mask"));

        gridLayout_8->addWidget(checkBox_projection_invert_alpha_mask, 16, 0, 1, 2);

        label_projection_intensity = new QLabel(groupBox_projection_options);
        label_projection_intensity->setObjectName(QString::fromUtf8("label_projection_intensity"));

        gridLayout_8->addWidget(label_projection_intensity, 17, 0, 1, 1);

        logedit_projection_intensity = new MyLineEdit(groupBox_projection_options);
        logedit_projection_intensity->setObjectName(QString::fromUtf8("logedit_projection_intensity"));

        gridLayout_8->addWidget(logedit_projection_intensity, 17, 1, 1, 1);

        label_projection_blend_mode = new QLabel(groupBox_projection_options);
        label_projection_blend_mode->setObjectName(QString::fromUtf8("label_projection_blend_mode"));

        gridLayout_8->addWidget(label_projection_blend_mode, 18, 0, 1, 1);

        comboBox_projection_blend_mode = new MyComboBox(groupBox_projection_options);
        comboBox_projection_blend_mode->addItem(QString());
        comboBox_projection_blend_mode->addItem(QString());
        comboBox_projection_blend_mode->addItem(QString());
        comboBox_projection_blend_mode->addItem(QString());
        comboBox_projection_blend_mode->setObjectName(QString::fromUtf8("comboBox_projection_blend_mode"));

        gridLayout_8->addWidget(comboBox_projection_blend_mode, 18, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout_8);

        gridLayout_alpha = new QGridLayout();
        gridLayout_alpha->setObjectName(QString::fromUtf8("gridLayout_alpha"));
        label_alpha_offset_x = new QLabel(groupBox_projection_options);
        label_alpha_offset_x->setObjectName(QString::fromUtf8("label_alpha_offset_x"));

        gridLayout_alpha->addWidget(label_alpha_offset_x, 0, 0, 1, 1);

        logedit_alpha_texture_offset_x = new MyLineEdit(groupBox_projection_options);
        logedit_alpha_texture_offset_x->setObjectName(QString::fromUtf8("logedit_alpha_texture_offset_x"));

        gridLayout_alpha->addWidget(logedit_alpha_texture_offset_x, 0, 1, 1, 1);

        label_alpha_offset_y = new QLabel(groupBox_projection_options);
        label_alpha_offset_y->setObjectName(QString::fromUtf8("label_alpha_offset_y"));

        gridLayout_alpha->addWidget(label_alpha_offset_y, 1, 0, 1, 1);

        logedit_alpha_texture_offset_y = new MyLineEdit(groupBox_projection_options);
        logedit_alpha_texture_offset_y->setObjectName(QString::fromUtf8("logedit_alpha_texture_offset_y"));

        gridLayout_alpha->addWidget(logedit_alpha_texture_offset_y, 1, 1, 1, 1);

        label_alpha_scale_x = new QLabel(groupBox_projection_options);
        label_alpha_scale_x->setObjectName(QString::fromUtf8("label_alpha_scale_x"));

        gridLayout_alpha->addWidget(label_alpha_scale_x, 2, 0, 1, 1);

        logedit_alpha_texture_scale_x = new MyLineEdit(groupBox_projection_options);
        logedit_alpha_texture_scale_x->setObjectName(QString::fromUtf8("logedit_alpha_texture_scale_x"));

        gridLayout_alpha->addWidget(logedit_alpha_texture_scale_x, 2, 1, 1, 1);

        label_alpha_scale_y = new QLabel(groupBox_projection_options);
        label_alpha_scale_y->setObjectName(QString::fromUtf8("label_alpha_scale_y"));

        gridLayout_alpha->addWidget(label_alpha_scale_y, 3, 0, 1, 1);

        logedit_alpha_texture_scale_y = new MyLineEdit(groupBox_projection_options);
        logedit_alpha_texture_scale_y->setObjectName(QString::fromUtf8("logedit_alpha_texture_scale_y"));

        gridLayout_alpha->addWidget(logedit_alpha_texture_scale_y, 3, 1, 1, 1);

        label_alpha_rotation_z = new QLabel(groupBox_projection_options);
        label_alpha_rotation_z->setObjectName(QString::fromUtf8("label_alpha_rotation_z"));

        gridLayout_alpha->addWidget(label_alpha_rotation_z, 4, 0, 1, 1);

        logedit_alpha_texture_rotation_z = new MyLineEdit(groupBox_projection_options);
        logedit_alpha_texture_rotation_z->setObjectName(QString::fromUtf8("logedit_alpha_texture_rotation_z"));

        gridLayout_alpha->addWidget(logedit_alpha_texture_rotation_z, 4, 1, 1, 1);

        label_alpha_repeat_mode = new QLabel(groupBox_projection_options);
        label_alpha_repeat_mode->setObjectName(QString::fromUtf8("label_alpha_repeat_mode"));

        gridLayout_alpha->addWidget(label_alpha_repeat_mode, 5, 0, 1, 1);

        comboBox_alpha_texture_repeat_mode = new MyComboBox(groupBox_projection_options);
        comboBox_alpha_texture_repeat_mode->addItem(QString());
        comboBox_alpha_texture_repeat_mode->addItem(QString());
        comboBox_alpha_texture_repeat_mode->addItem(QString());
        comboBox_alpha_texture_repeat_mode->setObjectName(QString::fromUtf8("comboBox_alpha_texture_repeat_mode"));

        gridLayout_alpha->addWidget(comboBox_alpha_texture_repeat_mode, 5, 1, 1, 1);

        label_alpha_soft_edge = new QLabel(groupBox_projection_options);
        label_alpha_soft_edge->setObjectName(QString::fromUtf8("label_alpha_soft_edge"));

        gridLayout_alpha->addWidget(label_alpha_soft_edge, 6, 0, 1, 1);

        logedit_alpha_texture_soft_edge = new MyLineEdit(groupBox_projection_options);
        logedit_alpha_texture_soft_edge->setObjectName(QString::fromUtf8("logedit_alpha_texture_soft_edge"));

        gridLayout_alpha->addWidget(logedit_alpha_texture_soft_edge, 6, 1, 1, 1);


        verticalLayout_4->addLayout(gridLayout_alpha);


        verticalLayout->addWidget(groupBox_projection_options);

        groupBox_beam_options = new QGroupBox(cLightEditor);
        groupBox_beam_options->setObjectName(QString::fromUtf8("groupBox_beam_options"));
        groupBox_beam_options->setEnabled(false);
        verticalLayout_beam = new QVBoxLayout(groupBox_beam_options);
        verticalLayout_beam->setSpacing(2);
        verticalLayout_beam->setObjectName(QString::fromUtf8("verticalLayout_beam"));
        verticalLayout_beam->setContentsMargins(2, 2, 2, 2);
        gridLayout_beam = new QGridLayout();
        gridLayout_beam->setObjectName(QString::fromUtf8("gridLayout_beam"));
        label_beam_radius = new QLabel(groupBox_beam_options);
        label_beam_radius->setObjectName(QString::fromUtf8("label_beam_radius"));

        gridLayout_beam->addWidget(label_beam_radius, 0, 0, 1, 1);

        logedit_beam_radius = new MyLineEdit(groupBox_beam_options);
        logedit_beam_radius->setObjectName(QString::fromUtf8("logedit_beam_radius"));

        gridLayout_beam->addWidget(logedit_beam_radius, 0, 1, 1, 1);

        label_beam_soft_edge = new QLabel(groupBox_beam_options);
        label_beam_soft_edge->setObjectName(QString::fromUtf8("label_beam_soft_edge"));

        gridLayout_beam->addWidget(label_beam_soft_edge, 1, 0, 1, 1);

        logedit_beam_soft_edge = new MyLineEdit(groupBox_beam_options);
        logedit_beam_soft_edge->setObjectName(QString::fromUtf8("logedit_beam_soft_edge"));

        gridLayout_beam->addWidget(logedit_beam_soft_edge, 1, 1, 1, 1);

        label_beam_fade_in = new QLabel(groupBox_beam_options);
        label_beam_fade_in->setObjectName(QString::fromUtf8("label_beam_fade_in"));

        gridLayout_beam->addWidget(label_beam_fade_in, 2, 0, 1, 1);

        logedit_beam_fade_in = new MyLineEdit(groupBox_beam_options);
        logedit_beam_fade_in->setObjectName(QString::fromUtf8("logedit_beam_fade_in"));

        gridLayout_beam->addWidget(logedit_beam_fade_in, 2, 1, 1, 1);

        label_beam_fade_out = new QLabel(groupBox_beam_options);
        label_beam_fade_out->setObjectName(QString::fromUtf8("label_beam_fade_out"));

        gridLayout_beam->addWidget(label_beam_fade_out, 3, 0, 1, 1);

        logedit_beam_fade_out = new MyLineEdit(groupBox_beam_options);
        logedit_beam_fade_out->setObjectName(QString::fromUtf8("logedit_beam_fade_out"));

        gridLayout_beam->addWidget(logedit_beam_fade_out, 3, 1, 1, 1);


        verticalLayout_beam->addLayout(gridLayout_beam);


        verticalLayout->addWidget(groupBox_beam_options);

        groupBox_spherical_texture = new QGroupBox(cLightEditor);
        groupBox_spherical_texture->setObjectName(QString::fromUtf8("groupBox_spherical_texture"));
        groupBox_spherical_texture->setEnabled(false);
        verticalLayout_spherical = new QVBoxLayout(groupBox_spherical_texture);
        verticalLayout_spherical->setSpacing(2);
        verticalLayout_spherical->setObjectName(QString::fromUtf8("verticalLayout_spherical"));
        verticalLayout_spherical->setContentsMargins(2, 2, 2, 2);
        gridLayout_spherical = new QGridLayout();
        gridLayout_spherical->setObjectName(QString::fromUtf8("gridLayout_spherical"));
        label_spherical_texture = new QLabel(groupBox_spherical_texture);
        label_spherical_texture->setObjectName(QString::fromUtf8("label_spherical_texture"));

        gridLayout_spherical->addWidget(label_spherical_texture, 0, 0, 1, 1);

        text_file_texture_spherical = new FileSelectWidget(groupBox_spherical_texture);
        text_file_texture_spherical->setObjectName(QString::fromUtf8("text_file_texture_spherical"));
        sizePolicy4.setHeightForWidth(text_file_texture_spherical->sizePolicy().hasHeightForWidth());
        text_file_texture_spherical->setSizePolicy(sizePolicy4);

        gridLayout_spherical->addWidget(text_file_texture_spherical, 0, 1, 1, 1);

        label_spherical_intensity = new QLabel(groupBox_spherical_texture);
        label_spherical_intensity->setObjectName(QString::fromUtf8("label_spherical_intensity"));

        gridLayout_spherical->addWidget(label_spherical_intensity, 1, 0, 1, 1);

        logedit_spherical_texture_intensity = new MyLineEdit(groupBox_spherical_texture);
        logedit_spherical_texture_intensity->setObjectName(QString::fromUtf8("logedit_spherical_texture_intensity"));

        gridLayout_spherical->addWidget(logedit_spherical_texture_intensity, 1, 1, 1, 1);


        verticalLayout_spherical->addLayout(gridLayout_spherical);


        verticalLayout->addWidget(groupBox_spherical_texture);


        retranslateUi(cLightEditor);

        QMetaObject::connectSlotsByName(cLightEditor);
    } // setupUi

    void retranslateUi(QWidget *cLightEditor)
    {
        cLightEditor->setWindowTitle(QCoreApplication::translate("cLightEditor", "Form", nullptr));
        groupBox->setTitle(QCoreApplication::translate("cLightEditor", "Parameters", nullptr));
#if QT_CONFIG(tooltip)
        logedit_intensity->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Brightness of the light source. Strength of  illumination.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        colorButton_color->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Color of light source</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        colorButton_color->setProperty("text", QVariant(QCoreApplication::translate("cLightEditor", "PushButton", nullptr)));
        label_11->setText(QCoreApplication::translate("cLightEditor", "Intensity:", nullptr));
        label_14->setText(QCoreApplication::translate("cLightEditor", "Size:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_size->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Size of illuminated fog around the light source.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_visibility->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Visibility of the light source. It simulates illuminated fog around the light source.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_13->setText(QCoreApplication::translate("cLightEditor", "Visibility:", nullptr));
        comboBox_type->setItemText(0, QCoreApplication::translate("cLightEditor", "Directional light", nullptr));
        comboBox_type->setItemText(1, QCoreApplication::translate("cLightEditor", "Point light", nullptr));
        comboBox_type->setItemText(2, QCoreApplication::translate("cLightEditor", "Spot light", nullptr));
        comboBox_type->setItemText(3, QCoreApplication::translate("cLightEditor", "Projection", nullptr));
        comboBox_type->setItemText(4, QCoreApplication::translate("cLightEditor", "Beam", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_type->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Selection of light source type</p><p>- Directional light - light source emitting from infinite distance at the angle defined by user</p><p>- Point light - light source emitting evenly around user defined point</p><p>- Spot light - light source emitting conical beam</p><p>- Projection - light source emitting beam of light colorized by texture image</p><p>- Beam - linear beam of the light (requires Monte Carlo rendering mode)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_15->setText(QCoreApplication::translate("cLightEditor", "Decay function", nullptr));
        label_2->setText(QCoreApplication::translate("cLightEditor", "Type:", nullptr));
        label_12->setText(QCoreApplication::translate("cLightEditor", "Color:", nullptr));
        comboBox_decayFunction->setItemText(0, QCoreApplication::translate("cLightEditor", "1/r", nullptr));
        comboBox_decayFunction->setItemText(1, QCoreApplication::translate("cLightEditor", "1/r\302\262", nullptr));
        comboBox_decayFunction->setItemText(2, QCoreApplication::translate("cLightEditor", "1/r\302\263", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_decayFunction->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Decay function defines how light intensity decays with distance from the light. Decay function 1/r\302\262 complies with the laws of physics. 1/r reduces the decaying of light intensity. 1/r\302\263 increases the decaying of light intensity. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_contour_sharpness->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Sharpness of contour of the light source.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_16->setText(QCoreApplication::translate("cLightEditor", "Contour sharpness:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("cLightEditor", "Position", nullptr));
#if QT_CONFIG(tooltip)
        vect3_position_z->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Coordinates of light source</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        vect3_position_y->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Coordinates of light source</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        vect3_position_x->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Coordinates of light source</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_21->setText(QCoreApplication::translate("cLightEditor", "x:", nullptr));
        label->setText(QCoreApplication::translate("cLightEditor", "Position:", nullptr));
        label_22->setText(QCoreApplication::translate("cLightEditor", "y:", nullptr));
        label_23->setText(QCoreApplication::translate("cLightEditor", "z:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxd3_rotation_z->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Rotation of light source.</p><p>For directional lights it can be controlled with ball widget.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinboxd3_rotation_z->setPrefix(QString());
        spinboxd3_rotation_z->setSuffix(QString());
        checkBox_use_target_point->setText(QCoreApplication::translate("cLightEditor", "Use target point instead of angles", nullptr));
#if QT_CONFIG(tooltip)
        spinboxd3_rotation_y->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Rotation of light source.</p><p>For directional lights it can be controlled with ball widget.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinboxd3_rotation_y->setPrefix(QString());
        spinboxd3_rotation_y->setSuffix(QString());
        label_target_y->setText(QCoreApplication::translate("cLightEditor", "y:", nullptr));
        label_roll->setText(QCoreApplication::translate("cLightEditor", "roll:", nullptr));
        label_vertical->setText(QCoreApplication::translate("cLightEditor", "vertical:", nullptr));
        label_horizontal->setText(QCoreApplication::translate("cLightEditor", "horizontal:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxd3_rotation_x->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Rotation of light source.</p><p>For directional lights it can be controlled with ball widget.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinboxd3_rotation_x->setPrefix(QString());
        spinboxd3_rotation_x->setSuffix(QString());
        label_angle->setText(QCoreApplication::translate("cLightEditor", "Angle:", nullptr));
        label_target_x->setText(QCoreApplication::translate("cLightEditor", "x:", nullptr));
        label_target_z->setText(QCoreApplication::translate("cLightEditor", "z:", nullptr));
        label_target->setText(QCoreApplication::translate("cLightEditor", "Target:", nullptr));
#if QT_CONFIG(tooltip)
        vect3_target_x->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Coordinates of light source</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        vect3_target_y->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Coordinates of light source</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        vect3_target_z->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Coordinates of light source</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_relative_position->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Enabling this option makes coordinates and rotation of the light relative to the camera. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_relative_position->setText(QCoreApplication::translate("cLightEditor", "Position and rotation relative to camera", nullptr));
        groupBox_orbit->setTitle(QCoreApplication::translate("cLightEditor", "Orbit placement", nullptr));
        label_orbit_dist->setText(QCoreApplication::translate("cLightEditor", "Distance:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxd_orbit_distance->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Distance from target point</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_orbit_yaw->setText(QCoreApplication::translate("cLightEditor", "Yaw:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxd_orbit_yaw->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Horizontal angle around target (-180 to 180)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_orbit_pitch->setText(QCoreApplication::translate("cLightEditor", "Pitch:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxd_orbit_pitch->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Vertical angle above/below target (-90 to 90)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pushButton_applyOrbit->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Calculate light position from orbit parameters and apply to position</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_applyOrbit->setText(QCoreApplication::translate("cLightEditor", "Apply orbit to position", nullptr));
        groupBox_autoIntensity->setTitle(QCoreApplication::translate("cLightEditor", "Auto intensity", nullptr));
        checkBox_auto_intensity->setText(QCoreApplication::translate("cLightEditor", "Auto-adjust intensity by distance", nullptr));
        label_auto_intensity_factor->setText(QCoreApplication::translate("cLightEditor", "Factor:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxd_auto_intensity_factor->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Multiplier for auto-calculated intensity. Formula: intensity = distance\302\262 \303\227 factor. Default 0.01 gives reasonable brightness at typical distances.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pushButton_applyAutoIntensity->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Calculate intensity based on distance to fractal surface and apply</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_applyAutoIntensity->setText(QCoreApplication::translate("cLightEditor", "Apply auto intensity", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("cLightEditor", "Shadows", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_cast_shadows->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Enables casting shadows from the light source</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_cast_shadows->setText(QCoreApplication::translate("cLightEditor", "Cast shadows", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_penetrating->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Makes light rays penetrate all the objects. When it's enabled, then even inside the fractal it will not be completely dark. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_penetrating->setText(QCoreApplication::translate("cLightEditor", "Penetrating light", nullptr));
        label_30->setText(QCoreApplication::translate("cLightEditor", "Soft shadow cone angle:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_soft_shadow_cone->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>This parameter controls angle of shadows cone. It simulates &quot;soft shadow&quot; effect. When it's zero, then shadows are very sharp.</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>shadow cone 0 degrees</p></td><td><p>shadow cone 5 degrees </p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - shader - shadow cone 0.jpeg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - shader - shadow cone 5.jpg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_soft_shadow_cone->setPrefix(QString());
        spinbox_soft_shadow_cone->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_volumetric->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Enables volumetric visibility of the light source with calculation of shadows on it. It can be used to simulate &quot;god rays&quot; effect.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_volumetric->setTitle(QCoreApplication::translate("cLightEditor", "Volumetric", nullptr));
#if QT_CONFIG(tooltip)
        logedit_volumetric_visibility->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Intensity of volumetric effect. </p><p>When effect is not visible try to increase intensity. If whole image is white, then decrease intensity.</p><p>To control quality of this effect change <span style=\" font-style:italic;\">Effects</span><span style=\" font-style:italic;\">/ Volumetric / Custom DE multiplier for volumetric effect</span> parameter (lower value - better quality).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_4->setText(QCoreApplication::translate("cLightEditor", "Visibility:", nullptr));
        groupBox_cone_options->setTitle(QCoreApplication::translate("cLightEditor", "Cone options", nullptr));
#if QT_CONFIG(tooltip)
        logedit_cone_angle->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Opening angle of conical shape of spot light</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_62->setText(QCoreApplication::translate("cLightEditor", "Opening angle", nullptr));
        label_64->setText(QCoreApplication::translate("cLightEditor", "Soft angle", nullptr));
#if QT_CONFIG(tooltip)
        logedit_cone_soft_angle->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Additional opening angle of conical shape of spot light with soft transition from full brightness to dark.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_projection_options->setTitle(QCoreApplication::translate("cLightEditor", "Projection options", nullptr));
#if QT_CONFIG(tooltip)
        text_file_texture->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Path to the light projection texture image. Acceptable formats are BMP, GIF, JPG, PNG</p><p>To use animated textures (image sequences), replace numbers by '%' symbol. Example: If sequence of images is as showed below: <br/>texture0001.jpg<br/>texture0002.jpg<br/>etc</p><p>Then use following file name: texture%%%%.jpg<br/>This tells the program to treat this as not a single image but as a sequence of images with 4 digit index.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_61->setText(QCoreApplication::translate("cLightEditor", "Texture path:", nullptr));
#if QT_CONFIG(tooltip)
        text_file_texture_alpha->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Path to an optional alpha mask texture. When &quot;Use texture alpha as mask&quot; is enabled, this image's brightness controls where the projection light is visible (white = full light, black = no light).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_alpha_texture->setText(QCoreApplication::translate("cLightEditor", "Alpha mask path:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_projection_vertical_angle->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Vertical opening angle of projected image </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_projection_horizonal_angle->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Horizontal opening angle of projected image </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_63->setText(QCoreApplication::translate("cLightEditor", "Horizontal opening angle", nullptr));
        label_65->setText(QCoreApplication::translate("cLightEditor", "Vertical opening angle", nullptr));
        label_repeat_mode->setText(QCoreApplication::translate("cLightEditor", "Repeat mode", nullptr));
        comboBox_projection_repeat_mode->setItemText(0, QCoreApplication::translate("cLightEditor", "Clamp", nullptr));
        comboBox_projection_repeat_mode->setItemText(1, QCoreApplication::translate("cLightEditor", "Repeat", nullptr));
        comboBox_projection_repeat_mode->setItemText(2, QCoreApplication::translate("cLightEditor", "Mirror", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_projection_repeat_mode->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Texture repeat mode: Clamp = no repeat with optional soft edge, Repeat = infinite tiling, Mirror = ping-pong tiling.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_soft_edge->setText(QCoreApplication::translate("cLightEditor", "Soft edge", nullptr));
#if QT_CONFIG(tooltip)
        logedit_projection_soft_edge->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Soft edge feather width. 0.0 = hard edges, 0.5 = maximum soft fade. Only applies in Clamp mode.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_texture_offset_x->setText(QCoreApplication::translate("cLightEditor", "Texture offset X", nullptr));
#if QT_CONFIG(tooltip)
        logedit_projection_texture_offset_x->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Horizontal offset of the projected texture in UV space.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_texture_offset_y->setText(QCoreApplication::translate("cLightEditor", "Texture offset Y", nullptr));
#if QT_CONFIG(tooltip)
        logedit_projection_texture_offset_y->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Vertical offset of the projected texture in UV space.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_texture_offset_z->setText(QCoreApplication::translate("cLightEditor", "Texture offset Z", nullptr));
#if QT_CONFIG(tooltip)
        logedit_projection_texture_offset_z->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Horizontal scale of the projected texture. 1.0 = original size.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_texture_scale_x->setText(QCoreApplication::translate("cLightEditor", "Texture scale X", nullptr));
#if QT_CONFIG(tooltip)
        logedit_projection_texture_scale_x->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Vertical scale of the projected texture. 1.0 = original size.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_texture_scale_y->setText(QCoreApplication::translate("cLightEditor", "Texture scale Y", nullptr));
#if QT_CONFIG(tooltip)
        logedit_projection_texture_scale_y->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Depth offset of the projected texture. Shifts the projection focus point along the light direction.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_texture_scale_z->setText(QCoreApplication::translate("cLightEditor", "Texture scale Z", nullptr));
#if QT_CONFIG(tooltip)
        logedit_projection_texture_scale_z->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Depth scale of the projected texture. Scales the projection focus along the light direction.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_texture_rotation_x->setText(QCoreApplication::translate("cLightEditor", "Texture rotation X", nullptr));
#if QT_CONFIG(tooltip)
        logedit_projection_texture_rotation_x->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Rotation of the projected texture around the light right axis (pitch) in degrees.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_texture_rotation_y->setText(QCoreApplication::translate("cLightEditor", "Texture rotation Y", nullptr));
#if QT_CONFIG(tooltip)
        logedit_projection_texture_rotation_y->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Rotation of the projected texture around the light top axis (yaw) in degrees.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_texture_rotation_z->setText(QCoreApplication::translate("cLightEditor", "Texture rotation Z", nullptr));
#if QT_CONFIG(tooltip)
        logedit_projection_texture_rotation_z->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Rotation of the projected texture around the light direction axis (roll) in degrees.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_projection_use_as_mask->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Use texture as intensity mask instead of color. Light color is preserved; texture brightness controls intensity.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_projection_use_as_mask->setText(QCoreApplication::translate("cLightEditor", "Use texture as mask", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_projection_use_alpha_as_mask->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Use texture alpha channel as intensity mask instead of color. Requires a PNG or image with alpha channel.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_projection_use_alpha_as_mask->setText(QCoreApplication::translate("cLightEditor", "Use texture alpha as mask", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_projection_use_texture_alpha_as_mask->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Use a separate alpha mask texture to control projection light visibility. The alpha mask path must be set above.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_projection_use_texture_alpha_as_mask->setText(QCoreApplication::translate("cLightEditor", "Use separate alpha mask texture", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_projection_invert_alpha_mask->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Invert the alpha mask. Black areas become fully lit and white areas become dark.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_projection_invert_alpha_mask->setText(QCoreApplication::translate("cLightEditor", "Invert alpha mask", nullptr));
        label_projection_intensity->setText(QCoreApplication::translate("cLightEditor", "Projection intensity", nullptr));
#if QT_CONFIG(tooltip)
        logedit_projection_intensity->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Intensity multiplier for the projection light. 1.0 = normal brightness, 0.0 = off, higher values make the projection brighter.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_projection_blend_mode->setText(QCoreApplication::translate("cLightEditor", "Blend mode", nullptr));
        comboBox_projection_blend_mode->setItemText(0, QCoreApplication::translate("cLightEditor", "Multiply", nullptr));
        comboBox_projection_blend_mode->setItemText(1, QCoreApplication::translate("cLightEditor", "Add", nullptr));
        comboBox_projection_blend_mode->setItemText(2, QCoreApplication::translate("cLightEditor", "Screen", nullptr));
        comboBox_projection_blend_mode->setItemText(3, QCoreApplication::translate("cLightEditor", "Overlay", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_projection_blend_mode->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Blend mode for projection texture with light color. Multiply = texture tints the light (default). Add = texture adds to light. Screen = soft addition. Overlay = contrast boosting.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_alpha_offset_x->setText(QCoreApplication::translate("cLightEditor", "Alpha offset X", nullptr));
#if QT_CONFIG(tooltip)
        logedit_alpha_texture_offset_x->setToolTip(QCoreApplication::translate("cLightEditor", "Horizontal offset of the alpha mask texture in UV space.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_alpha_offset_y->setText(QCoreApplication::translate("cLightEditor", "Alpha offset Y", nullptr));
#if QT_CONFIG(tooltip)
        logedit_alpha_texture_offset_y->setToolTip(QCoreApplication::translate("cLightEditor", "Vertical offset of the alpha mask texture in UV space.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_alpha_scale_x->setText(QCoreApplication::translate("cLightEditor", "Alpha scale X", nullptr));
#if QT_CONFIG(tooltip)
        logedit_alpha_texture_scale_x->setToolTip(QCoreApplication::translate("cLightEditor", "Horizontal scale of the alpha mask texture. 1.0 = original size.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_alpha_scale_y->setText(QCoreApplication::translate("cLightEditor", "Alpha scale Y", nullptr));
#if QT_CONFIG(tooltip)
        logedit_alpha_texture_scale_y->setToolTip(QCoreApplication::translate("cLightEditor", "Vertical scale of the alpha mask texture. 1.0 = original size.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_alpha_rotation_z->setText(QCoreApplication::translate("cLightEditor", "Alpha rotation Z", nullptr));
#if QT_CONFIG(tooltip)
        logedit_alpha_texture_rotation_z->setToolTip(QCoreApplication::translate("cLightEditor", "Rotation of the alpha mask texture around the light direction axis in degrees.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_alpha_repeat_mode->setText(QCoreApplication::translate("cLightEditor", "Alpha repeat mode", nullptr));
        comboBox_alpha_texture_repeat_mode->setItemText(0, QCoreApplication::translate("cLightEditor", "Clamp", nullptr));
        comboBox_alpha_texture_repeat_mode->setItemText(1, QCoreApplication::translate("cLightEditor", "Repeat", nullptr));
        comboBox_alpha_texture_repeat_mode->setItemText(2, QCoreApplication::translate("cLightEditor", "Mirror", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_alpha_texture_repeat_mode->setToolTip(QCoreApplication::translate("cLightEditor", "Alpha mask texture repeat mode.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_alpha_soft_edge->setText(QCoreApplication::translate("cLightEditor", "Alpha soft edge", nullptr));
#if QT_CONFIG(tooltip)
        logedit_alpha_texture_soft_edge->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Soft edge feather width for alpha mask texture. 0.0 = hard edges, 0.5 = maximum soft fade. Only applies in Clamp mode.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_beam_options->setTitle(QCoreApplication::translate("cLightEditor", "Beam options", nullptr));
        label_beam_radius->setText(QCoreApplication::translate("cLightEditor", "Beam radius", nullptr));
#if QT_CONFIG(tooltip)
        logedit_beam_radius->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Radius of the beam cylinder. 0.0 = thin line (original behavior). Larger values create a thicker, volumetric beam.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_beam_soft_edge->setText(QCoreApplication::translate("cLightEditor", "Beam soft edge", nullptr));
#if QT_CONFIG(tooltip)
        logedit_beam_soft_edge->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Softness of the beam edge. 0.0 = hard cutoff at radius, 1.0 = maximum softness (intensity fades from center to edge).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_beam_fade_in->setText(QCoreApplication::translate("cLightEditor", "Beam fade in", nullptr));
#if QT_CONFIG(tooltip)
        logedit_beam_fade_in->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Fade-in length from beam start (position), as fraction of total length. 0.0 = no fade, 1.0 = fade over entire length.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_beam_fade_out->setText(QCoreApplication::translate("cLightEditor", "Beam fade out", nullptr));
#if QT_CONFIG(tooltip)
        logedit_beam_fade_out->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Fade-out length from beam end (target), as fraction of total length. 0.0 = no fade, 1.0 = fade over entire length.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_spherical_texture->setTitle(QCoreApplication::translate("cLightEditor", "Spherical texture", nullptr));
        label_spherical_texture->setText(QCoreApplication::translate("cLightEditor", "Texture path:", nullptr));
#if QT_CONFIG(tooltip)
        text_file_texture_spherical->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Path to an equirectangular spherical texture image. The texture is mapped around the point light to create directional light patterns (e.g. softbox grid, window blinds).</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_spherical_intensity->setText(QCoreApplication::translate("cLightEditor", "Texture intensity", nullptr));
#if QT_CONFIG(tooltip)
        logedit_spherical_texture_intensity->setToolTip(QCoreApplication::translate("cLightEditor", "<html><head/><body><p>Intensity multiplier for the spherical texture. 1.0 = normal, 0.0 = off, higher values make the pattern stronger.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class cLightEditor: public Ui_cLightEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIGHT_EDITOR_H
