/********************************************************************************
** Form generated from reading UI file 'dock_pattern_lines.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_PATTERN_LINES_H
#define UI_DOCK_PATTERN_LINES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <pattern_lines_traps_panel.h>
#include "buton_load_settings_from_widget.h"
#include "buton_random_settings_from_widget.h"
#include "buton_reset_settings_from_widget.h"
#include "buton_save_settings_from_widget.h"
#include "my_check_box.h"
#include "my_color_button.h"
#include "my_combo_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cDockPatternLines
{
public:
    QVBoxLayout *verticalLayout_pattern_dock_root;
    QHBoxLayout *horizontalLayout_pattern_dock_tools;
    cButtonLoadSettingsFromWidget *pushButton_pattern_dock_load;
    cButtonSaveSettingsFromWidget *pushButton_pattern_dock_save;
    cButtonResetSettingsFromWidget *pushButton_pattern_dock_reset;
    cButtonRandomSettingsFromWidget *pushButton_pattern_dock_randomize;
    QPushButton *pushButton_pattern_dock_navi;
    QSpacerItem *horizontalSpacer_pattern_dock;
    cPatternLinesTrapsPanel *widget_pattern_lines_traps_panel;

    void setupUi(QWidget *cDockPatternLines)
    {
        if (cDockPatternLines->objectName().isEmpty())
            cDockPatternLines->setObjectName(QString::fromUtf8("cDockPatternLines"));
        cDockPatternLines->resize(480, 900);
        verticalLayout_pattern_dock_root = new QVBoxLayout(cDockPatternLines);
        verticalLayout_pattern_dock_root->setSpacing(2);
        verticalLayout_pattern_dock_root->setObjectName(QString::fromUtf8("verticalLayout_pattern_dock_root"));
        verticalLayout_pattern_dock_root->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_pattern_dock_tools = new QHBoxLayout();
        horizontalLayout_pattern_dock_tools->setObjectName(QString::fromUtf8("horizontalLayout_pattern_dock_tools"));
        pushButton_pattern_dock_load = new cButtonLoadSettingsFromWidget(cDockPatternLines);
        pushButton_pattern_dock_load->setObjectName(QString::fromUtf8("pushButton_pattern_dock_load"));

        horizontalLayout_pattern_dock_tools->addWidget(pushButton_pattern_dock_load);

        pushButton_pattern_dock_save = new cButtonSaveSettingsFromWidget(cDockPatternLines);
        pushButton_pattern_dock_save->setObjectName(QString::fromUtf8("pushButton_pattern_dock_save"));

        horizontalLayout_pattern_dock_tools->addWidget(pushButton_pattern_dock_save);

        pushButton_pattern_dock_reset = new cButtonResetSettingsFromWidget(cDockPatternLines);
        pushButton_pattern_dock_reset->setObjectName(QString::fromUtf8("pushButton_pattern_dock_reset"));

        horizontalLayout_pattern_dock_tools->addWidget(pushButton_pattern_dock_reset);

        pushButton_pattern_dock_randomize = new cButtonRandomSettingsFromWidget(cDockPatternLines);
        pushButton_pattern_dock_randomize->setObjectName(QString::fromUtf8("pushButton_pattern_dock_randomize"));

        horizontalLayout_pattern_dock_tools->addWidget(pushButton_pattern_dock_randomize);

        pushButton_pattern_dock_navi = new QPushButton(cDockPatternLines);
        pushButton_pattern_dock_navi->setObjectName(QString::fromUtf8("pushButton_pattern_dock_navi"));
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_pattern_dock_navi->sizePolicy().hasHeightForWidth());
        pushButton_pattern_dock_navi->setSizePolicy(sizePolicy);

        horizontalLayout_pattern_dock_tools->addWidget(pushButton_pattern_dock_navi);

        horizontalSpacer_pattern_dock = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_pattern_dock_tools->addItem(horizontalSpacer_pattern_dock);


        verticalLayout_pattern_dock_root->addLayout(horizontalLayout_pattern_dock_tools);

        widget_pattern_lines_traps_panel = new cPatternLinesTrapsPanel(cDockPatternLines);
        widget_pattern_lines_traps_panel->setObjectName(QString::fromUtf8("widget_pattern_lines_traps_panel"));

        verticalLayout_pattern_dock_root->addWidget(widget_pattern_lines_traps_panel);

        verticalLayout_pattern_dock_root->setStretch(1, 1);

        retranslateUi(cDockPatternLines);

        QMetaObject::connectSlotsByName(cDockPatternLines);
    } // setupUi

    void retranslateUi(QWidget *cDockPatternLines)
    {
        cDockPatternLines->setWindowTitle(QCoreApplication::translate("cDockPatternLines", "Form", nullptr));
        pushButton_pattern_dock_load->setText(QCoreApplication::translate("cDockPatternLines", "Laden", nullptr));
        pushButton_pattern_dock_save->setText(QCoreApplication::translate("cDockPatternLines", "Opslaan", nullptr));
        pushButton_pattern_dock_reset->setText(QCoreApplication::translate("cDockPatternLines", "Reset", nullptr));
        pushButton_pattern_dock_randomize->setText(QCoreApplication::translate("cDockPatternLines", "Randomize", nullptr));
        pushButton_pattern_dock_navi->setText(QCoreApplication::translate("cDockPatternLines", "Navi", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDockPatternLines: public Ui_cDockPatternLines {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_PATTERN_LINES_H
