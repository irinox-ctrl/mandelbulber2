/********************************************************************************
** Form generated from reading UI file 'material_editor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MATERIAL_EDITOR_H
#define UI_MATERIAL_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <material_editor_panel.h>
#include "buton_random_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "file_select_widget.h"
#include "gradient_edit_widget.h"
#include "material_widget.h"
#include "my_check_box.h"
#include "my_color_button.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cMaterialEditor
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    cButtonResetSettingsFromWidget *pushButton_local_reset_2;
    cButtonRandomSettingsFromWidget *pushButton_local_randomize_7;
    QPushButton *pushButton_local_navi;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    cMaterialWidget *widget_material_preview;
    QLabel *label_358;
    MyLineEdit *text_name;
    cMaterialEditorPanel *widget_material_editor_panel;

    void setupUi(QWidget *cMaterialEditor)
    {
        if (cMaterialEditor->objectName().isEmpty())
            cMaterialEditor->setObjectName(QString::fromUtf8("cMaterialEditor"));
        cMaterialEditor->resize(492, 1179);
        verticalLayout = new QVBoxLayout(cMaterialEditor);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_local_reset_2 = new cButtonResetSettingsFromWidget(cMaterialEditor);
        pushButton_local_reset_2->setObjectName(QString::fromUtf8("pushButton_local_reset_2"));

        horizontalLayout_3->addWidget(pushButton_local_reset_2);

        pushButton_local_randomize_7 = new cButtonRandomSettingsFromWidget(cMaterialEditor);
        pushButton_local_randomize_7->setObjectName(QString::fromUtf8("pushButton_local_randomize_7"));

        horizontalLayout_3->addWidget(pushButton_local_randomize_7);

        pushButton_local_navi = new QPushButton(cMaterialEditor);
        pushButton_local_navi->setObjectName(QString::fromUtf8("pushButton_local_navi"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_local_navi->sizePolicy().hasHeightForWidth());
        pushButton_local_navi->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(pushButton_local_navi);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 5, -1, -1);
        widget_material_preview = new cMaterialWidget(cMaterialEditor);
        widget_material_preview->setObjectName(QString::fromUtf8("widget_material_preview"));
        QSizePolicy sizePolicy1(QSizePolicy::Maximum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widget_material_preview->sizePolicy().hasHeightForWidth());
        widget_material_preview->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(widget_material_preview);

        label_358 = new QLabel(cMaterialEditor);
        label_358->setObjectName(QString::fromUtf8("label_358"));

        horizontalLayout_2->addWidget(label_358);

        text_name = new MyLineEdit(cMaterialEditor);
        text_name->setObjectName(QString::fromUtf8("text_name"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(text_name->sizePolicy().hasHeightForWidth());
        text_name->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(text_name);

        horizontalLayout_2->setStretch(2, 1);

        verticalLayout->addLayout(horizontalLayout_2);

        widget_material_editor_panel = new cMaterialEditorPanel(cMaterialEditor);
        widget_material_editor_panel->setObjectName(QString::fromUtf8("widget_material_editor_panel"));

        verticalLayout->addWidget(widget_material_editor_panel);


        retranslateUi(cMaterialEditor);

        QMetaObject::connectSlotsByName(cMaterialEditor);
    } // setupUi

    void retranslateUi(QWidget *cMaterialEditor)
    {
        cMaterialEditor->setWindowTitle(QCoreApplication::translate("cMaterialEditor", "Form", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_local_reset_2->setToolTip(QCoreApplication::translate("cMaterialEditor", "Restores all material parameters in the editor to their default values. ", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_local_reset_2->setText(QCoreApplication::translate("cMaterialEditor", "Reset", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_local_randomize_7->setToolTip(QCoreApplication::translate("cMaterialEditor", "Randomizes material parameters to generate a new, unique material appearance. Useful for exploring creative variations quickly.", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_local_randomize_7->setText(QCoreApplication::translate("cMaterialEditor", "Randomize", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_local_navi->setToolTip(QCoreApplication::translate("cMaterialEditor", "<html><head/><body><p>Opens navigator window which allows changes to material parameters with instant preview.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_local_navi->setText(QCoreApplication::translate("cMaterialEditor", "Navi", nullptr));
        label_358->setText(QCoreApplication::translate("cMaterialEditor", "Material name:", nullptr));
#if QT_CONFIG(tooltip)
        text_name->setToolTip(QCoreApplication::translate("cMaterialEditor", "<html><head/><body><p>Material name used in Material Manager</p><p>Tip: Well named materials will be easier to find in Material Manager</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
    } // retranslateUi

};

namespace Ui {
    class cMaterialEditor: public Ui_cMaterialEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MATERIAL_EDITOR_H
