/********************************************************************************
** Form generated from reading UI file 'navigator_window.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAVIGATOR_WINDOW_H
#define UI_NAVIGATOR_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "dock_navigation.h"
#include "my_combo_box.h"
#include "src/rendered_image_widget.hpp"

QT_BEGIN_NAMESPACE

class Ui_cNavigatorWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBoxParameterSet;
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollAreaParameterSet;
    QWidget *scrollAreaParameterSetContents;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_navigator_options;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    MyComboBox *comboBox_navigator_preview_size;
    QLabel *label_2;
    MyComboBox *comboBox_navigator_preview_quality;
    QCheckBox *checkBox_navigator_shadows;
    QCheckBox *checkBox_navigator_reflections;
    QCheckBox *checkBox_navigator_volumetrics;
    QCheckBox *checkBox_navigator_monte_carlo;
    QCheckBox *checkBox_navigator_dark_glow;
    QSpacerItem *horizontalSpacer_2;
    RenderedImage *widgetRenderedImage;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_mouse_click_functions;
    MyComboBox *comboBox_mouse_click_function;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_5;
    QToolButton *toolButton_multiMode;
    QToolButton *toolButton_rotMode;
    QToolButton *toolButton_rollMode;
    QToolButton *toolButton_rotAroundMode;
    QToolButton *toolButton_moveMode;
    QToolButton *toolButton_preciseRotation;
    QSpacerItem *horizontalSpacer;
    QFrame *frameNavigationButtons;
    QVBoxLayout *verticalLayout_2;
    cDockNavigation *widgetNavigationButtons;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonUse;
    QPushButton *pushButtonUse_without_camera;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *cNavigatorWindow)
    {
        if (cNavigatorWindow->objectName().isEmpty())
            cNavigatorWindow->setObjectName(QString::fromUtf8("cNavigatorWindow"));
        cNavigatorWindow->resize(1903, 1152);
        verticalLayout = new QVBoxLayout(cNavigatorWindow);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        groupBoxParameterSet = new QGroupBox(cNavigatorWindow);
        groupBoxParameterSet->setObjectName(QString::fromUtf8("groupBoxParameterSet"));
        verticalLayout_4 = new QVBoxLayout(groupBoxParameterSet);
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        scrollAreaParameterSet = new QScrollArea(groupBoxParameterSet);
        scrollAreaParameterSet->setObjectName(QString::fromUtf8("scrollAreaParameterSet"));
        scrollAreaParameterSet->setWidgetResizable(true);
        scrollAreaParameterSetContents = new QWidget();
        scrollAreaParameterSetContents->setObjectName(QString::fromUtf8("scrollAreaParameterSetContents"));
        scrollAreaParameterSetContents->setGeometry(QRect(0, 0, 491, 1089));
        verticalLayout_3 = new QVBoxLayout(scrollAreaParameterSetContents);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        scrollAreaParameterSet->setWidget(scrollAreaParameterSetContents);

        verticalLayout_4->addWidget(scrollAreaParameterSet);


        horizontalLayout->addWidget(groupBoxParameterSet);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, -1, -1, -1);
        groupBox_navigator_options = new QGroupBox(cNavigatorWindow);
        groupBox_navigator_options->setObjectName(QString::fromUtf8("groupBox_navigator_options"));
        verticalLayout_6 = new QVBoxLayout(groupBox_navigator_options);
        verticalLayout_6->setSpacing(2);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(groupBox_navigator_options);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        comboBox_navigator_preview_size = new MyComboBox(groupBox_navigator_options);
        comboBox_navigator_preview_size->addItem(QString());
        comboBox_navigator_preview_size->addItem(QString());
        comboBox_navigator_preview_size->addItem(QString());
        comboBox_navigator_preview_size->setObjectName(QString::fromUtf8("comboBox_navigator_preview_size"));

        horizontalLayout_4->addWidget(comboBox_navigator_preview_size);

        label_2 = new QLabel(groupBox_navigator_options);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        comboBox_navigator_preview_quality = new MyComboBox(groupBox_navigator_options);
        comboBox_navigator_preview_quality->addItem(QString());
        comboBox_navigator_preview_quality->addItem(QString());
        comboBox_navigator_preview_quality->addItem(QString());
        comboBox_navigator_preview_quality->addItem(QString());
        comboBox_navigator_preview_quality->addItem(QString());
        comboBox_navigator_preview_quality->addItem(QString());
        comboBox_navigator_preview_quality->addItem(QString());
        comboBox_navigator_preview_quality->setObjectName(QString::fromUtf8("comboBox_navigator_preview_quality"));

        horizontalLayout_4->addWidget(comboBox_navigator_preview_quality);

        checkBox_navigator_shadows = new QCheckBox(groupBox_navigator_options);
        checkBox_navigator_shadows->setObjectName(QString::fromUtf8("checkBox_navigator_shadows"));

        horizontalLayout_4->addWidget(checkBox_navigator_shadows);

        checkBox_navigator_reflections = new QCheckBox(groupBox_navigator_options);
        checkBox_navigator_reflections->setObjectName(QString::fromUtf8("checkBox_navigator_reflections"));

        horizontalLayout_4->addWidget(checkBox_navigator_reflections);

        checkBox_navigator_volumetrics = new QCheckBox(groupBox_navigator_options);
        checkBox_navigator_volumetrics->setObjectName(QString::fromUtf8("checkBox_navigator_volumetrics"));

        horizontalLayout_4->addWidget(checkBox_navigator_volumetrics);

        checkBox_navigator_monte_carlo = new QCheckBox(groupBox_navigator_options);
        checkBox_navigator_monte_carlo->setObjectName(QString::fromUtf8("checkBox_navigator_monte_carlo"));

        horizontalLayout_4->addWidget(checkBox_navigator_monte_carlo);

        checkBox_navigator_dark_glow = new QCheckBox(groupBox_navigator_options);
        checkBox_navigator_dark_glow->setObjectName(QString::fromUtf8("checkBox_navigator_dark_glow"));

        horizontalLayout_4->addWidget(checkBox_navigator_dark_glow);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout_6->addLayout(horizontalLayout_4);


        verticalLayout_5->addWidget(groupBox_navigator_options);

        widgetRenderedImage = new RenderedImage(cNavigatorWindow);
        widgetRenderedImage->setObjectName(QString::fromUtf8("widgetRenderedImage"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widgetRenderedImage->sizePolicy().hasHeightForWidth());
        widgetRenderedImage->setSizePolicy(sizePolicy);
        widgetRenderedImage->setMinimumSize(QSize(800, 600));

        verticalLayout_5->addWidget(widgetRenderedImage);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_mouse_click_functions = new QLabel(cNavigatorWindow);
        label_mouse_click_functions->setObjectName(QString::fromUtf8("label_mouse_click_functions"));

        horizontalLayout_3->addWidget(label_mouse_click_functions);

        comboBox_mouse_click_function = new MyComboBox(cNavigatorWindow);
        comboBox_mouse_click_function->addItem(QString());
        comboBox_mouse_click_function->setObjectName(QString::fromUtf8("comboBox_mouse_click_function"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboBox_mouse_click_function->sizePolicy().hasHeightForWidth());
        comboBox_mouse_click_function->setSizePolicy(sizePolicy1);
        comboBox_mouse_click_function->setMinimumSize(QSize(150, 0));

        horizontalLayout_3->addWidget(comboBox_mouse_click_function);

        frame = new QFrame(cNavigatorWindow);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_5 = new QHBoxLayout(frame);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(2, 2, 2, 2);
        toolButton_multiMode = new QToolButton(frame);
        toolButton_multiMode->setObjectName(QString::fromUtf8("toolButton_multiMode"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/navigation/icons/auto.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_multiMode->setIcon(icon);
        toolButton_multiMode->setCheckable(true);
        toolButton_multiMode->setChecked(true);
        toolButton_multiMode->setAutoExclusive(true);

        horizontalLayout_5->addWidget(toolButton_multiMode);

        toolButton_rotMode = new QToolButton(frame);
        toolButton_rotMode->setObjectName(QString::fromUtf8("toolButton_rotMode"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/navigation/icons/rot.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_rotMode->setIcon(icon1);
        toolButton_rotMode->setCheckable(true);
        toolButton_rotMode->setAutoExclusive(true);

        horizontalLayout_5->addWidget(toolButton_rotMode);

        toolButton_rollMode = new QToolButton(frame);
        toolButton_rollMode->setObjectName(QString::fromUtf8("toolButton_rollMode"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/navigation/icons/roll.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_rollMode->setIcon(icon2);
        toolButton_rollMode->setCheckable(true);
        toolButton_rollMode->setAutoExclusive(true);

        horizontalLayout_5->addWidget(toolButton_rollMode);

        toolButton_rotAroundMode = new QToolButton(frame);
        toolButton_rotAroundMode->setObjectName(QString::fromUtf8("toolButton_rotAroundMode"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/navigation/icons/rot-around.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_rotAroundMode->setIcon(icon3);
        toolButton_rotAroundMode->setCheckable(true);
        toolButton_rotAroundMode->setAutoExclusive(true);

        horizontalLayout_5->addWidget(toolButton_rotAroundMode);

        toolButton_moveMode = new QToolButton(frame);
        toolButton_moveMode->setObjectName(QString::fromUtf8("toolButton_moveMode"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/navigation/icons/cross.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_moveMode->setIcon(icon4);
        toolButton_moveMode->setCheckable(true);
        toolButton_moveMode->setAutoExclusive(true);

        horizontalLayout_5->addWidget(toolButton_moveMode);


        horizontalLayout_3->addWidget(frame);

        toolButton_preciseRotation = new QToolButton(cNavigatorWindow);
        toolButton_preciseRotation->setObjectName(QString::fromUtf8("toolButton_preciseRotation"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/navigation/icons/precise.svg"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_preciseRotation->setIcon(icon5);
        toolButton_preciseRotation->setCheckable(true);

        horizontalLayout_3->addWidget(toolButton_preciseRotation);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout_5->addLayout(horizontalLayout_3);

        verticalLayout_5->setStretch(1, 1);

        horizontalLayout->addLayout(verticalLayout_5);

        frameNavigationButtons = new QFrame(cNavigatorWindow);
        frameNavigationButtons->setObjectName(QString::fromUtf8("frameNavigationButtons"));
        frameNavigationButtons->setFrameShape(QFrame::StyledPanel);
        frameNavigationButtons->setFrameShadow(QFrame::Raised);
        verticalLayout_2 = new QVBoxLayout(frameNavigationButtons);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        widgetNavigationButtons = new cDockNavigation(frameNavigationButtons);
        widgetNavigationButtons->setObjectName(QString::fromUtf8("widgetNavigationButtons"));

        verticalLayout_2->addWidget(widgetNavigationButtons);


        horizontalLayout->addWidget(frameNavigationButtons);

        horizontalLayout->setStretch(0, 4);
        horizontalLayout->setStretch(1, 10);
        horizontalLayout->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButtonUse = new QPushButton(cNavigatorWindow);
        pushButtonUse->setObjectName(QString::fromUtf8("pushButtonUse"));

        horizontalLayout_2->addWidget(pushButtonUse);

        pushButtonUse_without_camera = new QPushButton(cNavigatorWindow);
        pushButtonUse_without_camera->setObjectName(QString::fromUtf8("pushButtonUse_without_camera"));

        horizontalLayout_2->addWidget(pushButtonUse_without_camera);

        pushButtonCancel = new QPushButton(cNavigatorWindow);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout_2->addWidget(pushButtonCancel);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalLayout->setStretch(0, 1);

        retranslateUi(cNavigatorWindow);

        QMetaObject::connectSlotsByName(cNavigatorWindow);
    } // setupUi

    void retranslateUi(QDialog *cNavigatorWindow)
    {
        cNavigatorWindow->setWindowTitle(QCoreApplication::translate("cNavigatorWindow", "Dialog", nullptr));
        groupBoxParameterSet->setTitle(QCoreApplication::translate("cNavigatorWindow", "Edited parameter set", nullptr));
        groupBox_navigator_options->setTitle(QCoreApplication::translate("cNavigatorWindow", "Preview quality options", nullptr));
        label->setText(QCoreApplication::translate("cNavigatorWindow", "Size", nullptr));
        comboBox_navigator_preview_size->setItemText(0, QCoreApplication::translate("cNavigatorWindow", "Small", nullptr));
        comboBox_navigator_preview_size->setItemText(1, QCoreApplication::translate("cNavigatorWindow", "Medium", nullptr));
        comboBox_navigator_preview_size->setItemText(2, QCoreApplication::translate("cNavigatorWindow", "Big", nullptr));

        label_2->setText(QCoreApplication::translate("cNavigatorWindow", "Quality", nullptr));
        comboBox_navigator_preview_quality->setItemText(0, QCoreApplication::translate("cNavigatorWindow", "Auto", nullptr));
        comboBox_navigator_preview_quality->setItemText(1, QCoreApplication::translate("cNavigatorWindow", "1", nullptr));
        comboBox_navigator_preview_quality->setItemText(2, QCoreApplication::translate("cNavigatorWindow", "1/2", nullptr));
        comboBox_navigator_preview_quality->setItemText(3, QCoreApplication::translate("cNavigatorWindow", "1/4", nullptr));
        comboBox_navigator_preview_quality->setItemText(4, QCoreApplication::translate("cNavigatorWindow", "1/8", nullptr));
        comboBox_navigator_preview_quality->setItemText(5, QCoreApplication::translate("cNavigatorWindow", "1/16", nullptr));
        comboBox_navigator_preview_quality->setItemText(6, QCoreApplication::translate("cNavigatorWindow", "1/32", nullptr));

#if QT_CONFIG(tooltip)
        checkBox_navigator_shadows->setToolTip(QCoreApplication::translate("cNavigatorWindow", "Enable shadow calculation in the preview", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_navigator_shadows->setText(QCoreApplication::translate("cNavigatorWindow", "Shadows", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_navigator_reflections->setToolTip(QCoreApplication::translate("cNavigatorWindow", "Enable reflections and transparency calculation in the preview", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_navigator_reflections->setText(QCoreApplication::translate("cNavigatorWindow", "Reflectons", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_navigator_volumetrics->setToolTip(QCoreApplication::translate("cNavigatorWindow", "Enable volumetric effects calculation in the preview", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_navigator_volumetrics->setText(QCoreApplication::translate("cNavigatorWindow", "Volumetrics", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_navigator_monte_carlo->setToolTip(QCoreApplication::translate("cNavigatorWindow", "Enable volumetric effects calculation in the preview", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_navigator_monte_carlo->setText(QCoreApplication::translate("cNavigatorWindow", "Monte Carlo", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_navigator_dark_glow->setToolTip(QCoreApplication::translate("cNavigatorWindow", "<html><head/><body><p>Disable shadows, reflections and volumetric effects, and enable fast dark glow effect which improves perception of depth.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_navigator_dark_glow->setText(QCoreApplication::translate("cNavigatorWindow", "Dark glow", nullptr));
        label_mouse_click_functions->setText(QCoreApplication::translate("cNavigatorWindow", "Mouse click function:", nullptr));
        comboBox_mouse_click_function->setItemText(0, QCoreApplication::translate("cNavigatorWindow", "No action", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_mouse_click_function->setToolTip(QCoreApplication::translate("cNavigatorWindow", "<html><head/><body><p>Selection for action which will be executed after clicking on the image</p><ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; -qt-list-indent: 1;\"><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">No action - blocks functionality of mouse pointer</li><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Move the camera - moves the camera or target (depends on movement and rotation mode)</li><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Set fog visibility - sets visibility distance for basic fog effect</li><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Set DOF focus - sets object which will appear in focus</li><li style=\" margin-top:12px; margin-bottom:0px; margin"
                        "-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Get Julia constant - gets value of constant for Julia fractal</li><li style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Place light #n - places light in selected place (mouse wheel controls distance from fractal) </li></ul></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        toolButton_multiMode->setToolTip(QCoreApplication::translate("cNavigatorWindow", "Auto - Rotation mode depends on used button", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_multiMode->setText(QCoreApplication::translate("cNavigatorWindow", "Multi", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_rotMode->setToolTip(QCoreApplication::translate("cNavigatorWindow", "Rotate camera", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_rotMode->setText(QCoreApplication::translate("cNavigatorWindow", "Rot", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_rollMode->setToolTip(QCoreApplication::translate("cNavigatorWindow", "Roll camera", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_rollMode->setText(QCoreApplication::translate("cNavigatorWindow", "Roll", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_rotAroundMode->setToolTip(QCoreApplication::translate("cNavigatorWindow", "Rotate around indicated point", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_rotAroundMode->setText(QCoreApplication::translate("cNavigatorWindow", "RotA", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_moveMode->setToolTip(QCoreApplication::translate("cNavigatorWindow", "Move camera", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_moveMode->setText(QCoreApplication::translate("cNavigatorWindow", "Move", nullptr));
#if QT_CONFIG(tooltip)
        toolButton_preciseRotation->setToolTip(QCoreApplication::translate("cNavigatorWindow", "Precise rotations", nullptr));
#endif // QT_CONFIG(tooltip)
        toolButton_preciseRotation->setText(QCoreApplication::translate("cNavigatorWindow", "P", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonUse->setToolTip(QCoreApplication::translate("cNavigatorWindow", "Closes the Navigator and copies actual parameters to the main window", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonUse->setText(QCoreApplication::translate("cNavigatorWindow", "Use in main window", nullptr));
#if QT_CONFIG(tooltip)
        pushButtonUse_without_camera->setToolTip(QCoreApplication::translate("cNavigatorWindow", "Closes the Navigator and copies actual parameters to the main window. It does not copy camera position and rotation.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButtonUse_without_camera->setText(QCoreApplication::translate("cNavigatorWindow", "Use in main window (without camera)", nullptr));
        pushButtonCancel->setText(QCoreApplication::translate("cNavigatorWindow", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cNavigatorWindow: public Ui_cNavigatorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAVIGATOR_WINDOW_H
