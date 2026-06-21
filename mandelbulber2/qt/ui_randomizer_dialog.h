/********************************************************************************
** Form generated from reading UI file 'randomizer_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RANDOMIZER_DIALOG_H
#define UI_RANDOMIZER_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include "thumbnail_widget.h"

QT_BEGIN_NAMESPACE

class Ui_cRandomizerDialog
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *pushButton_slight;
    QPushButton *pushButton_medium;
    QPushButton *pushButton_heavy;
    QPushButton *pushButton_stop;
    QCheckBox *checkBox_dont_randomize_booleans;
    QCheckBox *checkBox_dont_randomize_camera;
    QPushButton *pushButton_reset;
    QPushButton *pushButton_clean_up;
    QPushButton *pushButton_add_to_keyframes;
    QPushButton *pushButton_use;
    QProgressBar *progressBar;
    QGroupBox *groupBox_version_actual;
    QVBoxLayout *verticalLayout_4;
    cThumbnailWidget *previewwidget_actual;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_version_01;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_select_01;
    QToolButton *toolButton_save_01;
    QCheckBox *checkBox_keep_01;
    cThumbnailWidget *previewwidget_01;
    QGroupBox *groupBox_version_09;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_select_09;
    QToolButton *toolButton_save_09;
    QCheckBox *checkBox_keep_09;
    cThumbnailWidget *previewwidget_09;
    QGroupBox *groupBox_version_02;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_select_02;
    QToolButton *toolButton_save_02;
    QCheckBox *checkBox_keep_02;
    cThumbnailWidget *previewwidget_02;
    QGroupBox *groupBox_version_05;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_select_05;
    QToolButton *toolButton_save_05;
    QCheckBox *checkBox_keep_05;
    cThumbnailWidget *previewwidget_05;
    QGroupBox *groupBox_version_08;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *pushButton_select_08;
    QToolButton *toolButton_save_08;
    QCheckBox *checkBox_keep_08;
    cThumbnailWidget *previewwidget_08;
    QGroupBox *groupBox_version_03;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_14;
    QPushButton *pushButton_select_03;
    QToolButton *toolButton_save_03;
    QCheckBox *checkBox_keep_03;
    cThumbnailWidget *previewwidget_03;
    QGroupBox *groupBox_version_12;
    QVBoxLayout *verticalLayout_15;
    QHBoxLayout *horizontalLayout_12;
    QPushButton *pushButton_select_12;
    QToolButton *toolButton_save_12;
    QCheckBox *checkBox_keep_12;
    cThumbnailWidget *previewwidget_12;
    QGroupBox *groupBox_version_10;
    QVBoxLayout *verticalLayout_13;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_select_10;
    QToolButton *toolButton_save_10;
    QCheckBox *checkBox_keep_10;
    cThumbnailWidget *previewwidget_10;
    QGroupBox *groupBox_version_11;
    QVBoxLayout *verticalLayout_14;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *pushButton_select_11;
    QToolButton *toolButton_save_11;
    QCheckBox *checkBox_keep_11;
    cThumbnailWidget *previewwidget_11;
    QGroupBox *groupBox_version_04;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_select_04;
    QToolButton *toolButton_save_04;
    QCheckBox *checkBox_keep_04;
    cThumbnailWidget *previewwidget_04;
    QGroupBox *groupBox_version_07;
    QVBoxLayout *verticalLayout_11;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_select_07;
    QToolButton *toolButton_save_07;
    QCheckBox *checkBox_keep_07;
    cThumbnailWidget *previewwidget_07;
    QGroupBox *groupBox_version_06;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_select_06;
    QToolButton *toolButton_save_06;
    QCheckBox *checkBox_keep_06;
    cThumbnailWidget *previewwidget_06;

    void setupUi(QDialog *cRandomizerDialog)
    {
        if (cRandomizerDialog->objectName().isEmpty())
            cRandomizerDialog->setObjectName(QString::fromUtf8("cRandomizerDialog"));
        cRandomizerDialog->resize(820, 916);
        verticalLayout = new QVBoxLayout(cRandomizerDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        pushButton_slight = new QPushButton(cRandomizerDialog);
        pushButton_slight->setObjectName(QString::fromUtf8("pushButton_slight"));

        horizontalLayout_13->addWidget(pushButton_slight);

        pushButton_medium = new QPushButton(cRandomizerDialog);
        pushButton_medium->setObjectName(QString::fromUtf8("pushButton_medium"));

        horizontalLayout_13->addWidget(pushButton_medium);

        pushButton_heavy = new QPushButton(cRandomizerDialog);
        pushButton_heavy->setObjectName(QString::fromUtf8("pushButton_heavy"));

        horizontalLayout_13->addWidget(pushButton_heavy);

        pushButton_stop = new QPushButton(cRandomizerDialog);
        pushButton_stop->setObjectName(QString::fromUtf8("pushButton_stop"));

        horizontalLayout_13->addWidget(pushButton_stop);


        verticalLayout_2->addLayout(horizontalLayout_13);

        checkBox_dont_randomize_booleans = new QCheckBox(cRandomizerDialog);
        checkBox_dont_randomize_booleans->setObjectName(QString::fromUtf8("checkBox_dont_randomize_booleans"));

        verticalLayout_2->addWidget(checkBox_dont_randomize_booleans);

        checkBox_dont_randomize_camera = new QCheckBox(cRandomizerDialog);
        checkBox_dont_randomize_camera->setObjectName(QString::fromUtf8("checkBox_dont_randomize_camera"));

        verticalLayout_2->addWidget(checkBox_dont_randomize_camera);

        pushButton_reset = new QPushButton(cRandomizerDialog);
        pushButton_reset->setObjectName(QString::fromUtf8("pushButton_reset"));

        verticalLayout_2->addWidget(pushButton_reset);

        pushButton_clean_up = new QPushButton(cRandomizerDialog);
        pushButton_clean_up->setObjectName(QString::fromUtf8("pushButton_clean_up"));

        verticalLayout_2->addWidget(pushButton_clean_up);

        pushButton_add_to_keyframes = new QPushButton(cRandomizerDialog);
        pushButton_add_to_keyframes->setObjectName(QString::fromUtf8("pushButton_add_to_keyframes"));

        verticalLayout_2->addWidget(pushButton_add_to_keyframes);

        pushButton_use = new QPushButton(cRandomizerDialog);
        pushButton_use->setObjectName(QString::fromUtf8("pushButton_use"));

        verticalLayout_2->addWidget(pushButton_use);

        progressBar = new QProgressBar(cRandomizerDialog);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMaximum(1000);
        progressBar->setValue(0);

        verticalLayout_2->addWidget(progressBar);


        horizontalLayout->addLayout(verticalLayout_2);

        groupBox_version_actual = new QGroupBox(cRandomizerDialog);
        groupBox_version_actual->setObjectName(QString::fromUtf8("groupBox_version_actual"));
        verticalLayout_4 = new QVBoxLayout(groupBox_version_actual);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        previewwidget_actual = new cThumbnailWidget(groupBox_version_actual);
        previewwidget_actual->setObjectName(QString::fromUtf8("previewwidget_actual"));
        previewwidget_actual->setMinimumSize(QSize(128, 128));

        verticalLayout_4->addWidget(previewwidget_actual);


        horizontalLayout->addWidget(groupBox_version_actual);


        verticalLayout->addLayout(horizontalLayout);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_version_01 = new QGroupBox(cRandomizerDialog);
        groupBox_version_01->setObjectName(QString::fromUtf8("groupBox_version_01"));
        verticalLayout_3 = new QVBoxLayout(groupBox_version_01);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_select_01 = new QPushButton(groupBox_version_01);
        pushButton_select_01->setObjectName(QString::fromUtf8("pushButton_select_01"));

        horizontalLayout_2->addWidget(pushButton_select_01);

        toolButton_save_01 = new QToolButton(groupBox_version_01);
        toolButton_save_01->setObjectName(QString::fromUtf8("toolButton_save_01"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("document-save");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/system/icons/document-save.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        toolButton_save_01->setIcon(icon);

        horizontalLayout_2->addWidget(toolButton_save_01);

        checkBox_keep_01 = new QCheckBox(groupBox_version_01);
        checkBox_keep_01->setObjectName(QString::fromUtf8("checkBox_keep_01"));

        horizontalLayout_2->addWidget(checkBox_keep_01);

        horizontalLayout_2->setStretch(0, 1);

        verticalLayout_3->addLayout(horizontalLayout_2);

        previewwidget_01 = new cThumbnailWidget(groupBox_version_01);
        previewwidget_01->setObjectName(QString::fromUtf8("previewwidget_01"));
        previewwidget_01->setMinimumSize(QSize(16, 16));

        verticalLayout_3->addWidget(previewwidget_01);

        verticalLayout_3->setStretch(1, 1);

        gridLayout->addWidget(groupBox_version_01, 0, 0, 1, 1);

        groupBox_version_09 = new QGroupBox(cRandomizerDialog);
        groupBox_version_09->setObjectName(QString::fromUtf8("groupBox_version_09"));
        verticalLayout_12 = new QVBoxLayout(groupBox_version_09);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(0);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        pushButton_select_09 = new QPushButton(groupBox_version_09);
        pushButton_select_09->setObjectName(QString::fromUtf8("pushButton_select_09"));

        horizontalLayout_9->addWidget(pushButton_select_09);

        toolButton_save_09 = new QToolButton(groupBox_version_09);
        toolButton_save_09->setObjectName(QString::fromUtf8("toolButton_save_09"));
        toolButton_save_09->setIcon(icon);

        horizontalLayout_9->addWidget(toolButton_save_09);

        checkBox_keep_09 = new QCheckBox(groupBox_version_09);
        checkBox_keep_09->setObjectName(QString::fromUtf8("checkBox_keep_09"));

        horizontalLayout_9->addWidget(checkBox_keep_09);

        horizontalLayout_9->setStretch(0, 1);

        verticalLayout_12->addLayout(horizontalLayout_9);

        previewwidget_09 = new cThumbnailWidget(groupBox_version_09);
        previewwidget_09->setObjectName(QString::fromUtf8("previewwidget_09"));
        previewwidget_09->setMinimumSize(QSize(16, 16));

        verticalLayout_12->addWidget(previewwidget_09);

        verticalLayout_12->setStretch(1, 1);

        gridLayout->addWidget(groupBox_version_09, 2, 0, 1, 1);

        groupBox_version_02 = new QGroupBox(cRandomizerDialog);
        groupBox_version_02->setObjectName(QString::fromUtf8("groupBox_version_02"));
        verticalLayout_5 = new QVBoxLayout(groupBox_version_02);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_select_02 = new QPushButton(groupBox_version_02);
        pushButton_select_02->setObjectName(QString::fromUtf8("pushButton_select_02"));

        horizontalLayout_3->addWidget(pushButton_select_02);

        toolButton_save_02 = new QToolButton(groupBox_version_02);
        toolButton_save_02->setObjectName(QString::fromUtf8("toolButton_save_02"));
        toolButton_save_02->setIcon(icon);

        horizontalLayout_3->addWidget(toolButton_save_02);

        checkBox_keep_02 = new QCheckBox(groupBox_version_02);
        checkBox_keep_02->setObjectName(QString::fromUtf8("checkBox_keep_02"));

        horizontalLayout_3->addWidget(checkBox_keep_02);

        horizontalLayout_3->setStretch(0, 1);

        verticalLayout_5->addLayout(horizontalLayout_3);

        previewwidget_02 = new cThumbnailWidget(groupBox_version_02);
        previewwidget_02->setObjectName(QString::fromUtf8("previewwidget_02"));
        previewwidget_02->setMinimumSize(QSize(16, 16));

        verticalLayout_5->addWidget(previewwidget_02);

        verticalLayout_5->setStretch(1, 1);

        gridLayout->addWidget(groupBox_version_02, 0, 1, 1, 1);

        groupBox_version_05 = new QGroupBox(cRandomizerDialog);
        groupBox_version_05->setObjectName(QString::fromUtf8("groupBox_version_05"));
        verticalLayout_7 = new QVBoxLayout(groupBox_version_05);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButton_select_05 = new QPushButton(groupBox_version_05);
        pushButton_select_05->setObjectName(QString::fromUtf8("pushButton_select_05"));

        horizontalLayout_5->addWidget(pushButton_select_05);

        toolButton_save_05 = new QToolButton(groupBox_version_05);
        toolButton_save_05->setObjectName(QString::fromUtf8("toolButton_save_05"));
        toolButton_save_05->setIcon(icon);

        horizontalLayout_5->addWidget(toolButton_save_05);

        checkBox_keep_05 = new QCheckBox(groupBox_version_05);
        checkBox_keep_05->setObjectName(QString::fromUtf8("checkBox_keep_05"));

        horizontalLayout_5->addWidget(checkBox_keep_05);

        horizontalLayout_5->setStretch(0, 1);

        verticalLayout_7->addLayout(horizontalLayout_5);

        previewwidget_05 = new cThumbnailWidget(groupBox_version_05);
        previewwidget_05->setObjectName(QString::fromUtf8("previewwidget_05"));
        previewwidget_05->setMinimumSize(QSize(16, 16));

        verticalLayout_7->addWidget(previewwidget_05);

        verticalLayout_7->setStretch(1, 1);

        gridLayout->addWidget(groupBox_version_05, 1, 0, 1, 1);

        groupBox_version_08 = new QGroupBox(cRandomizerDialog);
        groupBox_version_08->setObjectName(QString::fromUtf8("groupBox_version_08"));
        verticalLayout_10 = new QVBoxLayout(groupBox_version_08);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(0);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        pushButton_select_08 = new QPushButton(groupBox_version_08);
        pushButton_select_08->setObjectName(QString::fromUtf8("pushButton_select_08"));

        horizontalLayout_8->addWidget(pushButton_select_08);

        toolButton_save_08 = new QToolButton(groupBox_version_08);
        toolButton_save_08->setObjectName(QString::fromUtf8("toolButton_save_08"));
        toolButton_save_08->setIcon(icon);

        horizontalLayout_8->addWidget(toolButton_save_08);

        checkBox_keep_08 = new QCheckBox(groupBox_version_08);
        checkBox_keep_08->setObjectName(QString::fromUtf8("checkBox_keep_08"));

        horizontalLayout_8->addWidget(checkBox_keep_08);

        horizontalLayout_8->setStretch(0, 1);

        verticalLayout_10->addLayout(horizontalLayout_8);

        previewwidget_08 = new cThumbnailWidget(groupBox_version_08);
        previewwidget_08->setObjectName(QString::fromUtf8("previewwidget_08"));
        previewwidget_08->setMinimumSize(QSize(16, 16));

        verticalLayout_10->addWidget(previewwidget_08);

        verticalLayout_10->setStretch(1, 1);

        gridLayout->addWidget(groupBox_version_08, 1, 3, 1, 1);

        groupBox_version_03 = new QGroupBox(cRandomizerDialog);
        groupBox_version_03->setObjectName(QString::fromUtf8("groupBox_version_03"));
        verticalLayout_6 = new QVBoxLayout(groupBox_version_03);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(0);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        pushButton_select_03 = new QPushButton(groupBox_version_03);
        pushButton_select_03->setObjectName(QString::fromUtf8("pushButton_select_03"));

        horizontalLayout_14->addWidget(pushButton_select_03);

        toolButton_save_03 = new QToolButton(groupBox_version_03);
        toolButton_save_03->setObjectName(QString::fromUtf8("toolButton_save_03"));
        toolButton_save_03->setIcon(icon);

        horizontalLayout_14->addWidget(toolButton_save_03);

        checkBox_keep_03 = new QCheckBox(groupBox_version_03);
        checkBox_keep_03->setObjectName(QString::fromUtf8("checkBox_keep_03"));

        horizontalLayout_14->addWidget(checkBox_keep_03);

        horizontalLayout_14->setStretch(0, 1);

        verticalLayout_6->addLayout(horizontalLayout_14);

        previewwidget_03 = new cThumbnailWidget(groupBox_version_03);
        previewwidget_03->setObjectName(QString::fromUtf8("previewwidget_03"));
        previewwidget_03->setMinimumSize(QSize(16, 16));

        verticalLayout_6->addWidget(previewwidget_03);

        verticalLayout_6->setStretch(1, 1);

        gridLayout->addWidget(groupBox_version_03, 0, 2, 1, 1);

        groupBox_version_12 = new QGroupBox(cRandomizerDialog);
        groupBox_version_12->setObjectName(QString::fromUtf8("groupBox_version_12"));
        verticalLayout_15 = new QVBoxLayout(groupBox_version_12);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(0);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        pushButton_select_12 = new QPushButton(groupBox_version_12);
        pushButton_select_12->setObjectName(QString::fromUtf8("pushButton_select_12"));

        horizontalLayout_12->addWidget(pushButton_select_12);

        toolButton_save_12 = new QToolButton(groupBox_version_12);
        toolButton_save_12->setObjectName(QString::fromUtf8("toolButton_save_12"));
        toolButton_save_12->setIcon(icon);

        horizontalLayout_12->addWidget(toolButton_save_12);

        checkBox_keep_12 = new QCheckBox(groupBox_version_12);
        checkBox_keep_12->setObjectName(QString::fromUtf8("checkBox_keep_12"));

        horizontalLayout_12->addWidget(checkBox_keep_12);

        horizontalLayout_12->setStretch(0, 1);

        verticalLayout_15->addLayout(horizontalLayout_12);

        previewwidget_12 = new cThumbnailWidget(groupBox_version_12);
        previewwidget_12->setObjectName(QString::fromUtf8("previewwidget_12"));
        previewwidget_12->setMinimumSize(QSize(16, 16));

        verticalLayout_15->addWidget(previewwidget_12);

        verticalLayout_15->setStretch(1, 1);

        gridLayout->addWidget(groupBox_version_12, 2, 3, 1, 1);

        groupBox_version_10 = new QGroupBox(cRandomizerDialog);
        groupBox_version_10->setObjectName(QString::fromUtf8("groupBox_version_10"));
        verticalLayout_13 = new QVBoxLayout(groupBox_version_10);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(0);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        pushButton_select_10 = new QPushButton(groupBox_version_10);
        pushButton_select_10->setObjectName(QString::fromUtf8("pushButton_select_10"));

        horizontalLayout_10->addWidget(pushButton_select_10);

        toolButton_save_10 = new QToolButton(groupBox_version_10);
        toolButton_save_10->setObjectName(QString::fromUtf8("toolButton_save_10"));
        toolButton_save_10->setIcon(icon);

        horizontalLayout_10->addWidget(toolButton_save_10);

        checkBox_keep_10 = new QCheckBox(groupBox_version_10);
        checkBox_keep_10->setObjectName(QString::fromUtf8("checkBox_keep_10"));

        horizontalLayout_10->addWidget(checkBox_keep_10);

        horizontalLayout_10->setStretch(0, 1);

        verticalLayout_13->addLayout(horizontalLayout_10);

        previewwidget_10 = new cThumbnailWidget(groupBox_version_10);
        previewwidget_10->setObjectName(QString::fromUtf8("previewwidget_10"));
        previewwidget_10->setMinimumSize(QSize(16, 16));

        verticalLayout_13->addWidget(previewwidget_10);

        verticalLayout_13->setStretch(1, 1);

        gridLayout->addWidget(groupBox_version_10, 2, 1, 1, 1);

        groupBox_version_11 = new QGroupBox(cRandomizerDialog);
        groupBox_version_11->setObjectName(QString::fromUtf8("groupBox_version_11"));
        verticalLayout_14 = new QVBoxLayout(groupBox_version_11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(0);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        pushButton_select_11 = new QPushButton(groupBox_version_11);
        pushButton_select_11->setObjectName(QString::fromUtf8("pushButton_select_11"));

        horizontalLayout_11->addWidget(pushButton_select_11);

        toolButton_save_11 = new QToolButton(groupBox_version_11);
        toolButton_save_11->setObjectName(QString::fromUtf8("toolButton_save_11"));
        toolButton_save_11->setIcon(icon);

        horizontalLayout_11->addWidget(toolButton_save_11);

        checkBox_keep_11 = new QCheckBox(groupBox_version_11);
        checkBox_keep_11->setObjectName(QString::fromUtf8("checkBox_keep_11"));

        horizontalLayout_11->addWidget(checkBox_keep_11);

        horizontalLayout_11->setStretch(0, 1);

        verticalLayout_14->addLayout(horizontalLayout_11);

        previewwidget_11 = new cThumbnailWidget(groupBox_version_11);
        previewwidget_11->setObjectName(QString::fromUtf8("previewwidget_11"));
        previewwidget_11->setMinimumSize(QSize(16, 16));

        verticalLayout_14->addWidget(previewwidget_11);

        verticalLayout_14->setStretch(1, 1);

        gridLayout->addWidget(groupBox_version_11, 2, 2, 1, 1);

        groupBox_version_04 = new QGroupBox(cRandomizerDialog);
        groupBox_version_04->setObjectName(QString::fromUtf8("groupBox_version_04"));
        verticalLayout_8 = new QVBoxLayout(groupBox_version_04);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton_select_04 = new QPushButton(groupBox_version_04);
        pushButton_select_04->setObjectName(QString::fromUtf8("pushButton_select_04"));

        horizontalLayout_4->addWidget(pushButton_select_04);

        toolButton_save_04 = new QToolButton(groupBox_version_04);
        toolButton_save_04->setObjectName(QString::fromUtf8("toolButton_save_04"));
        toolButton_save_04->setIcon(icon);

        horizontalLayout_4->addWidget(toolButton_save_04);

        checkBox_keep_04 = new QCheckBox(groupBox_version_04);
        checkBox_keep_04->setObjectName(QString::fromUtf8("checkBox_keep_04"));

        horizontalLayout_4->addWidget(checkBox_keep_04);

        horizontalLayout_4->setStretch(0, 1);

        verticalLayout_8->addLayout(horizontalLayout_4);

        previewwidget_04 = new cThumbnailWidget(groupBox_version_04);
        previewwidget_04->setObjectName(QString::fromUtf8("previewwidget_04"));
        previewwidget_04->setMinimumSize(QSize(16, 16));

        verticalLayout_8->addWidget(previewwidget_04);

        verticalLayout_8->setStretch(1, 1);

        gridLayout->addWidget(groupBox_version_04, 0, 3, 1, 1);

        groupBox_version_07 = new QGroupBox(cRandomizerDialog);
        groupBox_version_07->setObjectName(QString::fromUtf8("groupBox_version_07"));
        verticalLayout_11 = new QVBoxLayout(groupBox_version_07);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(0);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pushButton_select_07 = new QPushButton(groupBox_version_07);
        pushButton_select_07->setObjectName(QString::fromUtf8("pushButton_select_07"));

        horizontalLayout_7->addWidget(pushButton_select_07);

        toolButton_save_07 = new QToolButton(groupBox_version_07);
        toolButton_save_07->setObjectName(QString::fromUtf8("toolButton_save_07"));
        toolButton_save_07->setIcon(icon);

        horizontalLayout_7->addWidget(toolButton_save_07);

        checkBox_keep_07 = new QCheckBox(groupBox_version_07);
        checkBox_keep_07->setObjectName(QString::fromUtf8("checkBox_keep_07"));

        horizontalLayout_7->addWidget(checkBox_keep_07);

        horizontalLayout_7->setStretch(0, 1);

        verticalLayout_11->addLayout(horizontalLayout_7);

        previewwidget_07 = new cThumbnailWidget(groupBox_version_07);
        previewwidget_07->setObjectName(QString::fromUtf8("previewwidget_07"));
        previewwidget_07->setMinimumSize(QSize(16, 16));

        verticalLayout_11->addWidget(previewwidget_07);

        verticalLayout_11->setStretch(1, 1);

        gridLayout->addWidget(groupBox_version_07, 1, 2, 1, 1);

        groupBox_version_06 = new QGroupBox(cRandomizerDialog);
        groupBox_version_06->setObjectName(QString::fromUtf8("groupBox_version_06"));
        verticalLayout_9 = new QVBoxLayout(groupBox_version_06);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        pushButton_select_06 = new QPushButton(groupBox_version_06);
        pushButton_select_06->setObjectName(QString::fromUtf8("pushButton_select_06"));

        horizontalLayout_6->addWidget(pushButton_select_06);

        toolButton_save_06 = new QToolButton(groupBox_version_06);
        toolButton_save_06->setObjectName(QString::fromUtf8("toolButton_save_06"));
        toolButton_save_06->setIcon(icon);

        horizontalLayout_6->addWidget(toolButton_save_06);

        checkBox_keep_06 = new QCheckBox(groupBox_version_06);
        checkBox_keep_06->setObjectName(QString::fromUtf8("checkBox_keep_06"));

        horizontalLayout_6->addWidget(checkBox_keep_06);

        horizontalLayout_6->setStretch(0, 1);

        verticalLayout_9->addLayout(horizontalLayout_6);

        previewwidget_06 = new cThumbnailWidget(groupBox_version_06);
        previewwidget_06->setObjectName(QString::fromUtf8("previewwidget_06"));
        previewwidget_06->setMinimumSize(QSize(16, 16));

        verticalLayout_9->addWidget(previewwidget_06);

        verticalLayout_9->setStretch(1, 1);

        gridLayout->addWidget(groupBox_version_06, 1, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalLayout->setStretch(1, 1);

        retranslateUi(cRandomizerDialog);

        QMetaObject::connectSlotsByName(cRandomizerDialog);
    } // setupUi

    void retranslateUi(QDialog *cRandomizerDialog)
    {
        cRandomizerDialog->setWindowTitle(QCoreApplication::translate("cRandomizerDialog", "Dialog", nullptr));
        pushButton_slight->setText(QCoreApplication::translate("cRandomizerDialog", "Slight randomize", nullptr));
        pushButton_medium->setText(QCoreApplication::translate("cRandomizerDialog", "Medium randomize", nullptr));
        pushButton_heavy->setText(QCoreApplication::translate("cRandomizerDialog", "Heavy randomize", nullptr));
        pushButton_stop->setText(QCoreApplication::translate("cRandomizerDialog", "STOP", nullptr));
        checkBox_dont_randomize_booleans->setText(QCoreApplication::translate("cRandomizerDialog", "Do not randomize integers and booleans", nullptr));
        checkBox_dont_randomize_camera->setText(QCoreApplication::translate("cRandomizerDialog", "Do not randomize camera", nullptr));
        pushButton_reset->setText(QCoreApplication::translate("cRandomizerDialog", "Reset", nullptr));
        pushButton_clean_up->setText(QCoreApplication::translate("cRandomizerDialog", "Reset negligible parameters", nullptr));
        pushButton_add_to_keyframes->setText(QCoreApplication::translate("cRandomizerDialog", "Use and add to keyframe animation", nullptr));
        pushButton_use->setText(QCoreApplication::translate("cRandomizerDialog", "Use", nullptr));
        groupBox_version_actual->setTitle(QCoreApplication::translate("cRandomizerDialog", "Actual version", nullptr));
        groupBox_version_01->setTitle(QCoreApplication::translate("cRandomizerDialog", "Version 1", nullptr));
        pushButton_select_01->setText(QCoreApplication::translate("cRandomizerDialog", "Select", nullptr));
        toolButton_save_01->setText(QCoreApplication::translate("cRandomizerDialog", "...", nullptr));
        checkBox_keep_01->setText(QCoreApplication::translate("cRandomizerDialog", "Keep", nullptr));
        groupBox_version_09->setTitle(QCoreApplication::translate("cRandomizerDialog", "Version 9", nullptr));
        pushButton_select_09->setText(QCoreApplication::translate("cRandomizerDialog", "Select", nullptr));
        toolButton_save_09->setText(QCoreApplication::translate("cRandomizerDialog", "...", nullptr));
        checkBox_keep_09->setText(QCoreApplication::translate("cRandomizerDialog", "Keep", nullptr));
        groupBox_version_02->setTitle(QCoreApplication::translate("cRandomizerDialog", "Version 2", nullptr));
        pushButton_select_02->setText(QCoreApplication::translate("cRandomizerDialog", "Select", nullptr));
        toolButton_save_02->setText(QCoreApplication::translate("cRandomizerDialog", "...", nullptr));
        checkBox_keep_02->setText(QCoreApplication::translate("cRandomizerDialog", "Keep", nullptr));
        groupBox_version_05->setTitle(QCoreApplication::translate("cRandomizerDialog", "Version 5", nullptr));
        pushButton_select_05->setText(QCoreApplication::translate("cRandomizerDialog", "Select", nullptr));
        toolButton_save_05->setText(QCoreApplication::translate("cRandomizerDialog", "...", nullptr));
        checkBox_keep_05->setText(QCoreApplication::translate("cRandomizerDialog", "Keep", nullptr));
        groupBox_version_08->setTitle(QCoreApplication::translate("cRandomizerDialog", "Version 8", nullptr));
        pushButton_select_08->setText(QCoreApplication::translate("cRandomizerDialog", "Select", nullptr));
        toolButton_save_08->setText(QCoreApplication::translate("cRandomizerDialog", "...", nullptr));
        checkBox_keep_08->setText(QCoreApplication::translate("cRandomizerDialog", "Keep", nullptr));
        groupBox_version_03->setTitle(QCoreApplication::translate("cRandomizerDialog", "Version 3", nullptr));
        pushButton_select_03->setText(QCoreApplication::translate("cRandomizerDialog", "Select", nullptr));
        toolButton_save_03->setText(QCoreApplication::translate("cRandomizerDialog", "...", nullptr));
        checkBox_keep_03->setText(QCoreApplication::translate("cRandomizerDialog", "Keep", nullptr));
        groupBox_version_12->setTitle(QCoreApplication::translate("cRandomizerDialog", "Version 12", nullptr));
        pushButton_select_12->setText(QCoreApplication::translate("cRandomizerDialog", "Select", nullptr));
        toolButton_save_12->setText(QCoreApplication::translate("cRandomizerDialog", "...", nullptr));
        checkBox_keep_12->setText(QCoreApplication::translate("cRandomizerDialog", "Keep", nullptr));
        groupBox_version_10->setTitle(QCoreApplication::translate("cRandomizerDialog", "Version 10", nullptr));
        pushButton_select_10->setText(QCoreApplication::translate("cRandomizerDialog", "Select", nullptr));
        toolButton_save_10->setText(QCoreApplication::translate("cRandomizerDialog", "...", nullptr));
        checkBox_keep_10->setText(QCoreApplication::translate("cRandomizerDialog", "Keep", nullptr));
        groupBox_version_11->setTitle(QCoreApplication::translate("cRandomizerDialog", "Version 11", nullptr));
        pushButton_select_11->setText(QCoreApplication::translate("cRandomizerDialog", "Select", nullptr));
        toolButton_save_11->setText(QCoreApplication::translate("cRandomizerDialog", "...", nullptr));
        checkBox_keep_11->setText(QCoreApplication::translate("cRandomizerDialog", "Keep", nullptr));
        groupBox_version_04->setTitle(QCoreApplication::translate("cRandomizerDialog", "Version 4", nullptr));
        pushButton_select_04->setText(QCoreApplication::translate("cRandomizerDialog", "Select", nullptr));
        toolButton_save_04->setText(QCoreApplication::translate("cRandomizerDialog", "...", nullptr));
        checkBox_keep_04->setText(QCoreApplication::translate("cRandomizerDialog", "Keep", nullptr));
        groupBox_version_07->setTitle(QCoreApplication::translate("cRandomizerDialog", "Version 7", nullptr));
        pushButton_select_07->setText(QCoreApplication::translate("cRandomizerDialog", "Select", nullptr));
        toolButton_save_07->setText(QCoreApplication::translate("cRandomizerDialog", "...", nullptr));
        checkBox_keep_07->setText(QCoreApplication::translate("cRandomizerDialog", "Keep", nullptr));
        groupBox_version_06->setTitle(QCoreApplication::translate("cRandomizerDialog", "Version 6", nullptr));
        pushButton_select_06->setText(QCoreApplication::translate("cRandomizerDialog", "Select", nullptr));
        toolButton_save_06->setText(QCoreApplication::translate("cRandomizerDialog", "...", nullptr));
        checkBox_keep_06->setText(QCoreApplication::translate("cRandomizerDialog", "Keep", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cRandomizerDialog: public Ui_cRandomizerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RANDOMIZER_DIALOG_H
