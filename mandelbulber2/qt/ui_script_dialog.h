/********************************************************************************
** Form generated from reading UI file 'script_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCRIPT_DIALOG_H
#define UI_SCRIPT_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_cScriptDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *labelParameter;
    QLineEdit *lineEdit_script;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_insertParameter;
    QComboBox *comboBox_container;
    QComboBox *comboBox_parameter;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_Test;
    QPushButton *pushButton_delete;
    QSpacerItem *horizontalSpacer;
    QTextBrowser *textBrowser_result;
    QLabel *label;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *cScriptDialog)
    {
        if (cScriptDialog->objectName().isEmpty())
            cScriptDialog->setObjectName(QString::fromUtf8("cScriptDialog"));
        cScriptDialog->resize(956, 459);
        cScriptDialog->setModal(false);
        verticalLayout = new QVBoxLayout(cScriptDialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelParameter = new QLabel(cScriptDialog);
        labelParameter->setObjectName(QString::fromUtf8("labelParameter"));

        verticalLayout->addWidget(labelParameter);

        lineEdit_script = new QLineEdit(cScriptDialog);
        lineEdit_script->setObjectName(QString::fromUtf8("lineEdit_script"));

        verticalLayout->addWidget(lineEdit_script);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        pushButton_insertParameter = new QPushButton(cScriptDialog);
        pushButton_insertParameter->setObjectName(QString::fromUtf8("pushButton_insertParameter"));

        horizontalLayout_2->addWidget(pushButton_insertParameter);

        comboBox_container = new QComboBox(cScriptDialog);
        comboBox_container->setObjectName(QString::fromUtf8("comboBox_container"));

        horizontalLayout_2->addWidget(comboBox_container);

        comboBox_parameter = new QComboBox(cScriptDialog);
        comboBox_parameter->setObjectName(QString::fromUtf8("comboBox_parameter"));

        horizontalLayout_2->addWidget(comboBox_parameter);

        horizontalLayout_2->setStretch(1, 1);
        horizontalLayout_2->setStretch(2, 2);

        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton_Test = new QPushButton(cScriptDialog);
        pushButton_Test->setObjectName(QString::fromUtf8("pushButton_Test"));

        horizontalLayout->addWidget(pushButton_Test);

        pushButton_delete = new QPushButton(cScriptDialog);
        pushButton_delete->setObjectName(QString::fromUtf8("pushButton_delete"));

        horizontalLayout->addWidget(pushButton_delete);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        textBrowser_result = new QTextBrowser(cScriptDialog);
        textBrowser_result->setObjectName(QString::fromUtf8("textBrowser_result"));

        verticalLayout->addWidget(textBrowser_result);

        label = new QLabel(cScriptDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        buttonBox = new QDialogButtonBox(cScriptDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(cScriptDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), cScriptDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), cScriptDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(cScriptDialog);
    } // setupUi

    void retranslateUi(QDialog *cScriptDialog)
    {
        cScriptDialog->setWindowTitle(QCoreApplication::translate("cScriptDialog", "Dialog", nullptr));
        labelParameter->setText(QCoreApplication::translate("cScriptDialog", "Script for parameter:", nullptr));
        pushButton_insertParameter->setText(QCoreApplication::translate("cScriptDialog", "Insert parameter", nullptr));
        pushButton_Test->setText(QCoreApplication::translate("cScriptDialog", "Test", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("cScriptDialog", "Delete script", nullptr));
        label->setText(QCoreApplication::translate("cScriptDialog", "Remark: Parameter names need to be in single quotes (e.g. 'detail_level')\n"
"Vector components of parameters should be after dot (e.g. 'camera.x')\n"
"Vector components of destination parameter shoud be prefixed by x:, y: and z:\n"
"Example: x: 'target.x' * 10, y: 'target.y' * 10, z: sin('frame_no' / pi() * 0.1)\n"
"If the script begins with # then evaluation of script is ommited", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cScriptDialog: public Ui_cScriptDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCRIPT_DIALOG_H
