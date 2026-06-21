/********************************************************************************
** Form generated from reading UI file 'mesh_export_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESH_EXPORT_DIALOG_H
#define UI_MESH_EXPORT_DIALOG_H

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
#include "my_combo_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_progress_bar.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cMeshExportDialog
{
public:
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout;
    MyLineEdit *text_mesh_output_filename;
    QPushButton *pushButton_select_image_path;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    MyComboBox *comboBox_mesh_file_mode;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    MyCheckBox *checkBox_mesh_color;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QGridLayout *gridLayout_2;
    MySpinBox *spinboxInt_voxel_max_iter;
    QLabel *label_5;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_3;
    QLabel *label_6;
    MySpinBox *spinboxInt_voxel_samples_x;
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
    MyProgressBar *progressBar;
    QLabel *label_info;
    QSpacerItem *verticalSpacer;
    QLabel *label_2;

    void setupUi(QDialog *cMeshExportDialog)
    {
        if (cMeshExportDialog->objectName().isEmpty())
            cMeshExportDialog->setObjectName(QString::fromUtf8("cMeshExportDialog"));
        cMeshExportDialog->resize(543, 535);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/system/icons/mesh.png"), QSize(), QIcon::Normal, QIcon::Off);
        cMeshExportDialog->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(cMeshExportDialog);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        scrollArea = new QScrollArea(cMeshExportDialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 535, 527));
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
        text_mesh_output_filename = new MyLineEdit(groupBox);
        text_mesh_output_filename->setObjectName(QString::fromUtf8("text_mesh_output_filename"));

        gridLayout->addWidget(text_mesh_output_filename, 0, 1, 1, 1);

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

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_3->addWidget(label_3);

        comboBox_mesh_file_mode = new MyComboBox(groupBox);
        comboBox_mesh_file_mode->addItem(QString());
        comboBox_mesh_file_mode->addItem(QString());
        comboBox_mesh_file_mode->setObjectName(QString::fromUtf8("comboBox_mesh_file_mode"));

        horizontalLayout_3->addWidget(comboBox_mesh_file_mode);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);

        checkBox_mesh_color = new MyCheckBox(groupBox);
        checkBox_mesh_color->setObjectName(QString::fromUtf8("checkBox_mesh_color"));

        horizontalLayout_2->addWidget(checkBox_mesh_color);


        verticalLayout_3->addLayout(horizontalLayout_2);


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


        verticalLayout_2->addLayout(horizontalLayout);

        progressBar = new MyProgressBar(scrollAreaWidgetContents);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMaximum(1000);
        progressBar->setValue(24);

        verticalLayout_2->addWidget(progressBar);

        label_info = new QLabel(scrollAreaWidgetContents);
        label_info->setObjectName(QString::fromUtf8("label_info"));

        verticalLayout_2->addWidget(label_info);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setWordWrap(true);

        verticalLayout_2->addWidget(label_2);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        QWidget::setTabOrder(scrollArea, text_mesh_output_filename);
        QWidget::setTabOrder(text_mesh_output_filename, pushButton_select_image_path);
        QWidget::setTabOrder(pushButton_select_image_path, spinboxInt_voxel_max_iter);
        QWidget::setTabOrder(spinboxInt_voxel_max_iter, spinboxInt_voxel_samples_x);
        QWidget::setTabOrder(spinboxInt_voxel_samples_x, vect3_voxel_limit_min_x);
        QWidget::setTabOrder(vect3_voxel_limit_min_x, vect3_voxel_limit_min_y);
        QWidget::setTabOrder(vect3_voxel_limit_min_y, vect3_voxel_limit_min_z);
        QWidget::setTabOrder(vect3_voxel_limit_min_z, vect3_voxel_limit_max_x);
        QWidget::setTabOrder(vect3_voxel_limit_max_x, vect3_voxel_limit_max_y);
        QWidget::setTabOrder(vect3_voxel_limit_max_y, vect3_voxel_limit_max_z);
        QWidget::setTabOrder(vect3_voxel_limit_max_z, pushButton_start_render_layers);
        QWidget::setTabOrder(pushButton_start_render_layers, pushButton_stop_render_layers);

        retranslateUi(cMeshExportDialog);

        QMetaObject::connectSlotsByName(cMeshExportDialog);
    } // setupUi

    void retranslateUi(QDialog *cMeshExportDialog)
    {
        cMeshExportDialog->setWindowTitle(QCoreApplication::translate("cMeshExportDialog", "Export Mesh", nullptr));
        groupBox->setTitle(QCoreApplication::translate("cMeshExportDialog", "Output settings", nullptr));
        pushButton_select_image_path->setText(QString());
        label->setText(QCoreApplication::translate("cMeshExportDialog", "Output file name", nullptr));
        label_3->setText(QCoreApplication::translate("cMeshExportDialog", "File mode:", nullptr));
        comboBox_mesh_file_mode->setItemText(0, QCoreApplication::translate("cMeshExportDialog", "binary", nullptr));
        comboBox_mesh_file_mode->setItemText(1, QCoreApplication::translate("cMeshExportDialog", "ascii", nullptr));

        label_4->setText(QCoreApplication::translate("cMeshExportDialog", "Append to mesh:", nullptr));
        checkBox_mesh_color->setText(QCoreApplication::translate("cMeshExportDialog", "Color", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("cMeshExportDialog", "Render settings", nullptr));
        label_5->setText(QCoreApplication::translate("cMeshExportDialog", "MaxIter", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("cMeshExportDialog", "Sample count", nullptr));
        label_6->setText(QCoreApplication::translate("cMeshExportDialog", "Resolution", nullptr));
        groupCheck_voxel_custom_limit_enabled->setTitle(QCoreApplication::translate("cMeshExportDialog", "Custom Limits (leave &untoggled to use global limits)", nullptr));
        label_114->setText(QCoreApplication::translate("cMeshExportDialog", "top right back corner:", nullptr));
        label_110->setText(QCoreApplication::translate("cMeshExportDialog", "x:", nullptr));
        label_111->setText(QCoreApplication::translate("cMeshExportDialog", "y:", nullptr));
        label_112->setText(QCoreApplication::translate("cMeshExportDialog", "z:", nullptr));
        label_109->setText(QCoreApplication::translate("cMeshExportDialog", "bottom left front corner:", nullptr));
        label_117->setText(QCoreApplication::translate("cMeshExportDialog", "x:", nullptr));
        label_118->setText(QCoreApplication::translate("cMeshExportDialog", "y:", nullptr));
        label_119->setText(QCoreApplication::translate("cMeshExportDialog", "z:", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_start_render_layers->setToolTip(QCoreApplication::translate("cMeshExportDialog", "<html><head/><body><p>Start rendering of layers based on actual settings</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_start_render_layers->setText(QCoreApplication::translate("cMeshExportDialog", "&Export", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_stop_render_layers->setToolTip(QCoreApplication::translate("cMeshExportDialog", "<html><head/><body><p>Terminate rendering of layers</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_stop_render_layers->setText(QCoreApplication::translate("cMeshExportDialog", "&Stop", nullptr));
        label_info->setText(QString());
        label_2->setText(QCoreApplication::translate("cMeshExportDialog", "Computer Aided Manufacturing of Mandelbrot Fractals.", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cMeshExportDialog: public Ui_cMeshExportDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESH_EXPORT_DIALOG_H
