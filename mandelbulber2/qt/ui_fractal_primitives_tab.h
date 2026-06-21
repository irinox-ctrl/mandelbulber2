/********************************************************************************
** Form generated from reading UI file 'fractal_primitives_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRACTAL_PRIMITIVES_TAB_H
#define UI_FRACTAL_PRIMITIVES_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "buton_load_settings_from_widget.h"
#include "buton_random_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "my_check_box.h"
#include "my_double_spin_box.h"
#include "my_line_edit.h"
#include "primitives_manager.h"

QT_BEGIN_NAMESPACE

class Ui_cFractalPrimitivesTab
{
public:
    QVBoxLayout *verticalLayout_25;
    QHBoxLayout *horizontalLayout;
    cButtonRandomSettingsFromWidget *pushButton_local_randomize_7;
    QSpacerItem *horizontalSpacer;
    QScrollArea *scrollArea_primitives;
    QWidget *scrollAreaWidgetContents_primitives;
    QVBoxLayout *verticalLayout_74;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_5;
    QGridLayout *gridLayout_37;
    MyLineEdit *vect3_all_primitives_position_z;
    MyDoubleSpinBox *spinboxd3_all_primitives_rotation_x;
    QLabel *label_50;
    QLabel *label_141;
    QLabel *label_142;
    MyLineEdit *vect3_all_primitives_position_x;
    MyLineEdit *vect3_all_primitives_position_y;
    QLabel *label_49;
    QLabel *label_144;
    MyDoubleSpinBox *spinboxd3_all_primitives_rotation_y;
    MyDoubleSpinBox *spinboxd3_all_primitives_rotation_z;
    QLabel *label_51;
    QLabel *label_143;
    MyCheckBox *checkBox_all_primitives_invisible_alpha;
    cPrimitivesManager *widgetPrimitivesManager;
    QVBoxLayout *verticalLayout_primitives;
    QSpacerItem *verticalSpacer_9;

    void setupUi(QWidget *cFractalPrimitivesTab)
    {
        if (cFractalPrimitivesTab->objectName().isEmpty())
            cFractalPrimitivesTab->setObjectName(QString::fromUtf8("cFractalPrimitivesTab"));
        verticalLayout_25 = new QVBoxLayout(cFractalPrimitivesTab);
        verticalLayout_25->setSpacing(2);
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        verticalLayout_25->setContentsMargins(2, 2, 2, 2);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_local_randomize_7 = new cButtonRandomSettingsFromWidget(cFractalPrimitivesTab);
        pushButton_local_randomize_7->setObjectName(QString::fromUtf8("pushButton_local_randomize_7"));

        horizontalLayout->addWidget(pushButton_local_randomize_7);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_25->addLayout(horizontalLayout);

        scrollArea_primitives = new QScrollArea(cFractalPrimitivesTab);
        scrollArea_primitives->setObjectName(QString::fromUtf8("scrollArea_primitives"));
        scrollArea_primitives->setWidgetResizable(true);
        scrollAreaWidgetContents_primitives = new QWidget();
        scrollAreaWidgetContents_primitives->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_primitives"));
        scrollAreaWidgetContents_primitives->setGeometry(QRect(0, 0, 459, 840));
        verticalLayout_74 = new QVBoxLayout(scrollAreaWidgetContents_primitives);
        verticalLayout_74->setSpacing(2);
        verticalLayout_74->setObjectName(QString::fromUtf8("verticalLayout_74"));
        verticalLayout_74->setContentsMargins(2, 2, 2, 2);
        groupBox_4 = new QGroupBox(scrollAreaWidgetContents_primitives);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_5 = new QVBoxLayout(groupBox_4);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(2, 2, 2, 2);
        gridLayout_37 = new QGridLayout();
        gridLayout_37->setSpacing(2);
        gridLayout_37->setObjectName(QString::fromUtf8("gridLayout_37"));
        vect3_all_primitives_position_z = new MyLineEdit(groupBox_4);
        vect3_all_primitives_position_z->setObjectName(QString::fromUtf8("vect3_all_primitives_position_z"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(vect3_all_primitives_position_z->sizePolicy().hasHeightForWidth());
        vect3_all_primitives_position_z->setSizePolicy(sizePolicy);

        gridLayout_37->addWidget(vect3_all_primitives_position_z, 2, 2, 1, 1);

        spinboxd3_all_primitives_rotation_x = new MyDoubleSpinBox(groupBox_4);
        spinboxd3_all_primitives_rotation_x->setObjectName(QString::fromUtf8("spinboxd3_all_primitives_rotation_x"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinboxd3_all_primitives_rotation_x->sizePolicy().hasHeightForWidth());
        spinboxd3_all_primitives_rotation_x->setSizePolicy(sizePolicy1);
        spinboxd3_all_primitives_rotation_x->setDecimals(2);
        spinboxd3_all_primitives_rotation_x->setMinimum(-36000.000000000000000);
        spinboxd3_all_primitives_rotation_x->setMaximum(36000.000000000000000);
        spinboxd3_all_primitives_rotation_x->setSingleStep(0.100000000000000);

        gridLayout_37->addWidget(spinboxd3_all_primitives_rotation_x, 3, 2, 1, 1);

        label_50 = new QLabel(groupBox_4);
        label_50->setObjectName(QString::fromUtf8("label_50"));

        gridLayout_37->addWidget(label_50, 4, 0, 1, 1);

        label_141 = new QLabel(groupBox_4);
        label_141->setObjectName(QString::fromUtf8("label_141"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_141->sizePolicy().hasHeightForWidth());
        label_141->setSizePolicy(sizePolicy2);
        label_141->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_37->addWidget(label_141, 2, 1, 1, 1);

        label_142 = new QLabel(groupBox_4);
        label_142->setObjectName(QString::fromUtf8("label_142"));
        sizePolicy2.setHeightForWidth(label_142->sizePolicy().hasHeightForWidth());
        label_142->setSizePolicy(sizePolicy2);
        label_142->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_37->addWidget(label_142, 0, 1, 1, 1);

        vect3_all_primitives_position_x = new MyLineEdit(groupBox_4);
        vect3_all_primitives_position_x->setObjectName(QString::fromUtf8("vect3_all_primitives_position_x"));
        sizePolicy.setHeightForWidth(vect3_all_primitives_position_x->sizePolicy().hasHeightForWidth());
        vect3_all_primitives_position_x->setSizePolicy(sizePolicy);

        gridLayout_37->addWidget(vect3_all_primitives_position_x, 0, 2, 1, 1);

        vect3_all_primitives_position_y = new MyLineEdit(groupBox_4);
        vect3_all_primitives_position_y->setObjectName(QString::fromUtf8("vect3_all_primitives_position_y"));
        sizePolicy.setHeightForWidth(vect3_all_primitives_position_y->sizePolicy().hasHeightForWidth());
        vect3_all_primitives_position_y->setSizePolicy(sizePolicy);

        gridLayout_37->addWidget(vect3_all_primitives_position_y, 1, 2, 1, 1);

        label_49 = new QLabel(groupBox_4);
        label_49->setObjectName(QString::fromUtf8("label_49"));

        gridLayout_37->addWidget(label_49, 3, 0, 1, 1);

        label_144 = new QLabel(groupBox_4);
        label_144->setObjectName(QString::fromUtf8("label_144"));
        sizePolicy2.setHeightForWidth(label_144->sizePolicy().hasHeightForWidth());
        label_144->setSizePolicy(sizePolicy2);
        label_144->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_37->addWidget(label_144, 1, 1, 1, 1);

        spinboxd3_all_primitives_rotation_y = new MyDoubleSpinBox(groupBox_4);
        spinboxd3_all_primitives_rotation_y->setObjectName(QString::fromUtf8("spinboxd3_all_primitives_rotation_y"));
        sizePolicy1.setHeightForWidth(spinboxd3_all_primitives_rotation_y->sizePolicy().hasHeightForWidth());
        spinboxd3_all_primitives_rotation_y->setSizePolicy(sizePolicy1);
        spinboxd3_all_primitives_rotation_y->setDecimals(2);
        spinboxd3_all_primitives_rotation_y->setMinimum(-36000.000000000000000);
        spinboxd3_all_primitives_rotation_y->setMaximum(36000.000000000000000);
        spinboxd3_all_primitives_rotation_y->setSingleStep(0.100000000000000);

        gridLayout_37->addWidget(spinboxd3_all_primitives_rotation_y, 4, 2, 1, 1);

        spinboxd3_all_primitives_rotation_z = new MyDoubleSpinBox(groupBox_4);
        spinboxd3_all_primitives_rotation_z->setObjectName(QString::fromUtf8("spinboxd3_all_primitives_rotation_z"));
        sizePolicy1.setHeightForWidth(spinboxd3_all_primitives_rotation_z->sizePolicy().hasHeightForWidth());
        spinboxd3_all_primitives_rotation_z->setSizePolicy(sizePolicy1);
        spinboxd3_all_primitives_rotation_z->setDecimals(2);
        spinboxd3_all_primitives_rotation_z->setMinimum(-36000.000000000000000);
        spinboxd3_all_primitives_rotation_z->setMaximum(36000.000000000000000);
        spinboxd3_all_primitives_rotation_z->setSingleStep(0.100000000000000);

        gridLayout_37->addWidget(spinboxd3_all_primitives_rotation_z, 5, 2, 1, 1);

        label_51 = new QLabel(groupBox_4);
        label_51->setObjectName(QString::fromUtf8("label_51"));

        gridLayout_37->addWidget(label_51, 5, 0, 1, 1);

        label_143 = new QLabel(groupBox_4);
        label_143->setObjectName(QString::fromUtf8("label_143"));

        gridLayout_37->addWidget(label_143, 0, 0, 3, 1);


        verticalLayout_5->addLayout(gridLayout_37);


        verticalLayout_74->addWidget(groupBox_4);

        checkBox_all_primitives_invisible_alpha = new MyCheckBox(scrollAreaWidgetContents_primitives);
        checkBox_all_primitives_invisible_alpha->setObjectName(QString::fromUtf8("checkBox_all_primitives_invisible_alpha"));

        verticalLayout_74->addWidget(checkBox_all_primitives_invisible_alpha);

        widgetPrimitivesManager = new cPrimitivesManager(scrollAreaWidgetContents_primitives);
        widgetPrimitivesManager->setObjectName(QString::fromUtf8("widgetPrimitivesManager"));

        verticalLayout_74->addWidget(widgetPrimitivesManager);

        verticalLayout_primitives = new QVBoxLayout();
        verticalLayout_primitives->setSpacing(2);
        verticalLayout_primitives->setObjectName(QString::fromUtf8("verticalLayout_primitives"));

        verticalLayout_74->addLayout(verticalLayout_primitives);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_74->addItem(verticalSpacer_9);

        scrollArea_primitives->setWidget(scrollAreaWidgetContents_primitives);

        verticalLayout_25->addWidget(scrollArea_primitives);


        retranslateUi(cFractalPrimitivesTab);

        QMetaObject::connectSlotsByName(cFractalPrimitivesTab);
    } // setupUi

    void retranslateUi(QWidget *cFractalPrimitivesTab)
    {
        pushButton_local_randomize_7->setText(QCoreApplication::translate("cFractalPrimitivesTab", "Randomize", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("cFractalPrimitivesTab", "Global positioning of all primitives", nullptr));
        spinboxd3_all_primitives_rotation_x->setPrefix(QString());
        spinboxd3_all_primitives_rotation_x->setSuffix(QString());
        label_50->setText(QCoreApplication::translate("cFractalPrimitivesTab", "Y-axis rotation:", nullptr));
        label_141->setText(QCoreApplication::translate("cFractalPrimitivesTab", "z:", nullptr));
        label_142->setText(QCoreApplication::translate("cFractalPrimitivesTab", "x:", nullptr));
        label_49->setText(QCoreApplication::translate("cFractalPrimitivesTab", "X-axis rotation:", nullptr));
        label_144->setText(QCoreApplication::translate("cFractalPrimitivesTab", "y:", nullptr));
        spinboxd3_all_primitives_rotation_y->setPrefix(QString());
        spinboxd3_all_primitives_rotation_y->setSuffix(QString());
        spinboxd3_all_primitives_rotation_z->setPrefix(QString());
        spinboxd3_all_primitives_rotation_z->setSuffix(QString());
        label_51->setText(QCoreApplication::translate("cFractalPrimitivesTab", "Z-axis rotation:", nullptr));
        label_143->setText(QCoreApplication::translate("cFractalPrimitivesTab", "all primitives\n"
"position\n"
"(except plane\n"
"and water):", nullptr));
        checkBox_all_primitives_invisible_alpha->setText(QCoreApplication::translate("cFractalPrimitivesTab", "Invisible primitives in alpha channel\n"
"with visible shadows of fractal objects", nullptr));
        (void)cFractalPrimitivesTab;
    } // retranslateUi

};

namespace Ui {
    class cFractalPrimitivesTab: public Ui_cFractalPrimitivesTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRACTAL_PRIMITIVES_TAB_H
