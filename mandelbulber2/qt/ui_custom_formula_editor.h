/********************************************************************************
** Form generated from reading UI file 'custom_formula_editor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOM_FORMULA_EDITOR_H
#define UI_CUSTOM_FORMULA_EDITOR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_text_edit.h"

QT_BEGIN_NAMESPACE

class Ui_cCustomFormulaEditor
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_new;
    QPushButton *pushButton_load_builtin;
    QPushButton *pushButton_load_from_file;
    QPushButton *pushButton_save_to_file;
    QGroupBox *groupBox_parameters;
    QFormLayout *formLayoutParameters;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_auto_format;
    QPushButton *pushButton_check_syntax;
    QPushButton *pushButton_insert_parameter;
    QLabel *label_errors;
    QListWidget *listWidget_errors;
    cMyTextEdit *textEdit_formula_code;
    QLabel *label_lineColumn;

    void setupUi(QWidget *cCustomFormulaEditor)
    {
        if (cCustomFormulaEditor->objectName().isEmpty())
            cCustomFormulaEditor->setObjectName(QString::fromUtf8("cCustomFormulaEditor"));
        cCustomFormulaEditor->resize(498, 932);
        verticalLayout = new QVBoxLayout(cCustomFormulaEditor);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_new = new QPushButton(cCustomFormulaEditor);
        pushButton_new->setObjectName(QString::fromUtf8("pushButton_new"));

        horizontalLayout->addWidget(pushButton_new);

        pushButton_load_builtin = new QPushButton(cCustomFormulaEditor);
        pushButton_load_builtin->setObjectName(QString::fromUtf8("pushButton_load_builtin"));

        horizontalLayout->addWidget(pushButton_load_builtin);

        pushButton_load_from_file = new QPushButton(cCustomFormulaEditor);
        pushButton_load_from_file->setObjectName(QString::fromUtf8("pushButton_load_from_file"));

        horizontalLayout->addWidget(pushButton_load_from_file);

        pushButton_save_to_file = new QPushButton(cCustomFormulaEditor);
        pushButton_save_to_file->setObjectName(QString::fromUtf8("pushButton_save_to_file"));

        horizontalLayout->addWidget(pushButton_save_to_file);


        verticalLayout->addLayout(horizontalLayout);

        groupBox_parameters = new QGroupBox(cCustomFormulaEditor);
        groupBox_parameters->setObjectName(QString::fromUtf8("groupBox_parameters"));
        formLayoutParameters = new QFormLayout(groupBox_parameters);
        formLayoutParameters->setObjectName(QString::fromUtf8("formLayoutParameters"));
        formLayoutParameters->setHorizontalSpacing(2);
        formLayoutParameters->setVerticalSpacing(2);
        formLayoutParameters->setContentsMargins(2, 2, 2, 2);

        verticalLayout->addWidget(groupBox_parameters);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_auto_format = new QPushButton(cCustomFormulaEditor);
        pushButton_auto_format->setObjectName(QString::fromUtf8("pushButton_auto_format"));

        horizontalLayout_2->addWidget(pushButton_auto_format);

        pushButton_check_syntax = new QPushButton(cCustomFormulaEditor);
        pushButton_check_syntax->setObjectName(QString::fromUtf8("pushButton_check_syntax"));

        horizontalLayout_2->addWidget(pushButton_check_syntax);

        pushButton_insert_parameter = new QPushButton(cCustomFormulaEditor);
        pushButton_insert_parameter->setObjectName(QString::fromUtf8("pushButton_insert_parameter"));

        horizontalLayout_2->addWidget(pushButton_insert_parameter);


        verticalLayout->addLayout(horizontalLayout_2);

        label_errors = new QLabel(cCustomFormulaEditor);
        label_errors->setObjectName(QString::fromUtf8("label_errors"));

        verticalLayout->addWidget(label_errors);

        listWidget_errors = new QListWidget(cCustomFormulaEditor);
        listWidget_errors->setObjectName(QString::fromUtf8("listWidget_errors"));
        listWidget_errors->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        listWidget_errors->setResizeMode(QListView::Fixed);
        listWidget_errors->setWordWrap(true);

        verticalLayout->addWidget(listWidget_errors);

        textEdit_formula_code = new cMyTextEdit(cCustomFormulaEditor);
        textEdit_formula_code->setObjectName(QString::fromUtf8("textEdit_formula_code"));
        textEdit_formula_code->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        textEdit_formula_code->setLineWrapMode(QTextEdit::NoWrap);

        verticalLayout->addWidget(textEdit_formula_code);

        label_lineColumn = new QLabel(cCustomFormulaEditor);
        label_lineColumn->setObjectName(QString::fromUtf8("label_lineColumn"));

        verticalLayout->addWidget(label_lineColumn);


        retranslateUi(cCustomFormulaEditor);

        QMetaObject::connectSlotsByName(cCustomFormulaEditor);
    } // setupUi

    void retranslateUi(QWidget *cCustomFormulaEditor)
    {
#if QT_CONFIG(tooltip)
        pushButton_new->setToolTip(QCoreApplication::translate("cCustomFormulaEditor", "Creates empty custom formula", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_new->setText(QCoreApplication::translate("cCustomFormulaEditor", "New", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_load_builtin->setToolTip(QCoreApplication::translate("cCustomFormulaEditor", "<html><head/><body><p>Load formula code from selected build-in formula</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_load_builtin->setText(QCoreApplication::translate("cCustomFormulaEditor", "Load built-in", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_load_from_file->setToolTip(QCoreApplication::translate("cCustomFormulaEditor", "<html><head/><body><p>Loads formula code from file</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_load_from_file->setText(QCoreApplication::translate("cCustomFormulaEditor", "Load from file", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_save_to_file->setToolTip(QCoreApplication::translate("cCustomFormulaEditor", "<html><head/><body><p>Saves formula code to chosen file. </p><p>Remark: formula code is always saved together with fractal settings (compressed formula code in .fract file)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_save_to_file->setText(QCoreApplication::translate("cCustomFormulaEditor", "Save to file", nullptr));
        groupBox_parameters->setTitle(QCoreApplication::translate("cCustomFormulaEditor", "Formula parameters", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_auto_format->setToolTip(QCoreApplication::translate("cCustomFormulaEditor", "<html><head/><body><p>Formats code in the editor. It needs clang-format tool.</p><p>To install clang-format:</p><p>- Linux: Install clang-format from ypur package manager.</p><p>- Windows: Go to https://llvm.org/builds<br/>   download and install clang-format</p><p>MacOS: When you have the brew package manager installed run: <br/>brew install clang-format</p><p>If required, you can specify the program path under <br/>Preferences &gt; OpenCL (GPU) &gt; clang-format path.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_auto_format->setText(QCoreApplication::translate("cCustomFormulaEditor", "AutoFormat", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_check_syntax->setToolTip(QCoreApplication::translate("cCustomFormulaEditor", "<html><head/><body><p>Runs OpenCL compiler to check syntax</p><p>Errors are displayed in the list below.</p><p>You can double-click on chosen error to move cursor to the error position.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_check_syntax->setText(QCoreApplication::translate("cCustomFormulaEditor", "Check syntax", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_insert_parameter->setToolTip(QCoreApplication::translate("cCustomFormulaEditor", "<html><head/><body><p>Inserts parameter from the list of available parameter names.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_insert_parameter->setText(QCoreApplication::translate("cCustomFormulaEditor", "Insert parameter", nullptr));
        label_errors->setText(QCoreApplication::translate("cCustomFormulaEditor", "Errors:", nullptr));
        label_lineColumn->setText(QCoreApplication::translate("cCustomFormulaEditor", "line 0, column 0", nullptr));
        (void)cCustomFormulaEditor;
    } // retranslateUi

};

namespace Ui {
    class cCustomFormulaEditor: public Ui_cCustomFormulaEditor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOM_FORMULA_EDITOR_H
