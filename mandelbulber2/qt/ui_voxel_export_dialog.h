/********************************************************************************
** Form generated from reading UI file 'voxel_export_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VOXEL_EXPORT_DIALOG_H
#define UI_VOXEL_EXPORT_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_check_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_progress_bar.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cVoxelExportDialog
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    MyLineEdit *text_voxel_image_path;
    QPushButton *pushButton_select_image_path;
    QLabel *label;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_2;
    MySpinBox *spinboxInt_voxel_max_iter;
    QLabel *label_5;
    MyCheckBox *checkBox_voxel_greyscale_iterations;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_3;
    QLabel *label_6;
    MySpinBox *spinboxInt_voxel_samples_x;
    QLabel *label_7;
    MySpinBox *spinboxInt_voxel_samples_y;
    QLabel *label_8;
    MySpinBox *spinboxInt_voxel_samples_z;
    MyGroupBox *groupCheck_voxel_custom_limit_enabled;
    QVBoxLayout *verticalLayout_45;
    QGridLayout *gridLayout_21;
    MyLineEdit *vect3_voxel_limit_max_z;
    QLabel *label_114;
    MyLineEdit *vect3_voxel_limit_min_z;
    QLabel *label_110;
    MyLineEdit *vect3_voxel_limit_max_x;
    MyLineEdit *vect3_voxel_limit_max_y;
    MyLineEdit *vect3_voxel_limit_min_x;
    QLabel *label_111;
    MyLineEdit *vect3_voxel_limit_min_y;
    QLabel *label_112;
    QLabel *label_109;
    QLabel *label_117;
    QLabel *label_118;
    QLabel *label_119;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_start_render_layers;
    QPushButton *pushButton_stop_render_layers;
    QPushButton *pushButton_show_layers;
    MyProgressBar *progressBar;
    QLabel *label_info;
    MyGroupBox *groupCheck_voxel_show_information;
    QVBoxLayout *verticalLayout_voxel_show_information;
    QLabel *label_voxel_information;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *cVoxelExportDialog)
    {
        if (cVoxelExportDialog->objectName().isEmpty())
            cVoxelExportDialog->setObjectName(QString::fromUtf8("cVoxelExportDialog"));
        cVoxelExportDialog->resize(720, 1149);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/system/icons/layer.png"), QSize(), QIcon::Normal, QIcon::Off);
        cVoxelExportDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(cVoxelExportDialog);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        scrollArea = new QScrollArea(cVoxelExportDialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 712, 1141));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(2, 2, 2, 2);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        text_voxel_image_path = new MyLineEdit(groupBox);
        text_voxel_image_path->setObjectName(QString::fromUtf8("text_voxel_image_path"));

        gridLayout->addWidget(text_voxel_image_path, 0, 1, 1, 1);

        pushButton_select_image_path = new QPushButton(groupBox);
        pushButton_select_image_path->setObjectName(QString::fromUtf8("pushButton_select_image_path"));
        QIcon icon1;
        QString iconThemeName = QString::fromUtf8("folder");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/system/icons/folder.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_select_image_path->setIcon(icon1);

        gridLayout->addWidget(pushButton_select_image_path, 0, 2, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);


        verticalLayout_3->addLayout(gridLayout);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        spinboxInt_voxel_max_iter = new MySpinBox(groupBox_2);
        spinboxInt_voxel_max_iter->setObjectName(QString::fromUtf8("spinboxInt_voxel_max_iter"));
        spinboxInt_voxel_max_iter->setMinimum(1);
        spinboxInt_voxel_max_iter->setMaximum(10000);

        gridLayout_2->addWidget(spinboxInt_voxel_max_iter, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        checkBox_voxel_greyscale_iterations = new MyCheckBox(groupBox_2);
        checkBox_voxel_greyscale_iterations->setObjectName(QString::fromUtf8("checkBox_voxel_greyscale_iterations"));

        gridLayout_2->addWidget(checkBox_voxel_greyscale_iterations, 1, 0, 1, 2);


        verticalLayout_4->addLayout(gridLayout_2);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_5 = new QVBoxLayout(groupBox_3);
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(2, 2, 2, 2);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_6 = new QLabel(groupBox_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_6, 0, 0, 1, 1);

        spinboxInt_voxel_samples_x = new MySpinBox(groupBox_3);
        spinboxInt_voxel_samples_x->setObjectName(QString::fromUtf8("spinboxInt_voxel_samples_x"));
        spinboxInt_voxel_samples_x->setMinimum(1);
        spinboxInt_voxel_samples_x->setMaximum(65535);

        gridLayout_3->addWidget(spinboxInt_voxel_samples_x, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_7, 0, 2, 1, 1);

        spinboxInt_voxel_samples_y = new MySpinBox(groupBox_3);
        spinboxInt_voxel_samples_y->setObjectName(QString::fromUtf8("spinboxInt_voxel_samples_y"));
        spinboxInt_voxel_samples_y->setMinimum(2);
        spinboxInt_voxel_samples_y->setMaximum(65535);

        gridLayout_3->addWidget(spinboxInt_voxel_samples_y, 0, 3, 1, 1);

        label_8 = new QLabel(groupBox_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_3->addWidget(label_8, 0, 4, 1, 1);

        spinboxInt_voxel_samples_z = new MySpinBox(groupBox_3);
        spinboxInt_voxel_samples_z->setObjectName(QString::fromUtf8("spinboxInt_voxel_samples_z"));
        spinboxInt_voxel_samples_z->setMinimum(2);
        spinboxInt_voxel_samples_z->setMaximum(65535);

        gridLayout_3->addWidget(spinboxInt_voxel_samples_z, 0, 5, 1, 1);


        verticalLayout_5->addLayout(gridLayout_3);


        verticalLayout_2->addWidget(groupBox_3);

        groupCheck_voxel_custom_limit_enabled = new MyGroupBox(scrollAreaWidgetContents);
        groupCheck_voxel_custom_limit_enabled->setObjectName(QString::fromUtf8("groupCheck_voxel_custom_limit_enabled"));
        groupCheck_voxel_custom_limit_enabled->setCheckable(true);
        verticalLayout_45 = new QVBoxLayout(groupCheck_voxel_custom_limit_enabled);
        verticalLayout_45->setSpacing(2);
        verticalLayout_45->setObjectName(QString::fromUtf8("verticalLayout_45"));
        verticalLayout_45->setContentsMargins(2, 2, 2, 2);
        gridLayout_21 = new QGridLayout();
        gridLayout_21->setSpacing(2);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        vect3_voxel_limit_max_z = new MyLineEdit(groupCheck_voxel_custom_limit_enabled);
        vect3_voxel_limit_max_z->setObjectName(QString::fromUtf8("vect3_voxel_limit_max_z"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(vect3_voxel_limit_max_z->sizePolicy().hasHeightForWidth());
        vect3_voxel_limit_max_z->setSizePolicy(sizePolicy);

        gridLayout_21->addWidget(vect3_voxel_limit_max_z, 5, 2, 1, 1);

        label_114 = new QLabel(groupCheck_voxel_custom_limit_enabled);
        label_114->setObjectName(QString::fromUtf8("label_114"));

        gridLayout_21->addWidget(label_114, 3, 0, 1, 1);

        vect3_voxel_limit_min_z = new MyLineEdit(groupCheck_voxel_custom_limit_enabled);
        vect3_voxel_limit_min_z->setObjectName(QString::fromUtf8("vect3_voxel_limit_min_z"));
        sizePolicy.setHeightForWidth(vect3_voxel_limit_min_z->sizePolicy().hasHeightForWidth());
        vect3_voxel_limit_min_z->setSizePolicy(sizePolicy);

        gridLayout_21->addWidget(vect3_voxel_limit_min_z, 2, 2, 1, 1);

        label_110 = new QLabel(groupCheck_voxel_custom_limit_enabled);
        label_110->setObjectName(QString::fromUtf8("label_110"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_110->sizePolicy().hasHeightForWidth());
        label_110->setSizePolicy(sizePolicy1);
        label_110->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_21->addWidget(label_110, 0, 1, 1, 1);

        vect3_voxel_limit_max_x = new MyLineEdit(groupCheck_voxel_custom_limit_enabled);
        vect3_voxel_limit_max_x->setObjectName(QString::fromUtf8("vect3_voxel_limit_max_x"));
        sizePolicy.setHeightForWidth(vect3_voxel_limit_max_x->sizePolicy().hasHeightForWidth());
        vect3_voxel_limit_max_x->setSizePolicy(sizePolicy);

        gridLayout_21->addWidget(vect3_voxel_limit_max_x, 3, 2, 1, 1);

        vect3_voxel_limit_max_y = new MyLineEdit(groupCheck_voxel_custom_limit_enabled);
        vect3_voxel_limit_max_y->setObjectName(QString::fromUtf8("vect3_voxel_limit_max_y"));
        sizePolicy.setHeightForWidth(vect3_voxel_limit_max_y->sizePolicy().hasHeightForWidth());
        vect3_voxel_limit_max_y->setSizePolicy(sizePolicy);

        gridLayout_21->addWidget(vect3_voxel_limit_max_y, 4, 2, 1, 1);

        vect3_voxel_limit_min_x = new MyLineEdit(groupCheck_voxel_custom_limit_enabled);
        vect3_voxel_limit_min_x->setObjectName(QString::fromUtf8("vect3_voxel_limit_min_x"));
        sizePolicy.setHeightForWidth(vect3_voxel_limit_min_x->sizePolicy().hasHeightForWidth());
        vect3_voxel_limit_min_x->setSizePolicy(sizePolicy);

        gridLayout_21->addWidget(vect3_voxel_limit_min_x, 0, 2, 1, 1);

        label_111 = new QLabel(groupCheck_voxel_custom_limit_enabled);
        label_111->setObjectName(QString::fromUtf8("label_111"));
        sizePolicy1.setHeightForWidth(label_111->sizePolicy().hasHeightForWidth());
        label_111->setSizePolicy(sizePolicy1);
        label_111->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_21->addWidget(label_111, 1, 1, 1, 1);

        vect3_voxel_limit_min_y = new MyLineEdit(groupCheck_voxel_custom_limit_enabled);
        vect3_voxel_limit_min_y->setObjectName(QString::fromUtf8("vect3_voxel_limit_min_y"));
        sizePolicy.setHeightForWidth(vect3_voxel_limit_min_y->sizePolicy().hasHeightForWidth());
        vect3_voxel_limit_min_y->setSizePolicy(sizePolicy);

        gridLayout_21->addWidget(vect3_voxel_limit_min_y, 1, 2, 1, 1);

        label_112 = new QLabel(groupCheck_voxel_custom_limit_enabled);
        label_112->setObjectName(QString::fromUtf8("label_112"));
        sizePolicy1.setHeightForWidth(label_112->sizePolicy().hasHeightForWidth());
        label_112->setSizePolicy(sizePolicy1);
        label_112->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_21->addWidget(label_112, 2, 1, 1, 1);

        label_109 = new QLabel(groupCheck_voxel_custom_limit_enabled);
        label_109->setObjectName(QString::fromUtf8("label_109"));

        gridLayout_21->addWidget(label_109, 0, 0, 1, 1);

        label_117 = new QLabel(groupCheck_voxel_custom_limit_enabled);
        label_117->setObjectName(QString::fromUtf8("label_117"));
        sizePolicy1.setHeightForWidth(label_117->sizePolicy().hasHeightForWidth());
        label_117->setSizePolicy(sizePolicy1);
        label_117->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_21->addWidget(label_117, 3, 1, 1, 1);

        label_118 = new QLabel(groupCheck_voxel_custom_limit_enabled);
        label_118->setObjectName(QString::fromUtf8("label_118"));
        sizePolicy1.setHeightForWidth(label_118->sizePolicy().hasHeightForWidth());
        label_118->setSizePolicy(sizePolicy1);
        label_118->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_21->addWidget(label_118, 4, 1, 1, 1);

        label_119 = new QLabel(groupCheck_voxel_custom_limit_enabled);
        label_119->setObjectName(QString::fromUtf8("label_119"));
        sizePolicy1.setHeightForWidth(label_119->sizePolicy().hasHeightForWidth());
        label_119->setSizePolicy(sizePolicy1);
        label_119->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_21->addWidget(label_119, 5, 1, 1, 1);


        verticalLayout_45->addLayout(gridLayout_21);


        verticalLayout_2->addWidget(groupCheck_voxel_custom_limit_enabled);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_start_render_layers = new QPushButton(scrollAreaWidgetContents);
        pushButton_start_render_layers->setObjectName(QString::fromUtf8("pushButton_start_render_layers"));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("applications-graphics");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8(":/system/icons/applications-graphics.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_start_render_layers->setIcon(icon2);

        horizontalLayout->addWidget(pushButton_start_render_layers);

        pushButton_stop_render_layers = new QPushButton(scrollAreaWidgetContents);
        pushButton_stop_render_layers->setObjectName(QString::fromUtf8("pushButton_stop_render_layers"));
        QIcon icon3;
        iconThemeName = QString::fromUtf8("process-stop");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8(":/system/icons/process-stop.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_stop_render_layers->setIcon(icon3);

        horizontalLayout->addWidget(pushButton_stop_render_layers);

        pushButton_show_layers = new QPushButton(scrollAreaWidgetContents);
        pushButton_show_layers->setObjectName(QString::fromUtf8("pushButton_show_layers"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(pushButton_show_layers->sizePolicy().hasHeightForWidth());
        pushButton_show_layers->setSizePolicy(sizePolicy2);
        QIcon icon4;
        iconThemeName = QString::fromUtf8("media-playback-start");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8(":/system/icons/media-playback-start.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_show_layers->setIcon(icon4);

        horizontalLayout->addWidget(pushButton_show_layers);


        verticalLayout_2->addLayout(horizontalLayout);

        progressBar = new MyProgressBar(scrollAreaWidgetContents);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMaximum(1000);
        progressBar->setValue(24);

        verticalLayout_2->addWidget(progressBar);

        label_info = new QLabel(scrollAreaWidgetContents);
        label_info->setObjectName(QString::fromUtf8("label_info"));

        verticalLayout_2->addWidget(label_info);

        groupCheck_voxel_show_information = new MyGroupBox(scrollAreaWidgetContents);
        groupCheck_voxel_show_information->setObjectName(QString::fromUtf8("groupCheck_voxel_show_information"));
        groupCheck_voxel_show_information->setCheckable(true);
        verticalLayout_voxel_show_information = new QVBoxLayout(groupCheck_voxel_show_information);
        verticalLayout_voxel_show_information->setSpacing(2);
        verticalLayout_voxel_show_information->setObjectName(QString::fromUtf8("verticalLayout_voxel_show_information"));
        verticalLayout_voxel_show_information->setContentsMargins(2, 2, 2, 2);
        label_voxel_information = new QLabel(groupCheck_voxel_show_information);
        label_voxel_information->setObjectName(QString::fromUtf8("label_voxel_information"));

        verticalLayout_voxel_show_information->addWidget(label_voxel_information);


        verticalLayout_2->addWidget(groupCheck_voxel_show_information);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        QWidget::setTabOrder(scrollArea, text_voxel_image_path);
        QWidget::setTabOrder(text_voxel_image_path, pushButton_select_image_path);
        QWidget::setTabOrder(pushButton_select_image_path, spinboxInt_voxel_max_iter);
        QWidget::setTabOrder(spinboxInt_voxel_max_iter, spinboxInt_voxel_samples_x);
        QWidget::setTabOrder(spinboxInt_voxel_samples_x, spinboxInt_voxel_samples_y);
        QWidget::setTabOrder(spinboxInt_voxel_samples_y, spinboxInt_voxel_samples_z);
        QWidget::setTabOrder(spinboxInt_voxel_samples_z, vect3_voxel_limit_min_x);
        QWidget::setTabOrder(vect3_voxel_limit_min_x, vect3_voxel_limit_min_y);
        QWidget::setTabOrder(vect3_voxel_limit_min_y, vect3_voxel_limit_min_z);
        QWidget::setTabOrder(vect3_voxel_limit_min_z, vect3_voxel_limit_max_x);
        QWidget::setTabOrder(vect3_voxel_limit_max_x, vect3_voxel_limit_max_y);
        QWidget::setTabOrder(vect3_voxel_limit_max_y, vect3_voxel_limit_max_z);
        QWidget::setTabOrder(vect3_voxel_limit_max_z, pushButton_start_render_layers);
        QWidget::setTabOrder(pushButton_start_render_layers, pushButton_stop_render_layers);
        QWidget::setTabOrder(pushButton_stop_render_layers, pushButton_show_layers);

        retranslateUi(cVoxelExportDialog);

        QMetaObject::connectSlotsByName(cVoxelExportDialog);
    } // setupUi

    void retranslateUi(QDialog *cVoxelExportDialog)
    {
        cVoxelExportDialog->setWindowTitle(QCoreApplication::translate("cVoxelExportDialog", "Export Voxel", nullptr));
        groupBox->setTitle(QCoreApplication::translate("cVoxelExportDialog", "Layer settings", nullptr));
        pushButton_select_image_path->setText(QString());
        label->setText(QCoreApplication::translate("cVoxelExportDialog", "layer folder", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("cVoxelExportDialog", "Render settings", nullptr));
        label_5->setText(QCoreApplication::translate("cVoxelExportDialog", "MaxIter", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_voxel_greyscale_iterations->setToolTip(QCoreApplication::translate("cVoxelExportDialog", "<html><head/><body><p>When this option is enabled, the fractal appearance is maintained at all resolutions. </p><p>The fractal detail level will be automatically adjusted to match any change of image resolution. </p><p>For instance, if the resolution is doubled then the detail level will be reduced by half.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_voxel_greyscale_iterations->setText(QCoreApplication::translate("cVoxelExportDialog", "Save as greyscale images with iteration counts", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("cVoxelExportDialog", "Sample count", nullptr));
        label_6->setText(QCoreApplication::translate("cVoxelExportDialog", "Samples X", nullptr));
        label_7->setText(QCoreApplication::translate("cVoxelExportDialog", "Samples Y", nullptr));
        label_8->setText(QCoreApplication::translate("cVoxelExportDialog", "Samples Z", nullptr));
        groupCheck_voxel_custom_limit_enabled->setTitle(QCoreApplication::translate("cVoxelExportDialog", "Custom Limits (leave untoggled to use global limits)", nullptr));
        label_114->setText(QCoreApplication::translate("cVoxelExportDialog", "top right back corner:", nullptr));
        label_110->setText(QCoreApplication::translate("cVoxelExportDialog", "x:", nullptr));
        label_111->setText(QCoreApplication::translate("cVoxelExportDialog", "y:", nullptr));
        label_112->setText(QCoreApplication::translate("cVoxelExportDialog", "z:", nullptr));
        label_109->setText(QCoreApplication::translate("cVoxelExportDialog", "bottom left front corner:", nullptr));
        label_117->setText(QCoreApplication::translate("cVoxelExportDialog", "x:", nullptr));
        label_118->setText(QCoreApplication::translate("cVoxelExportDialog", "y:", nullptr));
        label_119->setText(QCoreApplication::translate("cVoxelExportDialog", "z:", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_start_render_layers->setToolTip(QCoreApplication::translate("cVoxelExportDialog", "<html><head/><body><p>Start rendering of layers based on actual settings</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_start_render_layers->setText(QCoreApplication::translate("cVoxelExportDialog", "Render Layers", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_stop_render_layers->setToolTip(QCoreApplication::translate("cVoxelExportDialog", "<html><head/><body><p>Terminate rendering of layers</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_stop_render_layers->setText(QCoreApplication::translate("cVoxelExportDialog", "Stop Render", nullptr));
        pushButton_show_layers->setText(QCoreApplication::translate("cVoxelExportDialog", "Show Layers", nullptr));
        label_info->setText(QString());
        groupCheck_voxel_show_information->setTitle(QCoreApplication::translate("cVoxelExportDialog", "Show Voxel Information", nullptr));
        label_voxel_information->setText(QCoreApplication::translate("cVoxelExportDialog", "<html><head/><body><p>The generated image layers can be used to generate </p><p>a <span style=\" font-weight:600;\">3d model</span> for various applications.</p><p>A possible workflow to work with these images:</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p align=\"center\"><span style=\" font-weight:600;\">Program</span></p></td><td><p align=\"center\"><span style=\" font-weight:600;\">Input</span></p></td><td><p align=\"center\"><span style=\" font-weight:600;\">Output</span></p></td></tr><tr><td><p><span style=\" font-weight:600;\">Mandelbulber</span></p></td><td><p align=\"center\">---</p></td><td><p align=\"center\">image layers</p></td></tr><tr><td><p><a href=\"http://fiji.sc/\"><span style=\" font-weight:600; text-decoration: underline; color:#0000ff;\">FIJI</span></a></p></td><td><p align=\"center\">image layers</p></td><td><p align=\"center\">3D model</p></td></tr><tr><td><p><a href=\"http://meshlab"
                        ".sourceforge.net/\"><span style=\" font-weight:600; text-decoration: underline; color:#0000ff;\">Meshlab</span></a></p></td><td><p align=\"center\">3D model</p></td><td><p align=\"center\">optimized 3D model</p></td></tr><tr><td><p><span style=\" font-weight:600;\">Online 3d print service</span></p></td><td><p align=\"center\">optimized 3D model</p></td><td><p align=\"center\">printed model</p></td></tr></table><p></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cVoxelExportDialog: public Ui_cVoxelExportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VOXEL_EXPORT_DIALOG_H
