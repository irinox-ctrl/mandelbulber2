/********************************************************************************
** Form generated from reading UI file 'dock_queue.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_QUEUE_H
#define UI_DOCK_QUEUE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_check_box.h"
#include "my_combo_box.h"

QT_BEGIN_NAMESPACE

class Ui_cDockQueue
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout_queue_options;
    QPushButton *pushButton_queue_remove_orphaned;
    QPushButton *pushButton_queue_render_queue;
    QPushButton *pushButton_queue_add_orphaned;
    QPushButton *pushButton_queue_add_current_settings;
    QPushButton *pushButton_queue_add_from_file;
    QPushButton *pushButton_queue_stop_rendering;
    MyComboBox *comboBox_queue_image_format;
    QLabel *label_image_type_2;
    MyCheckBox *checkBox_show_queue_thumbnails;
    QTableWidget *tableWidget_queue_list;

    void setupUi(QWidget *cDockQueue)
    {
        if (cDockQueue->objectName().isEmpty())
            cDockQueue->setObjectName(QString::fromUtf8("cDockQueue"));
        cDockQueue->resize(436, 524);
        verticalLayout = new QVBoxLayout(cDockQueue);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        gridLayout_queue_options = new QGridLayout();
        gridLayout_queue_options->setObjectName(QString::fromUtf8("gridLayout_queue_options"));
        gridLayout_queue_options->setHorizontalSpacing(2);
        gridLayout_queue_options->setContentsMargins(-1, 0, -1, -1);
        pushButton_queue_remove_orphaned = new QPushButton(cDockQueue);
        pushButton_queue_remove_orphaned->setObjectName(QString::fromUtf8("pushButton_queue_remove_orphaned"));
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("list-remove");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/system/icons/list-remove.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_queue_remove_orphaned->setIcon(icon);

        gridLayout_queue_options->addWidget(pushButton_queue_remove_orphaned, 1, 1, 1, 1);

        pushButton_queue_render_queue = new QPushButton(cDockQueue);
        pushButton_queue_render_queue->setObjectName(QString::fromUtf8("pushButton_queue_render_queue"));
        QIcon icon1;
        iconThemeName = QString::fromUtf8("applications-graphics");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/system/icons/applications-graphics.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_queue_render_queue->setIcon(icon1);

        gridLayout_queue_options->addWidget(pushButton_queue_render_queue, 2, 0, 1, 1);

        pushButton_queue_add_orphaned = new QPushButton(cDockQueue);
        pushButton_queue_add_orphaned->setObjectName(QString::fromUtf8("pushButton_queue_add_orphaned"));
        QIcon icon2;
        iconThemeName = QString::fromUtf8("view-refresh");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QString::fromUtf8(":/system/icons/view-refresh.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_queue_add_orphaned->setIcon(icon2);

        gridLayout_queue_options->addWidget(pushButton_queue_add_orphaned, 1, 0, 1, 1);

        pushButton_queue_add_current_settings = new QPushButton(cDockQueue);
        pushButton_queue_add_current_settings->setObjectName(QString::fromUtf8("pushButton_queue_add_current_settings"));
        QIcon icon3;
        iconThemeName = QString::fromUtf8("list-add");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon3 = QIcon::fromTheme(iconThemeName);
        } else {
            icon3.addFile(QString::fromUtf8(":/system/icons/list-add.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_queue_add_current_settings->setIcon(icon3);

        gridLayout_queue_options->addWidget(pushButton_queue_add_current_settings, 0, 0, 1, 1);

        pushButton_queue_add_from_file = new QPushButton(cDockQueue);
        pushButton_queue_add_from_file->setObjectName(QString::fromUtf8("pushButton_queue_add_from_file"));
        pushButton_queue_add_from_file->setIcon(icon3);

        gridLayout_queue_options->addWidget(pushButton_queue_add_from_file, 0, 1, 1, 1);

        pushButton_queue_stop_rendering = new QPushButton(cDockQueue);
        pushButton_queue_stop_rendering->setObjectName(QString::fromUtf8("pushButton_queue_stop_rendering"));
        QIcon icon4;
        iconThemeName = QString::fromUtf8("process-stop");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon4 = QIcon::fromTheme(iconThemeName);
        } else {
            icon4.addFile(QString::fromUtf8(":/system/icons/process-stop.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        pushButton_queue_stop_rendering->setIcon(icon4);

        gridLayout_queue_options->addWidget(pushButton_queue_stop_rendering, 2, 1, 1, 1);

        comboBox_queue_image_format = new MyComboBox(cDockQueue);
        comboBox_queue_image_format->addItem(QString());
        comboBox_queue_image_format->addItem(QString());
        comboBox_queue_image_format->addItem(QString());
        comboBox_queue_image_format->addItem(QString());
        comboBox_queue_image_format->setObjectName(QString::fromUtf8("comboBox_queue_image_format"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_queue_image_format->sizePolicy().hasHeightForWidth());
        comboBox_queue_image_format->setSizePolicy(sizePolicy);

        gridLayout_queue_options->addWidget(comboBox_queue_image_format, 3, 1, 1, 1);

        label_image_type_2 = new QLabel(cDockQueue);
        label_image_type_2->setObjectName(QString::fromUtf8("label_image_type_2"));

        gridLayout_queue_options->addWidget(label_image_type_2, 3, 0, 1, 1);


        verticalLayout->addLayout(gridLayout_queue_options);

        checkBox_show_queue_thumbnails = new MyCheckBox(cDockQueue);
        checkBox_show_queue_thumbnails->setObjectName(QString::fromUtf8("checkBox_show_queue_thumbnails"));

        verticalLayout->addWidget(checkBox_show_queue_thumbnails);

        tableWidget_queue_list = new QTableWidget(cDockQueue);
        tableWidget_queue_list->setObjectName(QString::fromUtf8("tableWidget_queue_list"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget_queue_list->sizePolicy().hasHeightForWidth());
        tableWidget_queue_list->setSizePolicy(sizePolicy1);
        tableWidget_queue_list->setMinimumSize(QSize(0, 150));
        tableWidget_queue_list->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableWidget_queue_list->verticalHeader()->setMinimumSectionSize(70);

        verticalLayout->addWidget(tableWidget_queue_list);

        QWidget::setTabOrder(pushButton_queue_add_current_settings, pushButton_queue_add_from_file);
        QWidget::setTabOrder(pushButton_queue_add_from_file, pushButton_queue_add_orphaned);
        QWidget::setTabOrder(pushButton_queue_add_orphaned, pushButton_queue_remove_orphaned);
        QWidget::setTabOrder(pushButton_queue_remove_orphaned, pushButton_queue_render_queue);
        QWidget::setTabOrder(pushButton_queue_render_queue, pushButton_queue_stop_rendering);
        QWidget::setTabOrder(pushButton_queue_stop_rendering, comboBox_queue_image_format);
        QWidget::setTabOrder(comboBox_queue_image_format, checkBox_show_queue_thumbnails);
        QWidget::setTabOrder(checkBox_show_queue_thumbnails, tableWidget_queue_list);

        retranslateUi(cDockQueue);

        QMetaObject::connectSlotsByName(cDockQueue);
    } // setupUi

    void retranslateUi(QWidget *cDockQueue)
    {
        cDockQueue->setWindowTitle(QCoreApplication::translate("cDockQueue", "Form", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_queue_remove_orphaned->setToolTip(QCoreApplication::translate("cDockQueue", "<html><head/><body><p>Remove files from queue folder which are not on the list.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_queue_remove_orphaned->setText(QCoreApplication::translate("cDockQueue", "Remove orphaned", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_queue_render_queue->setToolTip(QCoreApplication::translate("cDockQueue", "<html><head/><body><p>Render all elements from the queue list.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_queue_render_queue->setText(QCoreApplication::translate("cDockQueue", "Render queue", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_queue_add_orphaned->setToolTip(QCoreApplication::translate("cDockQueue", "<html><head/><body><p>Add orphaned files to the list from queue folder</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_queue_add_orphaned->setText(QCoreApplication::translate("cDockQueue", "Add orphaned", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_queue_add_current_settings->setToolTip(QCoreApplication::translate("cDockQueue", "<html><head/><body><p>Creates a settings file from the current Program Preferences, saves it to the queue folder and adds the entry to the queue list.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_queue_add_current_settings->setText(QCoreApplication::translate("cDockQueue", "Add current settings", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_queue_add_from_file->setToolTip(QCoreApplication::translate("cDockQueue", "<html><head/><body><p>Copies the selected source file to the queue folder and adds the entry to the queue list.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_queue_add_from_file->setText(QCoreApplication::translate("cDockQueue", "Add from file", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_queue_stop_rendering->setToolTip(QCoreApplication::translate("cDockQueue", "<html><head/><body><p>Terminate rendering of queue.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_queue_stop_rendering->setText(QCoreApplication::translate("cDockQueue", "STOP", nullptr));
        comboBox_queue_image_format->setItemText(0, QCoreApplication::translate("cDockQueue", "PNG", nullptr));
        comboBox_queue_image_format->setItemText(1, QCoreApplication::translate("cDockQueue", "JPG", nullptr));
        comboBox_queue_image_format->setItemText(2, QCoreApplication::translate("cDockQueue", "EXR", nullptr));
        comboBox_queue_image_format->setItemText(3, QCoreApplication::translate("cDockQueue", "TIFF", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_queue_image_format->setToolTip(QCoreApplication::translate("cDockQueue", "<html><head/><body><p>Selection for image format for still images</p><p>For more image format settings go to <span style=\" font-style:italic;\">File/Program Preferences</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_image_type_2->setText(QCoreApplication::translate("cDockQueue", "Image file format:", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_show_queue_thumbnails->setToolTip(QCoreApplication::translate("cDockQueue", "<html><head/><body><p>Enables rendering of queue previews in the queue table.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_show_queue_thumbnails->setText(QCoreApplication::translate("cDockQueue", "Show Queue thumbnails", nullptr));
    } // retranslateUi

};

namespace Ui {
    class cDockQueue: public Ui_cDockQueue {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_QUEUE_H
