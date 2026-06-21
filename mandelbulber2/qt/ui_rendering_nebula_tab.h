/********************************************************************************
** Form generated from reading UI file 'rendering_nebula_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERING_NEBULA_TAB_H
#define UI_RENDERING_NEBULA_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "gradient_edit_widget.h"
#include "my_check_box.h"
#include "my_combo_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cRenderingNebulaTab
{
public:
    QVBoxLayout *verticalLayout_3;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_16;
    MyGroupBox *groupCheck_nebula_mode;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_nebula_auto_brightness_dark;
    QPushButton *pushButton_nebula_auto_brightness_medium;
    QPushButton *pushButton_nebula_auto_brightness_bright;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    MyCheckBox *checkBox_nebula_inner_enabled;
    MyLineEdit *logedit_nebula_samples_per_pixel;
    QLabel *label;
    MyCheckBox *checkBox_nebula_outer_enabled;
    MyComboBox *comboBox_nebula_color_mixing;
    QLabel *label_4;
    QLabel *label_2;
    MyLineEdit *logedit_nebula_brightness;
    MySpinBox *spinboxInt_nebula_min_iteration;
    MyCheckBox *checkBox_nebula_constant_brightness;
    MyGroupBox *groupCheck_nebula_x_axis_colors_enabled;
    QVBoxLayout *verticalLayout_9;
    cGradientEditWidget *colorpalette_nebula_x_axis_colors;
    MyGroupBox *groupCheck_nebula_y_axis_colors_enabled;
    QVBoxLayout *verticalLayout_10;
    cGradientEditWidget *colorpalette_nebula_y_axis_colors;
    MyGroupBox *groupCheck_nebula_z_axis_colors_enabled;
    QVBoxLayout *verticalLayout_11;
    cGradientEditWidget *colorpalette_nebula_z_axis_colors;
    MyGroupBox *groupCheck_nebula_iterations_colors_enabled;
    QVBoxLayout *verticalLayout_12;
    cGradientEditWidget *colorpalette_nebula_iterations_colors;
    MyGroupBox *groupCheck_nebula_grid_domain_enabled;
    QGridLayout *gridLayout_4;
    QLabel *label_7;
    QLabel *label_6;
    QLabel *label_5;
    MyLineEdit *logedit_nebula_x_grid_size;
    MyLineEdit *logedit_nebula_y_grid_size;
    MyLineEdit *logedit_nebula_z_grid_size;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QWidget *cRenderingNebulaTab)
    {
        if (cRenderingNebulaTab->objectName().isEmpty())
            cRenderingNebulaTab->setObjectName(QString::fromUtf8("cRenderingNebulaTab"));
        verticalLayout_3 = new QVBoxLayout(cRenderingNebulaTab);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        scrollArea_2 = new QScrollArea(cRenderingNebulaTab);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 417, 1082));
        verticalLayout_16 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_16->setSpacing(2);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        verticalLayout_16->setContentsMargins(2, 2, 2, 2);
        groupCheck_nebula_mode = new MyGroupBox(scrollAreaWidgetContents_2);
        groupCheck_nebula_mode->setObjectName(QString::fromUtf8("groupCheck_nebula_mode"));
        groupCheck_nebula_mode->setCheckable(true);
        verticalLayout_8 = new QVBoxLayout(groupCheck_nebula_mode);
        verticalLayout_8->setSpacing(2);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(2, 2, 2, 2);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_nebula_auto_brightness_dark = new QPushButton(groupCheck_nebula_mode);
        pushButton_nebula_auto_brightness_dark->setObjectName(QString::fromUtf8("pushButton_nebula_auto_brightness_dark"));

        horizontalLayout->addWidget(pushButton_nebula_auto_brightness_dark);

        pushButton_nebula_auto_brightness_medium = new QPushButton(groupCheck_nebula_mode);
        pushButton_nebula_auto_brightness_medium->setObjectName(QString::fromUtf8("pushButton_nebula_auto_brightness_medium"));

        horizontalLayout->addWidget(pushButton_nebula_auto_brightness_medium);

        pushButton_nebula_auto_brightness_bright = new QPushButton(groupCheck_nebula_mode);
        pushButton_nebula_auto_brightness_bright->setObjectName(QString::fromUtf8("pushButton_nebula_auto_brightness_bright"));

        horizontalLayout->addWidget(pushButton_nebula_auto_brightness_bright);


        verticalLayout_8->addLayout(horizontalLayout);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 5, -1, -1);
        label_3 = new QLabel(groupCheck_nebula_mode);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 3, 0, 1, 1);

        checkBox_nebula_inner_enabled = new MyCheckBox(groupCheck_nebula_mode);
        checkBox_nebula_inner_enabled->setObjectName(QString::fromUtf8("checkBox_nebula_inner_enabled"));

        gridLayout_3->addWidget(checkBox_nebula_inner_enabled, 5, 0, 1, 2);

        logedit_nebula_samples_per_pixel = new MyLineEdit(groupCheck_nebula_mode);
        logedit_nebula_samples_per_pixel->setObjectName(QString::fromUtf8("logedit_nebula_samples_per_pixel"));

        gridLayout_3->addWidget(logedit_nebula_samples_per_pixel, 2, 1, 1, 1);

        label = new QLabel(groupCheck_nebula_mode);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 1, 0, 1, 1);

        checkBox_nebula_outer_enabled = new MyCheckBox(groupCheck_nebula_mode);
        checkBox_nebula_outer_enabled->setObjectName(QString::fromUtf8("checkBox_nebula_outer_enabled"));

        gridLayout_3->addWidget(checkBox_nebula_outer_enabled, 4, 0, 1, 2);

        comboBox_nebula_color_mixing = new MyComboBox(groupCheck_nebula_mode);
        comboBox_nebula_color_mixing->addItem(QString());
        comboBox_nebula_color_mixing->addItem(QString());
        comboBox_nebula_color_mixing->addItem(QString());
        comboBox_nebula_color_mixing->setObjectName(QString::fromUtf8("comboBox_nebula_color_mixing"));
        comboBox_nebula_color_mixing->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_nebula_color_mixing->sizePolicy().hasHeightForWidth());
        comboBox_nebula_color_mixing->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(comboBox_nebula_color_mixing, 6, 1, 1, 1);

        label_4 = new QLabel(groupCheck_nebula_mode);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_3->addWidget(label_4, 6, 0, 1, 1);

        label_2 = new QLabel(groupCheck_nebula_mode);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 2, 0, 1, 1);

        logedit_nebula_brightness = new MyLineEdit(groupCheck_nebula_mode);
        logedit_nebula_brightness->setObjectName(QString::fromUtf8("logedit_nebula_brightness"));

        gridLayout_3->addWidget(logedit_nebula_brightness, 1, 1, 1, 1);

        spinboxInt_nebula_min_iteration = new MySpinBox(groupCheck_nebula_mode);
        spinboxInt_nebula_min_iteration->setObjectName(QString::fromUtf8("spinboxInt_nebula_min_iteration"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinboxInt_nebula_min_iteration->sizePolicy().hasHeightForWidth());
        spinboxInt_nebula_min_iteration->setSizePolicy(sizePolicy1);
        spinboxInt_nebula_min_iteration->setMinimum(0);
        spinboxInt_nebula_min_iteration->setMaximum(9999);

        gridLayout_3->addWidget(spinboxInt_nebula_min_iteration, 3, 1, 1, 1);

        checkBox_nebula_constant_brightness = new MyCheckBox(groupCheck_nebula_mode);
        checkBox_nebula_constant_brightness->setObjectName(QString::fromUtf8("checkBox_nebula_constant_brightness"));
        checkBox_nebula_constant_brightness->setAcceptDrops(true);

        gridLayout_3->addWidget(checkBox_nebula_constant_brightness, 0, 0, 1, 2);


        verticalLayout_8->addLayout(gridLayout_3);

        groupCheck_nebula_x_axis_colors_enabled = new MyGroupBox(groupCheck_nebula_mode);
        groupCheck_nebula_x_axis_colors_enabled->setObjectName(QString::fromUtf8("groupCheck_nebula_x_axis_colors_enabled"));
        groupCheck_nebula_x_axis_colors_enabled->setCheckable(true);
        verticalLayout_9 = new QVBoxLayout(groupCheck_nebula_x_axis_colors_enabled);
        verticalLayout_9->setSpacing(2);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_9->setContentsMargins(2, 2, 2, 2);
        colorpalette_nebula_x_axis_colors = new cGradientEditWidget(groupCheck_nebula_x_axis_colors_enabled);
        colorpalette_nebula_x_axis_colors->setObjectName(QString::fromUtf8("colorpalette_nebula_x_axis_colors"));

        verticalLayout_9->addWidget(colorpalette_nebula_x_axis_colors);


        verticalLayout_8->addWidget(groupCheck_nebula_x_axis_colors_enabled);

        groupCheck_nebula_y_axis_colors_enabled = new MyGroupBox(groupCheck_nebula_mode);
        groupCheck_nebula_y_axis_colors_enabled->setObjectName(QString::fromUtf8("groupCheck_nebula_y_axis_colors_enabled"));
        groupCheck_nebula_y_axis_colors_enabled->setCheckable(true);
        verticalLayout_10 = new QVBoxLayout(groupCheck_nebula_y_axis_colors_enabled);
        verticalLayout_10->setSpacing(2);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        verticalLayout_10->setContentsMargins(2, 2, 2, 2);
        colorpalette_nebula_y_axis_colors = new cGradientEditWidget(groupCheck_nebula_y_axis_colors_enabled);
        colorpalette_nebula_y_axis_colors->setObjectName(QString::fromUtf8("colorpalette_nebula_y_axis_colors"));

        verticalLayout_10->addWidget(colorpalette_nebula_y_axis_colors);


        verticalLayout_8->addWidget(groupCheck_nebula_y_axis_colors_enabled);

        groupCheck_nebula_z_axis_colors_enabled = new MyGroupBox(groupCheck_nebula_mode);
        groupCheck_nebula_z_axis_colors_enabled->setObjectName(QString::fromUtf8("groupCheck_nebula_z_axis_colors_enabled"));
        groupCheck_nebula_z_axis_colors_enabled->setCheckable(true);
        verticalLayout_11 = new QVBoxLayout(groupCheck_nebula_z_axis_colors_enabled);
        verticalLayout_11->setSpacing(2);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalLayout_11->setContentsMargins(2, 2, 2, 2);
        colorpalette_nebula_z_axis_colors = new cGradientEditWidget(groupCheck_nebula_z_axis_colors_enabled);
        colorpalette_nebula_z_axis_colors->setObjectName(QString::fromUtf8("colorpalette_nebula_z_axis_colors"));

        verticalLayout_11->addWidget(colorpalette_nebula_z_axis_colors);


        verticalLayout_8->addWidget(groupCheck_nebula_z_axis_colors_enabled);

        groupCheck_nebula_iterations_colors_enabled = new MyGroupBox(groupCheck_nebula_mode);
        groupCheck_nebula_iterations_colors_enabled->setObjectName(QString::fromUtf8("groupCheck_nebula_iterations_colors_enabled"));
        groupCheck_nebula_iterations_colors_enabled->setCheckable(true);
        verticalLayout_12 = new QVBoxLayout(groupCheck_nebula_iterations_colors_enabled);
        verticalLayout_12->setSpacing(2);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(2, 2, 2, 2);
        colorpalette_nebula_iterations_colors = new cGradientEditWidget(groupCheck_nebula_iterations_colors_enabled);
        colorpalette_nebula_iterations_colors->setObjectName(QString::fromUtf8("colorpalette_nebula_iterations_colors"));

        verticalLayout_12->addWidget(colorpalette_nebula_iterations_colors);


        verticalLayout_8->addWidget(groupCheck_nebula_iterations_colors_enabled);

        groupCheck_nebula_grid_domain_enabled = new MyGroupBox(groupCheck_nebula_mode);
        groupCheck_nebula_grid_domain_enabled->setObjectName(QString::fromUtf8("groupCheck_nebula_grid_domain_enabled"));
        groupCheck_nebula_grid_domain_enabled->setCheckable(true);
        gridLayout_4 = new QGridLayout(groupCheck_nebula_grid_domain_enabled);
        gridLayout_4->setSpacing(2);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setContentsMargins(2, 2, 2, 2);
        label_7 = new QLabel(groupCheck_nebula_grid_domain_enabled);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_4->addWidget(label_7, 2, 0, 1, 1);

        label_6 = new QLabel(groupCheck_nebula_grid_domain_enabled);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_4->addWidget(label_6, 1, 0, 1, 1);

        label_5 = new QLabel(groupCheck_nebula_grid_domain_enabled);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_4->addWidget(label_5, 0, 0, 1, 1);

        logedit_nebula_x_grid_size = new MyLineEdit(groupCheck_nebula_grid_domain_enabled);
        logedit_nebula_x_grid_size->setObjectName(QString::fromUtf8("logedit_nebula_x_grid_size"));

        gridLayout_4->addWidget(logedit_nebula_x_grid_size, 0, 1, 1, 1);

        logedit_nebula_y_grid_size = new MyLineEdit(groupCheck_nebula_grid_domain_enabled);
        logedit_nebula_y_grid_size->setObjectName(QString::fromUtf8("logedit_nebula_y_grid_size"));

        gridLayout_4->addWidget(logedit_nebula_y_grid_size, 1, 1, 1, 1);

        logedit_nebula_z_grid_size = new MyLineEdit(groupCheck_nebula_grid_domain_enabled);
        logedit_nebula_z_grid_size->setObjectName(QString::fromUtf8("logedit_nebula_z_grid_size"));

        gridLayout_4->addWidget(logedit_nebula_z_grid_size, 2, 1, 1, 1);


        verticalLayout_8->addWidget(groupCheck_nebula_grid_domain_enabled);


        verticalLayout_16->addWidget(groupCheck_nebula_mode);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_16->addItem(verticalSpacer_3);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout_3->addWidget(scrollArea_2);


        retranslateUi(cRenderingNebulaTab);

        QMetaObject::connectSlotsByName(cRenderingNebulaTab);
    } // setupUi

    void retranslateUi(QWidget *cRenderingNebulaTab)
    {
#if QT_CONFIG(tooltip)
        groupCheck_nebula_mode->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "Enables rendering of nebula-style fractals, allowing for volumetric and cloud-like effects with additional controls for brightness and color.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_nebula_mode->setTitle(QCoreApplication::translate("cRenderingNebulaTab", "Nebula fractals", nullptr));
        pushButton_nebula_auto_brightness_dark->setText(QCoreApplication::translate("cRenderingNebulaTab", "Auto\n"
"dark", nullptr));
        pushButton_nebula_auto_brightness_medium->setText(QCoreApplication::translate("cRenderingNebulaTab", "Auto\n"
"medium", nullptr));
        pushButton_nebula_auto_brightness_bright->setText(QCoreApplication::translate("cRenderingNebulaTab", "Auto\n"
"bright", nullptr));
        label_3->setText(QCoreApplication::translate("cRenderingNebulaTab", "Min. iteration to draw:", nullptr));
        checkBox_nebula_inner_enabled->setText(QCoreApplication::translate("cRenderingNebulaTab", "Inner fractal iterations", nullptr));
#if QT_CONFIG(tooltip)
        logedit_nebula_samples_per_pixel->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "Number of samples per pixel for nebula rendering. Higher values reduce noise but increase rendering time.", nullptr));
#endif // QT_CONFIG(tooltip)
        label->setText(QCoreApplication::translate("cRenderingNebulaTab", "Brightness:", nullptr));
        checkBox_nebula_outer_enabled->setText(QCoreApplication::translate("cRenderingNebulaTab", "Outer fractal iterations", nullptr));
        comboBox_nebula_color_mixing->setItemText(0, QCoreApplication::translate("cRenderingNebulaTab", "Lighten", nullptr));
        comboBox_nebula_color_mixing->setItemText(1, QCoreApplication::translate("cRenderingNebulaTab", "Darken", nullptr));
        comboBox_nebula_color_mixing->setItemText(2, QCoreApplication::translate("cRenderingNebulaTab", "Darken by brighness", nullptr));

        label_4->setText(QCoreApplication::translate("cRenderingNebulaTab", "Color mining:", nullptr));
        label_2->setText(QCoreApplication::translate("cRenderingNebulaTab", "Number of samples per pixel:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_nebula_brightness->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "<html><body>Sets the brightness of the nebula effect. Use the auto buttons to adjust based on current image brightness.</body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinboxInt_nebula_min_iteration->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "Minimum iteration count required to draw nebula pixels. Increase to ignore low-iteration regions.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_nebula_constant_brightness->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "<html><head/><body><p>It tries to keep image brighness constant.</p><p>It is not recommended for animations because can cause unintended flickering.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_nebula_constant_brightness->setText(QCoreApplication::translate("cRenderingNebulaTab", "Constant brightness mode", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_nebula_x_axis_colors_enabled->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "Enable and configure a color gradient for the nebula based on the X axis position.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_nebula_x_axis_colors_enabled->setTitle(QCoreApplication::translate("cRenderingNebulaTab", "X axis colors", nullptr));
#if QT_CONFIG(tooltip)
        colorpalette_nebula_x_axis_colors->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "<html><head/><body><p>Gradient which defines the colors of the fractal surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_nebula_y_axis_colors_enabled->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "Enable and configure a color gradient for the nebula based on the Y axis position.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_nebula_y_axis_colors_enabled->setTitle(QCoreApplication::translate("cRenderingNebulaTab", "Y axis colors", nullptr));
#if QT_CONFIG(tooltip)
        colorpalette_nebula_y_axis_colors->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "<html><head/><body><p>Gradient which defines the colors of the fractal surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_nebula_z_axis_colors_enabled->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "Enable and configure a color gradient for the nebula based on the Z axis position.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_nebula_z_axis_colors_enabled->setTitle(QCoreApplication::translate("cRenderingNebulaTab", "Z axis colors", nullptr));
#if QT_CONFIG(tooltip)
        colorpalette_nebula_z_axis_colors->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "<html><head/><body><p>Gradient which defines the colors of the fractal surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_nebula_iterations_colors_enabled->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "Enable and configure a color gradient for the nebula based on the number of fractal iterations.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_nebula_iterations_colors_enabled->setTitle(QCoreApplication::translate("cRenderingNebulaTab", "Colors of iterations", nullptr));
#if QT_CONFIG(tooltip)
        colorpalette_nebula_iterations_colors->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "<html><head/><body><p>Gradient which defines the colors of the fractal surface.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_nebula_grid_domain_enabled->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "Enable grid-based domain calculation for the nebula, allowing control over grid spacing along each axis.", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_nebula_grid_domain_enabled->setTitle(QCoreApplication::translate("cRenderingNebulaTab", "Domain as grid", nullptr));
        label_7->setText(QCoreApplication::translate("cRenderingNebulaTab", "Grid spacing z:", nullptr));
        label_6->setText(QCoreApplication::translate("cRenderingNebulaTab", "Grid spacing y:", nullptr));
        label_5->setText(QCoreApplication::translate("cRenderingNebulaTab", "Grid spacing x:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_nebula_x_grid_size->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "Size of the grid along the X axis for nebula domain calculation.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_nebula_y_grid_size->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "Size of the grid along the Y axis for nebula domain calculation.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        logedit_nebula_z_grid_size->setToolTip(QCoreApplication::translate("cRenderingNebulaTab", "Size of the grid along the Z axis for nebula domain calculation.", nullptr));
#endif // QT_CONFIG(tooltip)
        (void)cRenderingNebulaTab;
    } // retranslateUi

};

namespace Ui {
    class cRenderingNebulaTab: public Ui_cRenderingNebulaTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERING_NEBULA_TAB_H
