/********************************************************************************
** Form generated from reading UI file 'slider_popup.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SLIDER_POPUP_H
#define UI_SLIDER_POPUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_cFrameSliderPopup
{
public:
    QVBoxLayout *verticalLayout_2;
    QDial *dial;
    QSlider *slider;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButton_super_fine;
    QRadioButton *radioButton_very_fine;
    QRadioButton *radioButton_fine;
    QRadioButton *radioButton_normal;
    QRadioButton *radioButton_coarse;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *buClose;
    QToolButton *buReset;
    QToolButton *buZero;
    QToolButton *buMinus;
    QToolButton *buDouble;
    QToolButton *buHalf;
    QToolButton *buUp;
    QToolButton *buRight;
    QToolButton *buDown;
    QToolButton *buLeft;
    QToolButton *buInteger;

    void setupUi(QFrame *cFrameSliderPopup)
    {
        if (cFrameSliderPopup->objectName().isEmpty())
            cFrameSliderPopup->setObjectName(QString::fromUtf8("cFrameSliderPopup"));
        cFrameSliderPopup->resize(460, 280);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cFrameSliderPopup->sizePolicy().hasHeightForWidth());
        cFrameSliderPopup->setSizePolicy(sizePolicy);
        cFrameSliderPopup->setAutoFillBackground(true);
        cFrameSliderPopup->setFrameShape(QFrame::StyledPanel);
        cFrameSliderPopup->setFrameShadow(QFrame::Raised);
        cFrameSliderPopup->setStyleSheet(QString::fromUtf8("QRadioButton, QToolButton { font-size: 13px; min-height: 24px; } QSlider::groove:horizontal { height: 8px; } QSlider::handle:horizontal { width: 18px; height: 18px; margin: -5px 0; }"));
        verticalLayout_2 = new QVBoxLayout(cFrameSliderPopup);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(8, 8, 8, 8);
        dial = new QDial(cFrameSliderPopup);
        dial->setObjectName(QString::fromUtf8("dial"));
        dial->setMinimumSize(QSize(100, 100));
        dial->setFocusPolicy(Qt::NoFocus);
        dial->setWrapping(true);
        dial->setNotchesVisible(false);

        verticalLayout_2->addWidget(dial);

        slider = new QSlider(cFrameSliderPopup);
        slider->setObjectName(QString::fromUtf8("slider"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(slider->sizePolicy().hasHeightForWidth());
        slider->setSizePolicy(sizePolicy1);
        slider->setMinimumSize(QSize(0, 28));
        slider->setFocusPolicy(Qt::NoFocus);
        slider->setMaximum(1000);
        slider->setPageStep(0);
        slider->setValue(500);
        slider->setOrientation(Qt::Horizontal);

        verticalLayout_2->addWidget(slider);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(4);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioButton_super_fine = new QRadioButton(cFrameSliderPopup);
        radioButton_super_fine->setObjectName(QString::fromUtf8("radioButton_super_fine"));
        radioButton_super_fine->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(radioButton_super_fine);

        radioButton_very_fine = new QRadioButton(cFrameSliderPopup);
        radioButton_very_fine->setObjectName(QString::fromUtf8("radioButton_very_fine"));
        radioButton_very_fine->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(radioButton_very_fine);

        radioButton_fine = new QRadioButton(cFrameSliderPopup);
        radioButton_fine->setObjectName(QString::fromUtf8("radioButton_fine"));
        radioButton_fine->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(radioButton_fine);

        radioButton_normal = new QRadioButton(cFrameSliderPopup);
        radioButton_normal->setObjectName(QString::fromUtf8("radioButton_normal"));
        radioButton_normal->setFocusPolicy(Qt::NoFocus);
        radioButton_normal->setChecked(true);

        horizontalLayout->addWidget(radioButton_normal);

        radioButton_coarse = new QRadioButton(cFrameSliderPopup);
        radioButton_coarse->setObjectName(QString::fromUtf8("radioButton_coarse"));
        radioButton_coarse->setFocusPolicy(Qt::NoFocus);

        horizontalLayout->addWidget(radioButton_coarse);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        buClose = new QToolButton(cFrameSliderPopup);
        buClose->setObjectName(QString::fromUtf8("buClose"));
        buClose->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(buClose);

        buReset = new QToolButton(cFrameSliderPopup);
        buReset->setObjectName(QString::fromUtf8("buReset"));
        buReset->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(buReset);

        buZero = new QToolButton(cFrameSliderPopup);
        buZero->setObjectName(QString::fromUtf8("buZero"));
        buZero->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(buZero);

        buMinus = new QToolButton(cFrameSliderPopup);
        buMinus->setObjectName(QString::fromUtf8("buMinus"));
        buMinus->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(buMinus);

        buDouble = new QToolButton(cFrameSliderPopup);
        buDouble->setObjectName(QString::fromUtf8("buDouble"));
        buDouble->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(buDouble);

        buHalf = new QToolButton(cFrameSliderPopup);
        buHalf->setObjectName(QString::fromUtf8("buHalf"));
        buHalf->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(buHalf);

        buUp = new QToolButton(cFrameSliderPopup);
        buUp->setObjectName(QString::fromUtf8("buUp"));
        buUp->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(buUp);

        buRight = new QToolButton(cFrameSliderPopup);
        buRight->setObjectName(QString::fromUtf8("buRight"));
        buRight->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(buRight);

        buDown = new QToolButton(cFrameSliderPopup);
        buDown->setObjectName(QString::fromUtf8("buDown"));
        buDown->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(buDown);

        buLeft = new QToolButton(cFrameSliderPopup);
        buLeft->setObjectName(QString::fromUtf8("buLeft"));
        buLeft->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(buLeft);

        buInteger = new QToolButton(cFrameSliderPopup);
        buInteger->setObjectName(QString::fromUtf8("buInteger"));
        buInteger->setFocusPolicy(Qt::NoFocus);

        horizontalLayout_2->addWidget(buInteger);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(cFrameSliderPopup);

        QMetaObject::connectSlotsByName(cFrameSliderPopup);
    } // setupUi

    void retranslateUi(QFrame *cFrameSliderPopup)
    {
        radioButton_super_fine->setText(QCoreApplication::translate("cFrameSliderPopup", "0.001", nullptr));
        radioButton_very_fine->setText(QCoreApplication::translate("cFrameSliderPopup", "0.01", nullptr));
        radioButton_fine->setText(QCoreApplication::translate("cFrameSliderPopup", "0.1", nullptr));
        radioButton_normal->setText(QCoreApplication::translate("cFrameSliderPopup", "1", nullptr));
        radioButton_coarse->setText(QCoreApplication::translate("cFrameSliderPopup", "10", nullptr));
#if QT_CONFIG(tooltip)
        buClose->setToolTip(QCoreApplication::translate("cFrameSliderPopup", "Hide slider", nullptr));
#endif // QT_CONFIG(tooltip)
        buClose->setText(QCoreApplication::translate("cFrameSliderPopup", "X", nullptr));
#if QT_CONFIG(tooltip)
        buReset->setToolTip(QCoreApplication::translate("cFrameSliderPopup", "Reset value to default", nullptr));
#endif // QT_CONFIG(tooltip)
        buReset->setText(QCoreApplication::translate("cFrameSliderPopup", "R", nullptr));
#if QT_CONFIG(tooltip)
        buZero->setToolTip(QCoreApplication::translate("cFrameSliderPopup", "Zero", nullptr));
#endif // QT_CONFIG(tooltip)
        buZero->setText(QCoreApplication::translate("cFrameSliderPopup", "0", nullptr));
#if QT_CONFIG(tooltip)
        buMinus->setToolTip(QCoreApplication::translate("cFrameSliderPopup", "Inversion of sign", nullptr));
#endif // QT_CONFIG(tooltip)
        buMinus->setText(QCoreApplication::translate("cFrameSliderPopup", "-", nullptr));
#if QT_CONFIG(tooltip)
        buDouble->setToolTip(QCoreApplication::translate("cFrameSliderPopup", "Double", nullptr));
#endif // QT_CONFIG(tooltip)
        buDouble->setText(QCoreApplication::translate("cFrameSliderPopup", "x2", nullptr));
#if QT_CONFIG(tooltip)
        buHalf->setToolTip(QCoreApplication::translate("cFrameSliderPopup", "Half", nullptr));
#endif // QT_CONFIG(tooltip)
        buHalf->setText(QCoreApplication::translate("cFrameSliderPopup", "\303\2672", nullptr));
#if QT_CONFIG(tooltip)
        buUp->setToolTip(QCoreApplication::translate("cFrameSliderPopup", "Zero", nullptr));
#endif // QT_CONFIG(tooltip)
        buUp->setText(QCoreApplication::translate("cFrameSliderPopup", "\342\206\221", nullptr));
#if QT_CONFIG(tooltip)
        buRight->setToolTip(QCoreApplication::translate("cFrameSliderPopup", "90 degrees", nullptr));
#endif // QT_CONFIG(tooltip)
        buRight->setText(QCoreApplication::translate("cFrameSliderPopup", "\342\206\222", nullptr));
#if QT_CONFIG(tooltip)
        buDown->setToolTip(QCoreApplication::translate("cFrameSliderPopup", "180 degrees", nullptr));
#endif // QT_CONFIG(tooltip)
        buDown->setText(QCoreApplication::translate("cFrameSliderPopup", "\342\206\223", nullptr));
#if QT_CONFIG(tooltip)
        buLeft->setToolTip(QCoreApplication::translate("cFrameSliderPopup", "-90 degrees", nullptr));
#endif // QT_CONFIG(tooltip)
        buLeft->setText(QCoreApplication::translate("cFrameSliderPopup", "\342\206\220", nullptr));
#if QT_CONFIG(tooltip)
        buInteger->setToolTip(QCoreApplication::translate("cFrameSliderPopup", "\"Magic Round\"", nullptr));
#endif // QT_CONFIG(tooltip)
        buInteger->setText(QCoreApplication::translate("cFrameSliderPopup", "\342\210\205", nullptr));
        (void)cFrameSliderPopup;
    } // retranslateUi

};

namespace Ui {
    class cFrameSliderPopup: public Ui_cFrameSliderPopup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SLIDER_POPUP_H
