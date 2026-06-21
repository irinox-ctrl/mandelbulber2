/********************************************************************************
** Form generated from reading UI file 'fractal_description_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRACTAL_DESCRIPTION_TAB_H
#define UI_FRACTAL_DESCRIPTION_TAB_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_cFractalDescriptionTab
{
public:
    QVBoxLayout *verticalLayout_description;
    QPlainTextEdit *text_description;

    void setupUi(QWidget *cFractalDescriptionTab)
    {
        if (cFractalDescriptionTab->objectName().isEmpty())
            cFractalDescriptionTab->setObjectName(QString::fromUtf8("cFractalDescriptionTab"));
        verticalLayout_description = new QVBoxLayout(cFractalDescriptionTab);
        verticalLayout_description->setSpacing(2);
        verticalLayout_description->setObjectName(QString::fromUtf8("verticalLayout_description"));
        verticalLayout_description->setContentsMargins(2, 2, 2, 2);
        text_description = new QPlainTextEdit(cFractalDescriptionTab);
        text_description->setObjectName(QString::fromUtf8("text_description"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(text_description->sizePolicy().hasHeightForWidth());
        text_description->setSizePolicy(sizePolicy);
        QFont font;
        font.setFamily(QString::fromUtf8("Monospace"));
        text_description->setFont(font);

        verticalLayout_description->addWidget(text_description);


        retranslateUi(cFractalDescriptionTab);

        QMetaObject::connectSlotsByName(cFractalDescriptionTab);
    } // setupUi

    void retranslateUi(QWidget *cFractalDescriptionTab)
    {
#if QT_CONFIG(tooltip)
        text_description->setToolTip(QCoreApplication::translate("cFractalDescriptionTab", "<html><head/><body><p>An explanation of the setting</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        text_description->setPlaceholderText(QCoreApplication::translate("cFractalDescriptionTab", "An explanation of the setting", nullptr));
        (void)cFractalDescriptionTab;
    } // retranslateUi

};

namespace Ui {
    class cFractalDescriptionTab: public Ui_cFractalDescriptionTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRACTAL_DESCRIPTION_TAB_H
