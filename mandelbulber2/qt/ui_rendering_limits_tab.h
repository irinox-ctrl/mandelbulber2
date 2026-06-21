/********************************************************************************
** Form generated from reading UI file 'rendering_limits_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERING_LIMITS_TAB_H
#define UI_RENDERING_LIMITS_TAB_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_check_box.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cRenderingLimitsTab
{
public:
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_13;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_43;
    QGridLayout *gridLayout_19;
    QLabel *label_108;
    MyLineEdit *logedit_view_distance_min;
    QLabel *label_107;
    MyLineEdit *logedit_view_distance_max;
    MyGroupBox *groupCheck_limits_enabled;
    QVBoxLayout *verticalLayout_45;
    QPushButton *bu_bounding_box_to_limit;
    QGridLayout *gridLayout_bounding_box_layout;
    MyLineEdit *logedit_limit_outer_bounding;
    QLabel *label_maximum_bounding_boy;
    QLabel *label_bounding_box_limit_manioulation;
    QGridLayout *gridLayout_bounding_box_size;
    QLabel *bounding_box_x_label;
    QToolButton *bu_bounding_box_size_x_up;
    QToolButton *bu_bounding_box_size_x_down;
    QToolButton *bu_bounding_box_move_x_neg;
    QToolButton *bu_bounding_box_move_x_pos;
    QLabel *bounding_box_y_label;
    QToolButton *bu_bounding_box_size_y_up;
    QToolButton *bu_bounding_box_size_y_down;
    QToolButton *bu_bounding_box_move_y_neg;
    QToolButton *bu_bounding_box_move_y_pos;
    QLabel *bounding_box_z_label;
    QToolButton *bu_bounding_box_size_z_up;
    QToolButton *bu_bounding_box_size_z_down;
    QToolButton *bu_bounding_box_move_z_neg;
    QToolButton *bu_bounding_box_move_z_pos;
    QGridLayout *gridLayout_21;
    QLabel *label_110;
    MyLineEdit *vect3_limit_max_x;
    MyLineEdit *vect3_limit_min_z;
    QLabel *label_109;
    MyLineEdit *vect3_limit_min_y;
    QLabel *label_111;
    QLabel *label_112;
    MyLineEdit *vect3_limit_min_x;
    MyLineEdit *vect3_limit_max_y;
    MyLineEdit *vect3_limit_max_z;
    QLabel *label_114;
    QLabel *label_117;
    QLabel *label_118;
    QLabel *label_119;
    QGroupBox *groupBox_auto_fog;
    QVBoxLayout *verticalLayout_autoFog;
    QHBoxLayout *horizontalLayout_autoFogQuality;
    QLabel *label_auto_fog_quality;
    MyComboBox *comboBox_auto_fog_quality;
    QHBoxLayout *horizontalLayout_volumetricMaxSteps;
    QLabel *label_volumetric_max_steps;
    MySpinBox *spinboxInt_volumetric_max_steps;
    MyCheckBox *checkBox_volumetric_preview_fast;
    QHBoxLayout *horizontalLayout_volumetricPreviewStepMul;
    QLabel *label_volumetric_preview_step_mul;
    MyDoubleSpinBox *spinbox_volumetric_preview_step_mul;
    MyCheckBox *checkBox_volumetric_blue_noise_jitter;
    QHBoxLayout *horizontalLayout_volumetricJitterStrength;
    QLabel *label_volumetric_jitter_strength;
    MyDoubleSpinBox *spinbox_volumetric_jitter_strength;
    QHBoxLayout *horizontalLayout_autoFogButtons2;
    QPushButton *pushButton_auto_clouds;
    QHBoxLayout *horizontalLayout_autoFogButtons;
    QPushButton *pushButton_auto_iteration_fog;
    QPushButton *pushButton_auto_volumetric_fog;
    QPushButton *pushButton_auto_all_fog;
    QLabel *label_auto_fog_result;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *cRenderingLimitsTab)
    {
        if (cRenderingLimitsTab->objectName().isEmpty())
            cRenderingLimitsTab->setObjectName(QString::fromUtf8("cRenderingLimitsTab"));
        verticalLayout_4 = new QVBoxLayout(cRenderingLimitsTab);
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(2, 2, 2, 2);
        scrollArea_3 = new QScrollArea(cRenderingLimitsTab);
        scrollArea_3->setObjectName(QString::fromUtf8("scrollArea_3"));
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 417, 1082));
        verticalLayout_13 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_13->setSpacing(2);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(2, 2, 2, 2);
        groupBox_4 = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_43 = new QVBoxLayout(groupBox_4);
        verticalLayout_43->setSpacing(2);
        verticalLayout_43->setObjectName(QString::fromUtf8("verticalLayout_43"));
        verticalLayout_43->setContentsMargins(2, 2, 2, 2);
        gridLayout_19 = new QGridLayout();
        gridLayout_19->setSpacing(2);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        label_108 = new QLabel(groupBox_4);
        label_108->setObjectName(QString::fromUtf8("label_108"));

        gridLayout_19->addWidget(label_108, 1, 0, 1, 1);

        logedit_view_distance_min = new MyLineEdit(groupBox_4);
        logedit_view_distance_min->setObjectName(QString::fromUtf8("logedit_view_distance_min"));

        gridLayout_19->addWidget(logedit_view_distance_min, 1, 1, 1, 1);

        label_107 = new QLabel(groupBox_4);
        label_107->setObjectName(QString::fromUtf8("label_107"));

        gridLayout_19->addWidget(label_107, 0, 0, 1, 1);

        logedit_view_distance_max = new MyLineEdit(groupBox_4);
        logedit_view_distance_max->setObjectName(QString::fromUtf8("logedit_view_distance_max"));

        gridLayout_19->addWidget(logedit_view_distance_max, 0, 1, 1, 1);


        verticalLayout_43->addLayout(gridLayout_19);


        verticalLayout_13->addWidget(groupBox_4);

        groupCheck_limits_enabled = new MyGroupBox(scrollAreaWidgetContents_3);
        groupCheck_limits_enabled->setObjectName(QString::fromUtf8("groupCheck_limits_enabled"));
        groupCheck_limits_enabled->setCheckable(true);
        verticalLayout_45 = new QVBoxLayout(groupCheck_limits_enabled);
        verticalLayout_45->setSpacing(2);
        verticalLayout_45->setObjectName(QString::fromUtf8("verticalLayout_45"));
        verticalLayout_45->setContentsMargins(2, 2, 2, 2);
        bu_bounding_box_to_limit = new QPushButton(groupCheck_limits_enabled);
        bu_bounding_box_to_limit->setObjectName(QString::fromUtf8("bu_bounding_box_to_limit"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(bu_bounding_box_to_limit->sizePolicy().hasHeightForWidth());
        bu_bounding_box_to_limit->setSizePolicy(sizePolicy);

        verticalLayout_45->addWidget(bu_bounding_box_to_limit);

        gridLayout_bounding_box_layout = new QGridLayout();
        gridLayout_bounding_box_layout->setSpacing(2);
        gridLayout_bounding_box_layout->setObjectName(QString::fromUtf8("gridLayout_bounding_box_layout"));
        logedit_limit_outer_bounding = new MyLineEdit(groupCheck_limits_enabled);
        logedit_limit_outer_bounding->setObjectName(QString::fromUtf8("logedit_limit_outer_bounding"));

        gridLayout_bounding_box_layout->addWidget(logedit_limit_outer_bounding, 0, 1, 1, 1);

        label_maximum_bounding_boy = new QLabel(groupCheck_limits_enabled);
        label_maximum_bounding_boy->setObjectName(QString::fromUtf8("label_maximum_bounding_boy"));

        gridLayout_bounding_box_layout->addWidget(label_maximum_bounding_boy, 0, 0, 1, 1);


        verticalLayout_45->addLayout(gridLayout_bounding_box_layout);

        label_bounding_box_limit_manioulation = new QLabel(groupCheck_limits_enabled);
        label_bounding_box_limit_manioulation->setObjectName(QString::fromUtf8("label_bounding_box_limit_manioulation"));

        verticalLayout_45->addWidget(label_bounding_box_limit_manioulation);

        gridLayout_bounding_box_size = new QGridLayout();
        gridLayout_bounding_box_size->setSpacing(2);
        gridLayout_bounding_box_size->setObjectName(QString::fromUtf8("gridLayout_bounding_box_size"));
        bounding_box_x_label = new QLabel(groupCheck_limits_enabled);
        bounding_box_x_label->setObjectName(QString::fromUtf8("bounding_box_x_label"));

        gridLayout_bounding_box_size->addWidget(bounding_box_x_label, 0, 0, 1, 1);

        bu_bounding_box_size_x_up = new QToolButton(groupCheck_limits_enabled);
        bu_bounding_box_size_x_up->setObjectName(QString::fromUtf8("bu_bounding_box_size_x_up"));
        sizePolicy.setHeightForWidth(bu_bounding_box_size_x_up->sizePolicy().hasHeightForWidth());
        bu_bounding_box_size_x_up->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/navigation/icons/size-up.png"), QSize(), QIcon::Normal, QIcon::Off);
        bu_bounding_box_size_x_up->setIcon(icon);
        bu_bounding_box_size_x_up->setIconSize(QSize(24, 24));

        gridLayout_bounding_box_size->addWidget(bu_bounding_box_size_x_up, 0, 1, 1, 1);

        bu_bounding_box_size_x_down = new QToolButton(groupCheck_limits_enabled);
        bu_bounding_box_size_x_down->setObjectName(QString::fromUtf8("bu_bounding_box_size_x_down"));
        sizePolicy.setHeightForWidth(bu_bounding_box_size_x_down->sizePolicy().hasHeightForWidth());
        bu_bounding_box_size_x_down->setSizePolicy(sizePolicy);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/navigation/icons/size-down.png"), QSize(), QIcon::Normal, QIcon::Off);
        bu_bounding_box_size_x_down->setIcon(icon1);
        bu_bounding_box_size_x_down->setIconSize(QSize(24, 24));

        gridLayout_bounding_box_size->addWidget(bu_bounding_box_size_x_down, 0, 2, 1, 1);

        bu_bounding_box_move_x_neg = new QToolButton(groupCheck_limits_enabled);
        bu_bounding_box_move_x_neg->setObjectName(QString::fromUtf8("bu_bounding_box_move_x_neg"));
        sizePolicy.setHeightForWidth(bu_bounding_box_move_x_neg->sizePolicy().hasHeightForWidth());
        bu_bounding_box_move_x_neg->setSizePolicy(sizePolicy);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/navigation/icons/go-previous.png"), QSize(), QIcon::Normal, QIcon::Off);
        bu_bounding_box_move_x_neg->setIcon(icon2);
        bu_bounding_box_move_x_neg->setIconSize(QSize(24, 24));

        gridLayout_bounding_box_size->addWidget(bu_bounding_box_move_x_neg, 0, 3, 1, 1);

        bu_bounding_box_move_x_pos = new QToolButton(groupCheck_limits_enabled);
        bu_bounding_box_move_x_pos->setObjectName(QString::fromUtf8("bu_bounding_box_move_x_pos"));
        sizePolicy.setHeightForWidth(bu_bounding_box_move_x_pos->sizePolicy().hasHeightForWidth());
        bu_bounding_box_move_x_pos->setSizePolicy(sizePolicy);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/navigation/icons/go-next.png"), QSize(), QIcon::Normal, QIcon::Off);
        bu_bounding_box_move_x_pos->setIcon(icon3);
        bu_bounding_box_move_x_pos->setIconSize(QSize(24, 24));

        gridLayout_bounding_box_size->addWidget(bu_bounding_box_move_x_pos, 0, 4, 1, 1);

        bounding_box_y_label = new QLabel(groupCheck_limits_enabled);
        bounding_box_y_label->setObjectName(QString::fromUtf8("bounding_box_y_label"));

        gridLayout_bounding_box_size->addWidget(bounding_box_y_label, 1, 0, 1, 1);

        bu_bounding_box_size_y_up = new QToolButton(groupCheck_limits_enabled);
        bu_bounding_box_size_y_up->setObjectName(QString::fromUtf8("bu_bounding_box_size_y_up"));
        sizePolicy.setHeightForWidth(bu_bounding_box_size_y_up->sizePolicy().hasHeightForWidth());
        bu_bounding_box_size_y_up->setSizePolicy(sizePolicy);
        bu_bounding_box_size_y_up->setIcon(icon);
        bu_bounding_box_size_y_up->setIconSize(QSize(24, 24));

        gridLayout_bounding_box_size->addWidget(bu_bounding_box_size_y_up, 1, 1, 1, 1);

        bu_bounding_box_size_y_down = new QToolButton(groupCheck_limits_enabled);
        bu_bounding_box_size_y_down->setObjectName(QString::fromUtf8("bu_bounding_box_size_y_down"));
        sizePolicy.setHeightForWidth(bu_bounding_box_size_y_down->sizePolicy().hasHeightForWidth());
        bu_bounding_box_size_y_down->setSizePolicy(sizePolicy);
        bu_bounding_box_size_y_down->setIcon(icon1);
        bu_bounding_box_size_y_down->setIconSize(QSize(24, 24));

        gridLayout_bounding_box_size->addWidget(bu_bounding_box_size_y_down, 1, 2, 1, 1);

        bu_bounding_box_move_y_neg = new QToolButton(groupCheck_limits_enabled);
        bu_bounding_box_move_y_neg->setObjectName(QString::fromUtf8("bu_bounding_box_move_y_neg"));
        sizePolicy.setHeightForWidth(bu_bounding_box_move_y_neg->sizePolicy().hasHeightForWidth());
        bu_bounding_box_move_y_neg->setSizePolicy(sizePolicy);
        bu_bounding_box_move_y_neg->setIcon(icon2);
        bu_bounding_box_move_y_neg->setIconSize(QSize(24, 24));

        gridLayout_bounding_box_size->addWidget(bu_bounding_box_move_y_neg, 1, 3, 1, 1);

        bu_bounding_box_move_y_pos = new QToolButton(groupCheck_limits_enabled);
        bu_bounding_box_move_y_pos->setObjectName(QString::fromUtf8("bu_bounding_box_move_y_pos"));
        sizePolicy.setHeightForWidth(bu_bounding_box_move_y_pos->sizePolicy().hasHeightForWidth());
        bu_bounding_box_move_y_pos->setSizePolicy(sizePolicy);
        bu_bounding_box_move_y_pos->setIcon(icon3);
        bu_bounding_box_move_y_pos->setIconSize(QSize(24, 24));

        gridLayout_bounding_box_size->addWidget(bu_bounding_box_move_y_pos, 1, 4, 1, 1);

        bounding_box_z_label = new QLabel(groupCheck_limits_enabled);
        bounding_box_z_label->setObjectName(QString::fromUtf8("bounding_box_z_label"));

        gridLayout_bounding_box_size->addWidget(bounding_box_z_label, 2, 0, 1, 1);

        bu_bounding_box_size_z_up = new QToolButton(groupCheck_limits_enabled);
        bu_bounding_box_size_z_up->setObjectName(QString::fromUtf8("bu_bounding_box_size_z_up"));
        sizePolicy.setHeightForWidth(bu_bounding_box_size_z_up->sizePolicy().hasHeightForWidth());
        bu_bounding_box_size_z_up->setSizePolicy(sizePolicy);
        bu_bounding_box_size_z_up->setIcon(icon);
        bu_bounding_box_size_z_up->setIconSize(QSize(24, 24));

        gridLayout_bounding_box_size->addWidget(bu_bounding_box_size_z_up, 2, 1, 1, 1);

        bu_bounding_box_size_z_down = new QToolButton(groupCheck_limits_enabled);
        bu_bounding_box_size_z_down->setObjectName(QString::fromUtf8("bu_bounding_box_size_z_down"));
        sizePolicy.setHeightForWidth(bu_bounding_box_size_z_down->sizePolicy().hasHeightForWidth());
        bu_bounding_box_size_z_down->setSizePolicy(sizePolicy);
        bu_bounding_box_size_z_down->setIcon(icon1);
        bu_bounding_box_size_z_down->setIconSize(QSize(24, 24));

        gridLayout_bounding_box_size->addWidget(bu_bounding_box_size_z_down, 2, 2, 1, 1);

        bu_bounding_box_move_z_neg = new QToolButton(groupCheck_limits_enabled);
        bu_bounding_box_move_z_neg->setObjectName(QString::fromUtf8("bu_bounding_box_move_z_neg"));
        sizePolicy.setHeightForWidth(bu_bounding_box_move_z_neg->sizePolicy().hasHeightForWidth());
        bu_bounding_box_move_z_neg->setSizePolicy(sizePolicy);
        bu_bounding_box_move_z_neg->setIcon(icon2);
        bu_bounding_box_move_z_neg->setIconSize(QSize(24, 24));

        gridLayout_bounding_box_size->addWidget(bu_bounding_box_move_z_neg, 2, 3, 1, 1);

        bu_bounding_box_move_z_pos = new QToolButton(groupCheck_limits_enabled);
        bu_bounding_box_move_z_pos->setObjectName(QString::fromUtf8("bu_bounding_box_move_z_pos"));
        sizePolicy.setHeightForWidth(bu_bounding_box_move_z_pos->sizePolicy().hasHeightForWidth());
        bu_bounding_box_move_z_pos->setSizePolicy(sizePolicy);
        bu_bounding_box_move_z_pos->setIcon(icon3);
        bu_bounding_box_move_z_pos->setIconSize(QSize(24, 24));

        gridLayout_bounding_box_size->addWidget(bu_bounding_box_move_z_pos, 2, 4, 1, 1);


        verticalLayout_45->addLayout(gridLayout_bounding_box_size);

        gridLayout_21 = new QGridLayout();
        gridLayout_21->setSpacing(2);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        label_110 = new QLabel(groupCheck_limits_enabled);
        label_110->setObjectName(QString::fromUtf8("label_110"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_110->sizePolicy().hasHeightForWidth());
        label_110->setSizePolicy(sizePolicy1);
        label_110->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_21->addWidget(label_110, 0, 1, 1, 1);

        vect3_limit_max_x = new MyLineEdit(groupCheck_limits_enabled);
        vect3_limit_max_x->setObjectName(QString::fromUtf8("vect3_limit_max_x"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(vect3_limit_max_x->sizePolicy().hasHeightForWidth());
        vect3_limit_max_x->setSizePolicy(sizePolicy2);

        gridLayout_21->addWidget(vect3_limit_max_x, 3, 2, 1, 1);

        vect3_limit_min_z = new MyLineEdit(groupCheck_limits_enabled);
        vect3_limit_min_z->setObjectName(QString::fromUtf8("vect3_limit_min_z"));
        sizePolicy2.setHeightForWidth(vect3_limit_min_z->sizePolicy().hasHeightForWidth());
        vect3_limit_min_z->setSizePolicy(sizePolicy2);

        gridLayout_21->addWidget(vect3_limit_min_z, 2, 2, 1, 1);

        label_109 = new QLabel(groupCheck_limits_enabled);
        label_109->setObjectName(QString::fromUtf8("label_109"));

        gridLayout_21->addWidget(label_109, 0, 0, 1, 1);

        vect3_limit_min_y = new MyLineEdit(groupCheck_limits_enabled);
        vect3_limit_min_y->setObjectName(QString::fromUtf8("vect3_limit_min_y"));
        sizePolicy2.setHeightForWidth(vect3_limit_min_y->sizePolicy().hasHeightForWidth());
        vect3_limit_min_y->setSizePolicy(sizePolicy2);

        gridLayout_21->addWidget(vect3_limit_min_y, 1, 2, 1, 1);

        label_111 = new QLabel(groupCheck_limits_enabled);
        label_111->setObjectName(QString::fromUtf8("label_111"));
        sizePolicy1.setHeightForWidth(label_111->sizePolicy().hasHeightForWidth());
        label_111->setSizePolicy(sizePolicy1);
        label_111->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_21->addWidget(label_111, 1, 1, 1, 1);

        label_112 = new QLabel(groupCheck_limits_enabled);
        label_112->setObjectName(QString::fromUtf8("label_112"));
        sizePolicy1.setHeightForWidth(label_112->sizePolicy().hasHeightForWidth());
        label_112->setSizePolicy(sizePolicy1);
        label_112->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_21->addWidget(label_112, 2, 1, 1, 1);

        vect3_limit_min_x = new MyLineEdit(groupCheck_limits_enabled);
        vect3_limit_min_x->setObjectName(QString::fromUtf8("vect3_limit_min_x"));
        sizePolicy2.setHeightForWidth(vect3_limit_min_x->sizePolicy().hasHeightForWidth());
        vect3_limit_min_x->setSizePolicy(sizePolicy2);

        gridLayout_21->addWidget(vect3_limit_min_x, 0, 2, 1, 1);

        vect3_limit_max_y = new MyLineEdit(groupCheck_limits_enabled);
        vect3_limit_max_y->setObjectName(QString::fromUtf8("vect3_limit_max_y"));
        sizePolicy2.setHeightForWidth(vect3_limit_max_y->sizePolicy().hasHeightForWidth());
        vect3_limit_max_y->setSizePolicy(sizePolicy2);

        gridLayout_21->addWidget(vect3_limit_max_y, 4, 2, 1, 1);

        vect3_limit_max_z = new MyLineEdit(groupCheck_limits_enabled);
        vect3_limit_max_z->setObjectName(QString::fromUtf8("vect3_limit_max_z"));
        sizePolicy2.setHeightForWidth(vect3_limit_max_z->sizePolicy().hasHeightForWidth());
        vect3_limit_max_z->setSizePolicy(sizePolicy2);

        gridLayout_21->addWidget(vect3_limit_max_z, 5, 2, 1, 1);

        label_114 = new QLabel(groupCheck_limits_enabled);
        label_114->setObjectName(QString::fromUtf8("label_114"));

        gridLayout_21->addWidget(label_114, 3, 0, 1, 1);

        label_117 = new QLabel(groupCheck_limits_enabled);
        label_117->setObjectName(QString::fromUtf8("label_117"));
        sizePolicy1.setHeightForWidth(label_117->sizePolicy().hasHeightForWidth());
        label_117->setSizePolicy(sizePolicy1);
        label_117->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_21->addWidget(label_117, 3, 1, 1, 1);

        label_118 = new QLabel(groupCheck_limits_enabled);
        label_118->setObjectName(QString::fromUtf8("label_118"));
        sizePolicy1.setHeightForWidth(label_118->sizePolicy().hasHeightForWidth());
        label_118->setSizePolicy(sizePolicy1);
        label_118->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_21->addWidget(label_118, 4, 1, 1, 1);

        label_119 = new QLabel(groupCheck_limits_enabled);
        label_119->setObjectName(QString::fromUtf8("label_119"));
        sizePolicy1.setHeightForWidth(label_119->sizePolicy().hasHeightForWidth());
        label_119->setSizePolicy(sizePolicy1);
        label_119->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_21->addWidget(label_119, 5, 1, 1, 1);


        verticalLayout_45->addLayout(gridLayout_21);


        verticalLayout_13->addWidget(groupCheck_limits_enabled);

        groupBox_auto_fog = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox_auto_fog->setObjectName(QString::fromUtf8("groupBox_auto_fog"));
        verticalLayout_autoFog = new QVBoxLayout(groupBox_auto_fog);
        verticalLayout_autoFog->setSpacing(4);
        verticalLayout_autoFog->setObjectName(QString::fromUtf8("verticalLayout_autoFog"));
        verticalLayout_autoFog->setContentsMargins(4, 4, 4, 4);
        horizontalLayout_autoFogQuality = new QHBoxLayout();
        horizontalLayout_autoFogQuality->setObjectName(QString::fromUtf8("horizontalLayout_autoFogQuality"));
        label_auto_fog_quality = new QLabel(groupBox_auto_fog);
        label_auto_fog_quality->setObjectName(QString::fromUtf8("label_auto_fog_quality"));

        horizontalLayout_autoFogQuality->addWidget(label_auto_fog_quality);

        comboBox_auto_fog_quality = new MyComboBox(groupBox_auto_fog);
        comboBox_auto_fog_quality->setObjectName(QString::fromUtf8("comboBox_auto_fog_quality"));

        horizontalLayout_autoFogQuality->addWidget(comboBox_auto_fog_quality);


        verticalLayout_autoFog->addLayout(horizontalLayout_autoFogQuality);

        horizontalLayout_volumetricMaxSteps = new QHBoxLayout();
        horizontalLayout_volumetricMaxSteps->setObjectName(QString::fromUtf8("horizontalLayout_volumetricMaxSteps"));
        label_volumetric_max_steps = new QLabel(groupBox_auto_fog);
        label_volumetric_max_steps->setObjectName(QString::fromUtf8("label_volumetric_max_steps"));

        horizontalLayout_volumetricMaxSteps->addWidget(label_volumetric_max_steps);

        spinboxInt_volumetric_max_steps = new MySpinBox(groupBox_auto_fog);
        spinboxInt_volumetric_max_steps->setObjectName(QString::fromUtf8("spinboxInt_volumetric_max_steps"));
        spinboxInt_volumetric_max_steps->setMaximum(2000);
        spinboxInt_volumetric_max_steps->setValue(96);

        horizontalLayout_volumetricMaxSteps->addWidget(spinboxInt_volumetric_max_steps);


        verticalLayout_autoFog->addLayout(horizontalLayout_volumetricMaxSteps);

        checkBox_volumetric_preview_fast = new MyCheckBox(groupBox_auto_fog);
        checkBox_volumetric_preview_fast->setObjectName(QString::fromUtf8("checkBox_volumetric_preview_fast"));
        checkBox_volumetric_preview_fast->setChecked(true);

        verticalLayout_autoFog->addWidget(checkBox_volumetric_preview_fast);

        horizontalLayout_volumetricPreviewStepMul = new QHBoxLayout();
        horizontalLayout_volumetricPreviewStepMul->setObjectName(QString::fromUtf8("horizontalLayout_volumetricPreviewStepMul"));
        label_volumetric_preview_step_mul = new QLabel(groupBox_auto_fog);
        label_volumetric_preview_step_mul->setObjectName(QString::fromUtf8("label_volumetric_preview_step_mul"));

        horizontalLayout_volumetricPreviewStepMul->addWidget(label_volumetric_preview_step_mul);

        spinbox_volumetric_preview_step_mul = new MyDoubleSpinBox(groupBox_auto_fog);
        spinbox_volumetric_preview_step_mul->setObjectName(QString::fromUtf8("spinbox_volumetric_preview_step_mul"));
        spinbox_volumetric_preview_step_mul->setMinimum(1.000000000000000);
        spinbox_volumetric_preview_step_mul->setMaximum(8.000000000000000);
        spinbox_volumetric_preview_step_mul->setSingleStep(0.100000000000000);
        spinbox_volumetric_preview_step_mul->setValue(2.000000000000000);

        horizontalLayout_volumetricPreviewStepMul->addWidget(spinbox_volumetric_preview_step_mul);


        verticalLayout_autoFog->addLayout(horizontalLayout_volumetricPreviewStepMul);

        checkBox_volumetric_blue_noise_jitter = new MyCheckBox(groupBox_auto_fog);
        checkBox_volumetric_blue_noise_jitter->setObjectName(QString::fromUtf8("checkBox_volumetric_blue_noise_jitter"));
        checkBox_volumetric_blue_noise_jitter->setChecked(true);

        verticalLayout_autoFog->addWidget(checkBox_volumetric_blue_noise_jitter);

        horizontalLayout_volumetricJitterStrength = new QHBoxLayout();
        horizontalLayout_volumetricJitterStrength->setObjectName(QString::fromUtf8("horizontalLayout_volumetricJitterStrength"));
        label_volumetric_jitter_strength = new QLabel(groupBox_auto_fog);
        label_volumetric_jitter_strength->setObjectName(QString::fromUtf8("label_volumetric_jitter_strength"));

        horizontalLayout_volumetricJitterStrength->addWidget(label_volumetric_jitter_strength);

        spinbox_volumetric_jitter_strength = new MyDoubleSpinBox(groupBox_auto_fog);
        spinbox_volumetric_jitter_strength->setObjectName(QString::fromUtf8("spinbox_volumetric_jitter_strength"));
        spinbox_volumetric_jitter_strength->setDecimals(1);
        spinbox_volumetric_jitter_strength->setMaximum(10.000000000000000);
        spinbox_volumetric_jitter_strength->setValue(2.000000000000000);

        horizontalLayout_volumetricJitterStrength->addWidget(spinbox_volumetric_jitter_strength);


        verticalLayout_autoFog->addLayout(horizontalLayout_volumetricJitterStrength);

        horizontalLayout_autoFogButtons2 = new QHBoxLayout();
        horizontalLayout_autoFogButtons2->setObjectName(QString::fromUtf8("horizontalLayout_autoFogButtons2"));
        pushButton_auto_clouds = new QPushButton(groupBox_auto_fog);
        pushButton_auto_clouds->setObjectName(QString::fromUtf8("pushButton_auto_clouds"));

        horizontalLayout_autoFogButtons2->addWidget(pushButton_auto_clouds);


        verticalLayout_autoFog->addLayout(horizontalLayout_autoFogButtons2);

        horizontalLayout_autoFogButtons = new QHBoxLayout();
        horizontalLayout_autoFogButtons->setObjectName(QString::fromUtf8("horizontalLayout_autoFogButtons"));
        pushButton_auto_iteration_fog = new QPushButton(groupBox_auto_fog);
        pushButton_auto_iteration_fog->setObjectName(QString::fromUtf8("pushButton_auto_iteration_fog"));

        horizontalLayout_autoFogButtons->addWidget(pushButton_auto_iteration_fog);

        pushButton_auto_volumetric_fog = new QPushButton(groupBox_auto_fog);
        pushButton_auto_volumetric_fog->setObjectName(QString::fromUtf8("pushButton_auto_volumetric_fog"));

        horizontalLayout_autoFogButtons->addWidget(pushButton_auto_volumetric_fog);

        pushButton_auto_all_fog = new QPushButton(groupBox_auto_fog);
        pushButton_auto_all_fog->setObjectName(QString::fromUtf8("pushButton_auto_all_fog"));

        horizontalLayout_autoFogButtons->addWidget(pushButton_auto_all_fog);


        verticalLayout_autoFog->addLayout(horizontalLayout_autoFogButtons);

        label_auto_fog_result = new QLabel(groupBox_auto_fog);
        label_auto_fog_result->setObjectName(QString::fromUtf8("label_auto_fog_result"));
        label_auto_fog_result->setWordWrap(true);

        verticalLayout_autoFog->addWidget(label_auto_fog_result);


        verticalLayout_13->addWidget(groupBox_auto_fog);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_2);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_4->addWidget(scrollArea_3);


        retranslateUi(cRenderingLimitsTab);

        QMetaObject::connectSlotsByName(cRenderingLimitsTab);
    } // setupUi

    void retranslateUi(QWidget *cRenderingLimitsTab)
    {
        groupBox_4->setTitle(QCoreApplication::translate("cRenderingLimitsTab", "View distance limits", nullptr));
        label_108->setText(QCoreApplication::translate("cRenderingLimitsTab", "minimum view distance:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_view_distance_min->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "<html><head/><body><p>All objects closer than this distance won't be visible</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_107->setText(QCoreApplication::translate("cRenderingLimitsTab", "maximum view distance:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_view_distance_max->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "<html><head/><body><p>Defines visibility distance. All objects farther  than this distance won't be visible. </p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        groupCheck_limits_enabled->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "<html><head/><body><p>Enables rendering of fractal cross sections.</p><p>Example cross sections of Buffalo fractal:</p><table border=\"0\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px;\" cellspacing=\"2\" cellpadding=\"0\"><tr><td><p>x = {-10; 10}, y = {-10, 10}, z = {-10, 0}</p></td><td><p>x = {-10, 0}, y = {0, 10}, z = {-0.1; 0.1}</p></td></tr><tr><td><p><img src=\":/tooltips/tooltips_images/image - limits z.jpeg\"/></p></td><td><p><img src=\":/tooltips/tooltips_images/image - limits x, y, z.jpeg\"/></p></td></tr></table></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_limits_enabled->setTitle(QCoreApplication::translate("cRenderingLimitsTab", "Limits (bounding bo&x)", nullptr));
#if QT_CONFIG(tooltip)
        bu_bounding_box_to_limit->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "<html><head/><body><p>Calculates the bounding box of the fractal and sets these as the limit values. This can be helpful to automatically set the limits for the voxel export</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_bounding_box_to_limit->setText(QCoreApplication::translate("cRenderingLimitsTab", "Bounding Box to limit", nullptr));
        label_maximum_bounding_boy->setText(QCoreApplication::translate("cRenderingLimitsTab", "maximum bounding box:", nullptr));
        label_bounding_box_limit_manioulation->setText(QCoreApplication::translate("cRenderingLimitsTab", "Resize and move the bounding box axes:", nullptr));
        bounding_box_x_label->setText(QCoreApplication::translate("cRenderingLimitsTab", "X", nullptr));
        bounding_box_y_label->setText(QCoreApplication::translate("cRenderingLimitsTab", "Y", nullptr));
        bounding_box_z_label->setText(QCoreApplication::translate("cRenderingLimitsTab", "Z", nullptr));
        label_110->setText(QCoreApplication::translate("cRenderingLimitsTab", "x:", nullptr));
        label_109->setText(QCoreApplication::translate("cRenderingLimitsTab", "bottom left front corner:", nullptr));
        label_111->setText(QCoreApplication::translate("cRenderingLimitsTab", "y:", nullptr));
        label_112->setText(QCoreApplication::translate("cRenderingLimitsTab", "z:", nullptr));
        label_114->setText(QCoreApplication::translate("cRenderingLimitsTab", "top right back corner:", nullptr));
        label_117->setText(QCoreApplication::translate("cRenderingLimitsTab", "x:", nullptr));
        label_118->setText(QCoreApplication::translate("cRenderingLimitsTab", "y:", nullptr));
        label_119->setText(QCoreApplication::translate("cRenderingLimitsTab", "z:", nullptr));
        groupBox_auto_fog->setTitle(QCoreApplication::translate("cRenderingLimitsTab", "Auto fog tuning", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_auto_fog->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Probe the current view and auto-tune fog parameters. Uses a small off-screen render to measure iteration and distance statistics, then applies fractal-class modifiers (Mandelbox, Kleinian, etc.). Basic and iteration fog toggle instantly in the Full OpenCL engine; clouds and volumetric fog may trigger a kernel recompile when enabled.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_auto_fog_quality->setText(QCoreApplication::translate("cRenderingLimitsTab", "Probe quality:", nullptr));
#if QT_CONFIG(tooltip)
        label_auto_fog_quality->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Resolution of the probe render used to measure fog statistics. Preview is fastest; Cinematic is slowest but most accurate for final tuning.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        comboBox_auto_fog_quality->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Preview = 16\303\22716 probe, 48 volumetric steps. Balanced = 32\303\22732 probe, 96 steps (default). Cinematic = 48\303\22748 probe, 192 steps. Higher quality gives more reliable auto-tuning but takes longer.", nullptr));
#endif // QT_CONFIG(tooltip)
        label_volumetric_max_steps->setText(QCoreApplication::translate("cRenderingLimitsTab", "Volumetric max steps:", nullptr));
#if QT_CONFIG(tooltip)
        label_volumetric_max_steps->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Maximum ray-marching steps for all volumetric effects (fog, clouds, glow). Lower = faster preview; higher = fewer banding artifacts. 0 = follow probe quality defaults.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinboxInt_volumetric_max_steps->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Caps volumetric ray steps per pixel (0 = auto from probe quality: Preview 48, Balanced 96, Cinematic 192). Rendering stops early when transmittance is nearly zero.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_volumetric_preview_fast->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "When the main preview is downscaled (Preview scale > 1:1), march volumetric effects with fewer, larger steps for faster navigation. Final renders at 1:1 are unaffected.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_volumetric_preview_fast->setText(QCoreApplication::translate("cRenderingLimitsTab", "Fast volumetric preview", nullptr));
        label_volumetric_preview_step_mul->setText(QCoreApplication::translate("cRenderingLimitsTab", "Preview step multiplier:", nullptr));
#if QT_CONFIG(tooltip)
        label_volumetric_preview_step_mul->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Larger steps during preview volumetric marching (2 = half the samples). Preview is upscaled by the existing Preview scale control.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_volumetric_preview_step_mul->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Step size multiplier while fast preview is active. Increase for speed, decrease for smoother fog during navigation.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_volumetric_blue_noise_jitter->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Use IGN (interleaved gradient noise) for volumetric step jitter instead of white noise. Reduces banding and sparkle in fog, clouds, and glow marching.", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_volumetric_blue_noise_jitter->setText(QCoreApplication::translate("cRenderingLimitsTab", "Blue-noise volumetric jitter", nullptr));
        label_volumetric_jitter_strength->setText(QCoreApplication::translate("cRenderingLimitsTab", "Jitter strength (%):", nullptr));
#if QT_CONFIG(tooltip)
        label_volumetric_jitter_strength->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "How much each volumetric march step is randomly shortened (0 = off, 2 = default). Higher values reduce banding faster but add more noise.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        spinbox_volumetric_jitter_strength->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Percentage of step-size variation applied per volumetric sample. Works with both blue-noise and white-noise jitter modes.", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pushButton_auto_clouds->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Applies the \"Volumetric Clouds\" preset (softer opacity, moderate sharpness, adaptive stepping) and enables clouds. Note: enabling clouds in OpenCL may recompile the render kernel.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_auto_clouds->setText(QCoreApplication::translate("cRenderingLimitsTab", "Auto Clouds", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_auto_iteration_fog->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Probe the scene and tune iteration fog (trim, opacity, color thresholds) using percentile statistics plus fractal-class modifiers. Results appear below. In Full OpenCL engine, toggling iteration fog afterward is instant (no kernel rebuild).", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_auto_iteration_fog->setText(QCoreApplication::translate("cRenderingLimitsTab", "Auto Iteration Fog", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_auto_volumetric_fog->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Probe the scene and tune distance-based volumetric fog (density, distance factor, surface offset). Enabling volumetric fog in OpenCL may recompile the render kernel.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_auto_volumetric_fog->setText(QCoreApplication::translate("cRenderingLimitsTab", "Auto Volumetric Fog", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_auto_all_fog->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Runs iteration fog, volumetric fog, and basic fog auto-tuning in one pass using the selected probe quality.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_auto_all_fog->setText(QCoreApplication::translate("cRenderingLimitsTab", "Auto All Fog", nullptr));
        label_auto_fog_result->setText(QCoreApplication::translate("cRenderingLimitsTab", "-", nullptr));
#if QT_CONFIG(tooltip)
        label_auto_fog_result->setToolTip(QCoreApplication::translate("cRenderingLimitsTab", "Summary of the last auto-fog probe: detected fractal modifiers, tuned parameter values, and probe timing.", nullptr));
#endif // QT_CONFIG(tooltip)
        (void)cRenderingLimitsTab;
    } // retranslateUi

};

namespace Ui {
    class cRenderingLimitsTab: public Ui_cRenderingLimitsTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERING_LIMITS_TAB_H
