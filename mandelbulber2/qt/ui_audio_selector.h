/********************************************************************************
** Form generated from reading UI file 'audio_selector.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUDIO_SELECTOR_H
#define UI_AUDIO_SELECTOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "anim_audio_view.h"
#include "fft_view.h"
#include "my_check_box.h"
#include "my_double_spin_box.h"
#include "my_group_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"
#include "time_ruler.h"
#include "wave_form_view.h"

QT_BEGIN_NAMESPACE

class Ui_cAudioSelector
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QPushButton *pushButton_loadAudioFile;
    MyLineEdit *text_animsound_soundfile;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_playback_start;
    QPushButton *pushButton_playback_stop;
    QPushButton *pushButton_delete_audiotrack;
    MyGroupBox *groupCheck_animsound_enable;
    QVBoxLayout *verticalLayout_119;
    QGridLayout *gridLayout;
    QLabel *label_132;
    MyLineEdit *logedit_animsound_additionfactor;
    MyCheckBox *checkBox_animsound_pitchmode;
    QLabel *label_134;
    MyDoubleSpinBox *spinbox_animsound_midfreq;
    MyCheckBox *checkBox_animsound_negative;
    MyDoubleSpinBox *spinbox_animsound_bandwidth;
    QLabel *label_131;
    QLabel *label_133;
    MyLineEdit *logedit_animsound_multfactor;
    QLabel *label_135;
    MySpinBox *spinboxInt_animsound_sounddelay;
    MyGroupBox *groupCheck_animsound_binaryfilter;
    QVBoxLayout *verticalLayout_123;
    QGridLayout *gridLayout_5;
    MyDoubleSpinBox *spinbox_animsound_binarylength;
    MyDoubleSpinBox *spinbox_animsound_binarythresh;
    QLabel *label_142;
    QLabel *label_141;
    MyGroupBox *groupCheck_animsound_decayfilter;
    QVBoxLayout *verticalLayout_121;
    QGridLayout *gridLayout_3;
    QLabel *label_139;
    MyDoubleSpinBox *spinbox_animsound_decaystrength;
    MyGroupBox *groupCheck_animsound_smoothfilter;
    QVBoxLayout *verticalLayout_122;
    QGridLayout *gridLayout_4;
    QLabel *label_140;
    MyDoubleSpinBox *spinbox_animsound_smoothstrength;
    QLabel *label_4;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    cWaveFormView *waveForm;
    QLabel *label_2;
    cFFTView *fft;
    QLabel *label_3;
    cAnimAudioView *animAudioView;
    cTimeRuler *timeRuler;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_time;
    QSlider *audio_position_slider;

    void setupUi(QWidget *cAudioSelector)
    {
        if (cAudioSelector->objectName().isEmpty())
            cAudioSelector->setObjectName(QString::fromUtf8("cAudioSelector"));
        cAudioSelector->resize(1279, 738);
        verticalLayout = new QVBoxLayout(cAudioSelector);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        pushButton_loadAudioFile = new QPushButton(cAudioSelector);
        pushButton_loadAudioFile->setObjectName(QString::fromUtf8("pushButton_loadAudioFile"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("document-open");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/system/icons/document-open.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_loadAudioFile->setIcon(icon);

        verticalLayout_3->addWidget(pushButton_loadAudioFile);

        text_animsound_soundfile = new MyLineEdit(cAudioSelector);
        text_animsound_soundfile->setObjectName(QString::fromUtf8("text_animsound_soundfile"));

        verticalLayout_3->addWidget(text_animsound_soundfile);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        pushButton_playback_start = new QPushButton(cAudioSelector);
        pushButton_playback_start->setObjectName(QString::fromUtf8("pushButton_playback_start"));
        QIcon icon1;
        iconThemeName = QString::fromUtf8("media-playback-start");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/system/icons/media-playback-start.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_playback_start->setIcon(icon1);

        horizontalLayout_2->addWidget(pushButton_playback_start);

        pushButton_playback_stop = new QPushButton(cAudioSelector);
        pushButton_playback_stop->setObjectName(QString::fromUtf8("pushButton_playback_stop"));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("media-playback-stop");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8(":/system/icons/media-playback-stop.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_playback_stop->setIcon(icon2);

        horizontalLayout_2->addWidget(pushButton_playback_stop);


        verticalLayout_3->addLayout(horizontalLayout_2);

        pushButton_delete_audiotrack = new QPushButton(cAudioSelector);
        pushButton_delete_audiotrack->setObjectName(QString::fromUtf8("pushButton_delete_audiotrack"));
        QIcon icon3;
        iconThemeName = QString::fromUtf8("edit-delete");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8(":/system/icons/edit-delete.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_delete_audiotrack->setIcon(icon3);

        verticalLayout_3->addWidget(pushButton_delete_audiotrack);

        groupCheck_animsound_enable = new MyGroupBox(cAudioSelector);
        groupCheck_animsound_enable->setObjectName(QString::fromUtf8("groupCheck_animsound_enable"));
        groupCheck_animsound_enable->setCheckable(true);
        verticalLayout_119 = new QVBoxLayout(groupCheck_animsound_enable);
        verticalLayout_119->setSpacing(2);
        verticalLayout_119->setObjectName(QString::fromUtf8("verticalLayout_119"));
        verticalLayout_119->setContentsMargins(2, 2, 2, 2);
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_132 = new QLabel(groupCheck_animsound_enable);
        label_132->setObjectName(QString::fromUtf8("label_132"));

        gridLayout->addWidget(label_132, 2, 0, 1, 1);

        logedit_animsound_additionfactor = new MyLineEdit(groupCheck_animsound_enable);
        logedit_animsound_additionfactor->setObjectName(QString::fromUtf8("logedit_animsound_additionfactor"));

        gridLayout->addWidget(logedit_animsound_additionfactor, 3, 1, 1, 1);

        checkBox_animsound_pitchmode = new MyCheckBox(groupCheck_animsound_enable);
        checkBox_animsound_pitchmode->setObjectName(QString::fromUtf8("checkBox_animsound_pitchmode"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(checkBox_animsound_pitchmode->sizePolicy().hasHeightForWidth());
        checkBox_animsound_pitchmode->setSizePolicy(sizePolicy);

        gridLayout->addWidget(checkBox_animsound_pitchmode, 6, 0, 1, 2);

        label_134 = new QLabel(groupCheck_animsound_enable);
        label_134->setObjectName(QString::fromUtf8("label_134"));

        gridLayout->addWidget(label_134, 4, 0, 1, 1);

        spinbox_animsound_midfreq = new MyDoubleSpinBox(groupCheck_animsound_enable);
        spinbox_animsound_midfreq->setObjectName(QString::fromUtf8("spinbox_animsound_midfreq"));
        sizePolicy.setHeightForWidth(spinbox_animsound_midfreq->sizePolicy().hasHeightForWidth());
        spinbox_animsound_midfreq->setSizePolicy(sizePolicy);
        spinbox_animsound_midfreq->setDecimals(0);
        spinbox_animsound_midfreq->setMinimum(0.000000000000000);
        spinbox_animsound_midfreq->setMaximum(20000.000000000000000);
        spinbox_animsound_midfreq->setSingleStep(10.000000000000000);
        spinbox_animsound_midfreq->setValue(1.000000000000000);

        gridLayout->addWidget(spinbox_animsound_midfreq, 1, 1, 1, 1);

        checkBox_animsound_negative = new MyCheckBox(groupCheck_animsound_enable);
        checkBox_animsound_negative->setObjectName(QString::fromUtf8("checkBox_animsound_negative"));
        sizePolicy.setHeightForWidth(checkBox_animsound_negative->sizePolicy().hasHeightForWidth());
        checkBox_animsound_negative->setSizePolicy(sizePolicy);

        gridLayout->addWidget(checkBox_animsound_negative, 5, 0, 1, 2);

        spinbox_animsound_bandwidth = new MyDoubleSpinBox(groupCheck_animsound_enable);
        spinbox_animsound_bandwidth->setObjectName(QString::fromUtf8("spinbox_animsound_bandwidth"));
        sizePolicy.setHeightForWidth(spinbox_animsound_bandwidth->sizePolicy().hasHeightForWidth());
        spinbox_animsound_bandwidth->setSizePolicy(sizePolicy);
        spinbox_animsound_bandwidth->setDecimals(0);
        spinbox_animsound_bandwidth->setMinimum(0.000000000000000);
        spinbox_animsound_bandwidth->setMaximum(20000.000000000000000);
        spinbox_animsound_bandwidth->setSingleStep(10.000000000000000);
        spinbox_animsound_bandwidth->setValue(1.000000000000000);

        gridLayout->addWidget(spinbox_animsound_bandwidth, 2, 1, 1, 1);

        label_131 = new QLabel(groupCheck_animsound_enable);
        label_131->setObjectName(QString::fromUtf8("label_131"));

        gridLayout->addWidget(label_131, 1, 0, 1, 1);

        label_133 = new QLabel(groupCheck_animsound_enable);
        label_133->setObjectName(QString::fromUtf8("label_133"));

        gridLayout->addWidget(label_133, 3, 0, 1, 1);

        logedit_animsound_multfactor = new MyLineEdit(groupCheck_animsound_enable);
        logedit_animsound_multfactor->setObjectName(QString::fromUtf8("logedit_animsound_multfactor"));

        gridLayout->addWidget(logedit_animsound_multfactor, 4, 1, 1, 1);

        label_135 = new QLabel(groupCheck_animsound_enable);
        label_135->setObjectName(QString::fromUtf8("label_135"));

        gridLayout->addWidget(label_135, 0, 0, 1, 1);

        spinboxInt_animsound_sounddelay = new MySpinBox(groupCheck_animsound_enable);
        spinboxInt_animsound_sounddelay->setObjectName(QString::fromUtf8("spinboxInt_animsound_sounddelay"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(spinboxInt_animsound_sounddelay->sizePolicy().hasHeightForWidth());
        spinboxInt_animsound_sounddelay->setSizePolicy(sizePolicy1);
        spinboxInt_animsound_sounddelay->setMinimum(-100000);
        spinboxInt_animsound_sounddelay->setMaximum(100000);
        spinboxInt_animsound_sounddelay->setSingleStep(1);

        gridLayout->addWidget(spinboxInt_animsound_sounddelay, 0, 1, 1, 1);


        verticalLayout_119->addLayout(gridLayout);

        groupCheck_animsound_binaryfilter = new MyGroupBox(groupCheck_animsound_enable);
        groupCheck_animsound_binaryfilter->setObjectName(QString::fromUtf8("groupCheck_animsound_binaryfilter"));
        groupCheck_animsound_binaryfilter->setCheckable(true);
        verticalLayout_123 = new QVBoxLayout(groupCheck_animsound_binaryfilter);
        verticalLayout_123->setSpacing(2);
        verticalLayout_123->setObjectName(QString::fromUtf8("verticalLayout_123"));
        verticalLayout_123->setContentsMargins(2, 2, 2, 2);
        gridLayout_5 = new QGridLayout();
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        spinbox_animsound_binarylength = new MyDoubleSpinBox(groupCheck_animsound_binaryfilter);
        spinbox_animsound_binarylength->setObjectName(QString::fromUtf8("spinbox_animsound_binarylength"));
        sizePolicy.setHeightForWidth(spinbox_animsound_binarylength->sizePolicy().hasHeightForWidth());
        spinbox_animsound_binarylength->setSizePolicy(sizePolicy);
        spinbox_animsound_binarylength->setDecimals(0);
        spinbox_animsound_binarylength->setMinimum(0.000000000000000);
        spinbox_animsound_binarylength->setMaximum(1000.000000000000000);
        spinbox_animsound_binarylength->setSingleStep(1.000000000000000);
        spinbox_animsound_binarylength->setValue(1.000000000000000);

        gridLayout_5->addWidget(spinbox_animsound_binarylength, 1, 1, 1, 1);

        spinbox_animsound_binarythresh = new MyDoubleSpinBox(groupCheck_animsound_binaryfilter);
        spinbox_animsound_binarythresh->setObjectName(QString::fromUtf8("spinbox_animsound_binarythresh"));
        sizePolicy.setHeightForWidth(spinbox_animsound_binarythresh->sizePolicy().hasHeightForWidth());
        spinbox_animsound_binarythresh->setSizePolicy(sizePolicy);
        spinbox_animsound_binarythresh->setDecimals(3);
        spinbox_animsound_binarythresh->setMinimum(0.000000000000000);
        spinbox_animsound_binarythresh->setMaximum(1.000000000000000);
        spinbox_animsound_binarythresh->setSingleStep(0.010000000000000);
        spinbox_animsound_binarythresh->setValue(1.000000000000000);

        gridLayout_5->addWidget(spinbox_animsound_binarythresh, 0, 1, 1, 1);

        label_142 = new QLabel(groupCheck_animsound_binaryfilter);
        label_142->setObjectName(QString::fromUtf8("label_142"));

        gridLayout_5->addWidget(label_142, 1, 0, 1, 1);

        label_141 = new QLabel(groupCheck_animsound_binaryfilter);
        label_141->setObjectName(QString::fromUtf8("label_141"));

        gridLayout_5->addWidget(label_141, 0, 0, 1, 1);


        verticalLayout_123->addLayout(gridLayout_5);


        verticalLayout_119->addWidget(groupCheck_animsound_binaryfilter);

        groupCheck_animsound_decayfilter = new MyGroupBox(groupCheck_animsound_enable);
        groupCheck_animsound_decayfilter->setObjectName(QString::fromUtf8("groupCheck_animsound_decayfilter"));
        groupCheck_animsound_decayfilter->setCheckable(true);
        verticalLayout_121 = new QVBoxLayout(groupCheck_animsound_decayfilter);
        verticalLayout_121->setSpacing(2);
        verticalLayout_121->setObjectName(QString::fromUtf8("verticalLayout_121"));
        verticalLayout_121->setContentsMargins(2, 2, 2, 2);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_139 = new QLabel(groupCheck_animsound_decayfilter);
        label_139->setObjectName(QString::fromUtf8("label_139"));

        gridLayout_3->addWidget(label_139, 0, 0, 1, 1);

        spinbox_animsound_decaystrength = new MyDoubleSpinBox(groupCheck_animsound_decayfilter);
        spinbox_animsound_decaystrength->setObjectName(QString::fromUtf8("spinbox_animsound_decaystrength"));
        sizePolicy.setHeightForWidth(spinbox_animsound_decaystrength->sizePolicy().hasHeightForWidth());
        spinbox_animsound_decaystrength->setSizePolicy(sizePolicy);
        spinbox_animsound_decaystrength->setDecimals(2);
        spinbox_animsound_decaystrength->setMinimum(1.000000000000000);
        spinbox_animsound_decaystrength->setMaximum(1000.000000000000000);
        spinbox_animsound_decaystrength->setSingleStep(1.000000000000000);
        spinbox_animsound_decaystrength->setValue(1.000000000000000);

        gridLayout_3->addWidget(spinbox_animsound_decaystrength, 0, 1, 1, 1);


        verticalLayout_121->addLayout(gridLayout_3);


        verticalLayout_119->addWidget(groupCheck_animsound_decayfilter);

        groupCheck_animsound_smoothfilter = new MyGroupBox(groupCheck_animsound_enable);
        groupCheck_animsound_smoothfilter->setObjectName(QString::fromUtf8("groupCheck_animsound_smoothfilter"));
        groupCheck_animsound_smoothfilter->setCheckable(true);
        verticalLayout_122 = new QVBoxLayout(groupCheck_animsound_smoothfilter);
        verticalLayout_122->setSpacing(2);
        verticalLayout_122->setObjectName(QString::fromUtf8("verticalLayout_122"));
        verticalLayout_122->setContentsMargins(2, 2, 2, 2);
        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_140 = new QLabel(groupCheck_animsound_smoothfilter);
        label_140->setObjectName(QString::fromUtf8("label_140"));

        gridLayout_4->addWidget(label_140, 0, 0, 1, 1);

        spinbox_animsound_smoothstrength = new MyDoubleSpinBox(groupCheck_animsound_smoothfilter);
        spinbox_animsound_smoothstrength->setObjectName(QString::fromUtf8("spinbox_animsound_smoothstrength"));
        sizePolicy.setHeightForWidth(spinbox_animsound_smoothstrength->sizePolicy().hasHeightForWidth());
        spinbox_animsound_smoothstrength->setSizePolicy(sizePolicy);
        spinbox_animsound_smoothstrength->setDecimals(2);
        spinbox_animsound_smoothstrength->setMinimum(1.000000000000000);
        spinbox_animsound_smoothstrength->setMaximum(1000.000000000000000);
        spinbox_animsound_smoothstrength->setSingleStep(1.000000000000000);
        spinbox_animsound_smoothstrength->setValue(1.000000000000000);

        gridLayout_4->addWidget(spinbox_animsound_smoothstrength, 0, 1, 1, 1);


        verticalLayout_122->addLayout(gridLayout_4);


        verticalLayout_119->addWidget(groupCheck_animsound_smoothfilter);


        verticalLayout_3->addWidget(groupCheck_animsound_enable);

        label_4 = new QLabel(cAudioSelector);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setWordWrap(true);

        verticalLayout_3->addWidget(label_4);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        scrollArea = new QScrollArea(cAudioSelector);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 977, 672));
        verticalLayout_2 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(2, 2, 2, 2);
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        waveForm = new cWaveFormView(scrollAreaWidgetContents);
        waveForm->setObjectName(QString::fromUtf8("waveForm"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(waveForm->sizePolicy().hasHeightForWidth());
        waveForm->setSizePolicy(sizePolicy2);
        waveForm->setMinimumSize(QSize(0, 128));
        waveForm->setMaximumSize(QSize(16777215, 128));
        waveForm->setBaseSize(QSize(0, 0));

        verticalLayout_2->addWidget(waveForm);

        label_2 = new QLabel(scrollAreaWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        fft = new cFFTView(scrollAreaWidgetContents);
        fft->setObjectName(QString::fromUtf8("fft"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(fft->sizePolicy().hasHeightForWidth());
        fft->setSizePolicy(sizePolicy3);
        fft->setMaximumSize(QSize(16777215, 1024));

        verticalLayout_2->addWidget(fft);

        label_3 = new QLabel(scrollAreaWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        animAudioView = new cAnimAudioView(scrollAreaWidgetContents);
        animAudioView->setObjectName(QString::fromUtf8("animAudioView"));
        sizePolicy2.setHeightForWidth(animAudioView->sizePolicy().hasHeightForWidth());
        animAudioView->setSizePolicy(sizePolicy2);
        animAudioView->setMinimumSize(QSize(0, 128));
        animAudioView->setMaximumSize(QSize(16777215, 128));
        animAudioView->setBaseSize(QSize(0, 0));

        verticalLayout_2->addWidget(animAudioView);

        timeRuler = new cTimeRuler(scrollAreaWidgetContents);
        timeRuler->setObjectName(QString::fromUtf8("timeRuler"));
        sizePolicy2.setHeightForWidth(timeRuler->sizePolicy().hasHeightForWidth());
        timeRuler->setSizePolicy(sizePolicy2);
        timeRuler->setMinimumSize(QSize(0, 64));
        timeRuler->setMaximumSize(QSize(16777215, 64));
        timeRuler->setBaseSize(QSize(0, 0));

        verticalLayout_2->addWidget(timeRuler);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_4->addWidget(scrollArea);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label_time = new QLabel(cAudioSelector);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        horizontalLayout_3->addWidget(label_time);

        audio_position_slider = new QSlider(cAudioSelector);
        audio_position_slider->setObjectName(QString::fromUtf8("audio_position_slider"));
        audio_position_slider->setMaximum(1000000);
        audio_position_slider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(audio_position_slider);


        verticalLayout_4->addLayout(horizontalLayout_3);


        horizontalLayout->addLayout(verticalLayout_4);

        horizontalLayout->setStretch(1, 1);

        verticalLayout->addLayout(horizontalLayout);

        QWidget::setTabOrder(pushButton_loadAudioFile, text_animsound_soundfile);
        QWidget::setTabOrder(text_animsound_soundfile, pushButton_playback_start);
        QWidget::setTabOrder(pushButton_playback_start, pushButton_playback_stop);
        QWidget::setTabOrder(pushButton_playback_stop, pushButton_delete_audiotrack);
        QWidget::setTabOrder(pushButton_delete_audiotrack, groupCheck_animsound_enable);
        QWidget::setTabOrder(groupCheck_animsound_enable, spinbox_animsound_midfreq);
        QWidget::setTabOrder(spinbox_animsound_midfreq, spinbox_animsound_bandwidth);
        QWidget::setTabOrder(spinbox_animsound_bandwidth, logedit_animsound_additionfactor);
        QWidget::setTabOrder(logedit_animsound_additionfactor, logedit_animsound_multfactor);
        QWidget::setTabOrder(logedit_animsound_multfactor, checkBox_animsound_negative);
        QWidget::setTabOrder(checkBox_animsound_negative, checkBox_animsound_pitchmode);
        QWidget::setTabOrder(checkBox_animsound_pitchmode, groupCheck_animsound_binaryfilter);
        QWidget::setTabOrder(groupCheck_animsound_binaryfilter, spinbox_animsound_binarythresh);
        QWidget::setTabOrder(spinbox_animsound_binarythresh, spinbox_animsound_binarylength);
        QWidget::setTabOrder(spinbox_animsound_binarylength, groupCheck_animsound_decayfilter);
        QWidget::setTabOrder(groupCheck_animsound_decayfilter, spinbox_animsound_decaystrength);
        QWidget::setTabOrder(spinbox_animsound_decaystrength, groupCheck_animsound_smoothfilter);
        QWidget::setTabOrder(groupCheck_animsound_smoothfilter, spinbox_animsound_smoothstrength);
        QWidget::setTabOrder(spinbox_animsound_smoothstrength, audio_position_slider);
        QWidget::setTabOrder(audio_position_slider, scrollArea);

        retranslateUi(cAudioSelector);

        QMetaObject::connectSlotsByName(cAudioSelector);
    } // setupUi

    void retranslateUi(QWidget *cAudioSelector)
    {
        cAudioSelector->setWindowTitle(QCoreApplication::translate("cAudioSelector", "Form", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_loadAudioFile->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Load audio from file.</p><p>Parameter values can be animated in response to the input from audio files.</p><p>The following formats are supported:</p><p>- *.wav (wave form audio format)</p><p>- *.ogg (Ogg Vorbis)</p><p>- *.flac (Free Lossless Audio Format)</p><p>- *.mp3 (MPEG II Audio Layer 3) - supported only under Linux</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_loadAudioFile->setText(QCoreApplication::translate("cAudioSelector", "Select audio file", nullptr));
#if QT_CONFIG(tooltip)
        text_animsound_soundfile->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>path to audio file</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        pushButton_playback_start->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Play loaded audio track</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_playback_start->setText(QCoreApplication::translate("cAudioSelector", "Play sound", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_playback_stop->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Stop playing audio track</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_playback_stop->setText(QCoreApplication::translate("cAudioSelector", "Stop", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_delete_audiotrack->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Remove audio track from animation</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_delete_audiotrack->setText(QCoreApplication::translate("cAudioSelector", "Delete audio track", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_animsound_enable->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Enables Animation by Sound, which uses digital data from audio files to adjust parameter values obtained from the keyframe animation table.</p><p>The change in a parameter value can be in response to either the amplitude or the pitch of the sound sampled at each frame (independent from keyframes.)</p><p>There are two types of parameters in this program.\302\240\302\240 The first type can have negative values entered, the second type\302\240 cannot. <span style=\" text-decoration: underline;\">It is important</span> when animating a parameter of the second type, that the functions and settings used do not result in a negative number.</p><p>Animation by Sound can be used in combination with animation from the Keyframe table. </p><p>Example:</p><p>An object can be moving in a linear direction in respect to the keyframe animation table calculation, and at the same time have this movement responding to the audio.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_animsound_enable->setTitle(QCoreApplication::translate("cAudioSelector", "Enable animation by so&und", nullptr));
        label_132->setText(QCoreApplication::translate("cAudioSelector", "Bandwidth:", nullptr));
#if QT_CONFIG(tooltip)
        logedit_animsound_additionfactor->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>The value of animation of a parameter, is the sum of the <span style=\" text-decoration: underline;\">sound value</span> added to the <span style=\" text-decoration: underline;\">parameter value</span> (from the keyframe animation table): </p><p><span style=\" font-weight:600; font-style:italic;\">animation = parameter_value + sound * addition factor </span><span style=\" font-weight:400; font-style:italic;\">+ parameter_value * </span><span style=\" font-weight:400; font-style:italic;\">multiplication_factor * sound</span><span style=\" font-weight:400; font-style:italic;\">;</span></p><p>where:</p><p><span style=\" font-style:italic;\">sound</span> - effect of average amplitude or pitch of the selected range of sound frequencies. It is calculated as a value from 0 to 1, ( 0 = silent , 1 = maximum.) </p><p><span style=\" font-style:italic;\">parameter value </span>- from keyframe animation calculations.</p><p><span style=\" font-style:italic;\">animation</span> - value of the parameter v"
                        "alue after the sound has been applied.</p><p>To get subtraction of the sound value from parameter value, use <span style=\" font-style:italic;\">Negative influence</span> option.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        checkBox_animsound_pitchmode->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Changes the way the sound is calculated.</p><p>If the mode is disabled, then the sound is calculated from the average amplitude of the selected sound frequencies.</p><p>When it is enabled, then the sound  is calculated from the average pitch of the selected sound frequencies.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_animsound_pitchmode->setText(QCoreApplication::translate("cAudioSelector", "Sound pitch mode", nullptr));
        label_134->setText(QCoreApplication::translate("cAudioSelector", "Multiplication factor", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_animsound_midfreq->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Frequency of sound which will be used to calculate animation.</p><p>This frequency is shown on the &quot;Frequency spectrum&quot; chart.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_animsound_midfreq->setPrefix(QString());
        spinbox_animsound_midfreq->setSuffix(QString());
#if QT_CONFIG(tooltip)
        checkBox_animsound_negative->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Changes direction of influence of the sound value.</p><p><span style=\" font-weight:600; font-style:italic;\">animation = parameter_value / (1 + multiplication_factor * sound) - (addition_factor * sound);</span></p><p>Note: multiplication_factor  scales the denominator in this function.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_animsound_negative->setText(QCoreApplication::translate("cAudioSelector", "Negative influence", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_animsound_bandwidth->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Width of the band of frequencies used to calculate the sound value effect on an animation.</p><p>Selected bandwidth is shown on the &quot;Frequency spectrum&quot; chart.</p><p>If the bandwidth is wide, then the sound value will be calculated from the average amplitude of the selected frequencies.</p><p>If the bandwidth is set to the maximum value, then the sound value will be calculated from the amplitude of the sound.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_animsound_bandwidth->setPrefix(QString());
        spinbox_animsound_bandwidth->setSuffix(QString());
        label_131->setText(QCoreApplication::translate("cAudioSelector", "Frequency of interest:", nullptr));
        label_133->setText(QCoreApplication::translate("cAudioSelector", "Addition factor", nullptr));
#if QT_CONFIG(tooltip)
        logedit_animsound_multfactor->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>The value of animation of a parameter, is the sum of the <span style=\" text-decoration: underline;\">sound value</span> added to the <span style=\" text-decoration: underline;\">parameter value</span> (from the keyframe animation table): </p><p><span style=\" font-weight:600; font-style:italic;\">animation =</span><span style=\" font-weight:600;\"> parameter_value + parameter_value * multiplication_factor * sound</span><span style=\" font-style:italic;\"> + </span><span style=\" font-style:italic;\">sound * addition factor</span><span style=\" font-style:italic;\">;</span></p><p>where:</p><p><span style=\" font-style:italic;\">sound</span> - average amplitude or pitch of the selected range of sound frequencies. It is calculated as a value from 0 to 1, ( 0 = silent\302\240, 1 = maximum.) </p><p><span style=\" font-style:italic;\">parameter value </span>- from keyframe animation calculations.</p><p><span style=\" font-style:italic;\">animation</span> - value of the parameter value after th"
                        "e sound_value has been added.</p><p>Note: when only multiplication factor is used (i.e. addition_factor is close to zero), it is guaranteed that <span style=\" font-style:italic;\">sound</span> will not modify the sign of animated parameter value. </p><p>Note: multiplication_factor operates differently in Negative Influence mode function. There it is used as division instead of multiplication.      Negative Influence mode function:</p><p><span style=\" font-weight:600; font-style:italic;\">animation =</span><span style=\" font-weight:600;\"> parameter_value / (1.0 + multiplication_factor * sound)</span><span style=\" font-style:italic;\"> + sound * addition factor;</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_135->setText(QCoreApplication::translate("cAudioSelector", "Sound delay (frames)", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_animsound_binaryfilter->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>This option enables the binary filter.</p><p>The addition of the sound value to the parameter value is triggered when the sound rises above the threshold and ceases when the sound drops below the threshold, (unless the minimum duration is extended past that frame point.)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_animsound_binaryfilter->setTitle(QCoreApplication::translate("cAudioSelector", "&Binary filter", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_animsound_binarylength->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Minimum duration for which the sound value will be calculated and added to the parameter value, from the frame where the sound first exceeded the threshold, ( measured in frames.)</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_animsound_binarylength->setPrefix(QString());
        spinbox_animsound_binarylength->setSuffix(QString());
#if QT_CONFIG(tooltip)
        spinbox_animsound_binarythresh->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Threshold for binary filter. </p><p>When sound is above the threshold, the sound value is calculated and added to the parameter value.  Calculation continues until the sound falls below the threshold or the minimum duration is exceeded.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_animsound_binarythresh->setPrefix(QString());
        spinbox_animsound_binarythresh->setSuffix(QString());
        label_142->setText(QCoreApplication::translate("cAudioSelector", "Minimum duration:", nullptr));
        label_141->setText(QCoreApplication::translate("cAudioSelector", "Threshold:", nullptr));
#if QT_CONFIG(tooltip)
        groupCheck_animsound_decayfilter->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>This option enables the decay filter.</p><p>The sound value will rise fast, but decay slowly.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_animsound_decayfilter->setTitle(QCoreApplication::translate("cAudioSelector", "Decay fil&ter", nullptr));
        label_139->setText(QCoreApplication::translate("cAudioSelector", "Strength:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_animsound_decaystrength->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>A higher value extends the decay of the sound value.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_animsound_decaystrength->setPrefix(QString());
        spinbox_animsound_decaystrength->setSuffix(QString());
#if QT_CONFIG(tooltip)
        groupCheck_animsound_smoothfilter->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>This option enables the smooth filter.</p><p>The sound value will change in a smooth way.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupCheck_animsound_smoothfilter->setTitle(QCoreApplication::translate("cAudioSelector", "Smooth fi&lter", nullptr));
        label_140->setText(QCoreApplication::translate("cAudioSelector", "Strength:", nullptr));
#if QT_CONFIG(tooltip)
        spinbox_animsound_smoothstrength->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>A higher value will result in a reduced audio influence on the animated parameter.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        spinbox_animsound_smoothstrength->setPrefix(QString());
        spinbox_animsound_smoothstrength->setSuffix(QString());
        label_4->setText(QCoreApplication::translate("cAudioSelector", "Note: you can drag keyframes on the ruler to align them with audio", nullptr));
        label->setText(QCoreApplication::translate("cAudioSelector", "Waveform", nullptr));
#if QT_CONFIG(tooltip)
        waveForm->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Displays waveform of loaded audio file.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_2->setText(QCoreApplication::translate("cAudioSelector", "Frequency spectrum", nullptr));
#if QT_CONFIG(tooltip)
        fft->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Displays frequency spectrum of loaded audio file.</p><p>The chart displays low frequencies of the sound (bass) at the bottom,  and  high frequencies (high tones)  at the top.</p><p>Brighter pixels indicates louder tones.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_3->setText(QCoreApplication::translate("cAudioSelector", "Sound Animation chart", nullptr));
#if QT_CONFIG(tooltip)
        animAudioView->setToolTip(QCoreApplication::translate("cAudioSelector", "<html><head/><body><p>Animation chart shows <span style=\" font-weight:600;\">sound</span>  that is used in the calculation of sound value. It ranges from silent at the bottom up to maximum of 1.</p><p><br/></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_time->setText(QCoreApplication::translate("cAudioSelector", "-- / --", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cAudioSelector: public Ui_cAudioSelector {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUDIO_SELECTOR_H
