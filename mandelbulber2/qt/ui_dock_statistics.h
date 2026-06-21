/********************************************************************************
** Form generated from reading UI file 'dock_statistics.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOCK_STATISTICS_H
#define UI_DOCK_STATISTICS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_histogram_label.h"

QT_BEGIN_NAMESPACE

class Ui_cDockStatistics
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_17;
    QVBoxLayout *verticalLayout_histogram_iter;
    QLabel *label_hist_iter;
    MyHistogramLabel *label_histogram_iter;
    QVBoxLayout *verticalLayout_histogram_de;
    QLabel *label_hist_de;
    MyHistogramLabel *label_histogram_de;
    QTableWidget *tableWidget_statistics;

    void setupUi(QWidget *cDockStatistics)
    {
        if (cDockStatistics->objectName().isEmpty())
            cDockStatistics->setObjectName(QString::fromUtf8("cDockStatistics"));
        cDockStatistics->resize(417, 384);
        verticalLayout = new QVBoxLayout(cDockStatistics);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(2);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalLayout_17->setContentsMargins(2, 2, 2, 2);
        verticalLayout_histogram_iter = new QVBoxLayout();
        verticalLayout_histogram_iter->setObjectName(QString::fromUtf8("verticalLayout_histogram_iter"));
        label_hist_iter = new QLabel(cDockStatistics);
        label_hist_iter->setObjectName(QString::fromUtf8("label_hist_iter"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_hist_iter->sizePolicy().hasHeightForWidth());
        label_hist_iter->setSizePolicy(sizePolicy);
        label_hist_iter->setWordWrap(true);

        verticalLayout_histogram_iter->addWidget(label_hist_iter);

        label_histogram_iter = new MyHistogramLabel(cDockStatistics);
        label_histogram_iter->setObjectName(QString::fromUtf8("label_histogram_iter"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_histogram_iter->sizePolicy().hasHeightForWidth());
        label_histogram_iter->setSizePolicy(sizePolicy1);
        label_histogram_iter->setMinimumSize(QSize(0, 40));

        verticalLayout_histogram_iter->addWidget(label_histogram_iter);


        horizontalLayout_17->addLayout(verticalLayout_histogram_iter);

        verticalLayout_histogram_de = new QVBoxLayout();
        verticalLayout_histogram_de->setObjectName(QString::fromUtf8("verticalLayout_histogram_de"));
        label_hist_de = new QLabel(cDockStatistics);
        label_hist_de->setObjectName(QString::fromUtf8("label_hist_de"));
        sizePolicy.setHeightForWidth(label_hist_de->sizePolicy().hasHeightForWidth());
        label_hist_de->setSizePolicy(sizePolicy);
        label_hist_de->setMinimumSize(QSize(0, 0));
        label_hist_de->setWordWrap(true);

        verticalLayout_histogram_de->addWidget(label_hist_de);

        label_histogram_de = new MyHistogramLabel(cDockStatistics);
        label_histogram_de->setObjectName(QString::fromUtf8("label_histogram_de"));
        sizePolicy1.setHeightForWidth(label_histogram_de->sizePolicy().hasHeightForWidth());
        label_histogram_de->setSizePolicy(sizePolicy1);
        label_histogram_de->setMinimumSize(QSize(0, 40));

        verticalLayout_histogram_de->addWidget(label_histogram_de);


        horizontalLayout_17->addLayout(verticalLayout_histogram_de);


        verticalLayout->addLayout(horizontalLayout_17);

        tableWidget_statistics = new QTableWidget(cDockStatistics);
        if (tableWidget_statistics->columnCount() < 1)
            tableWidget_statistics->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget_statistics->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (tableWidget_statistics->rowCount() < 6)
            tableWidget_statistics->setRowCount(6);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget_statistics->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget_statistics->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget_statistics->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget_statistics->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget_statistics->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget_statistics->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget_statistics->setItem(0, 0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableWidget_statistics->setItem(1, 0, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableWidget_statistics->setItem(2, 0, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableWidget_statistics->setItem(3, 0, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableWidget_statistics->setItem(4, 0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableWidget_statistics->setItem(5, 0, __qtablewidgetitem12);
        tableWidget_statistics->setObjectName(QString::fromUtf8("tableWidget_statistics"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tableWidget_statistics->sizePolicy().hasHeightForWidth());
        tableWidget_statistics->setSizePolicy(sizePolicy2);
        tableWidget_statistics->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);
        tableWidget_statistics->setShowGrid(true);
        tableWidget_statistics->horizontalHeader()->setMinimumSectionSize(14);
        tableWidget_statistics->horizontalHeader()->setDefaultSectionSize(150);
        tableWidget_statistics->verticalHeader()->setCascadingSectionResizes(false);
        tableWidget_statistics->verticalHeader()->setMinimumSectionSize(14);
        tableWidget_statistics->verticalHeader()->setDefaultSectionSize(20);

        verticalLayout->addWidget(tableWidget_statistics);

        verticalLayout->setStretch(0, 1);

        retranslateUi(cDockStatistics);

        QMetaObject::connectSlotsByName(cDockStatistics);
    } // setupUi

    void retranslateUi(QWidget *cDockStatistics)
    {
        cDockStatistics->setWindowTitle(QCoreApplication::translate("cDockStatistics", "Form", nullptr));
        label_hist_iter->setText(QCoreApplication::translate("cDockStatistics", "Histogram of fractal iteration count", nullptr));
        label_hist_de->setText(QCoreApplication::translate("cDockStatistics", "Histogram of ray-marching step count", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget_statistics->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("cDockStatistics", "Value", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget_statistics->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("cDockStatistics", "Total number of iterations", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget_statistics->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("cDockStatistics", "Number of iterations per pixel", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget_statistics->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("cDockStatistics", "Number of iterations per second", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget_statistics->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("cDockStatistics", "Distance estimation algorithm", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget_statistics->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("cDockStatistics", "Percentage of wrong distance estimations", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget_statistics->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("cDockStatistics", "Distance of camera to fractal surface", nullptr));

        const bool __sortingEnabled = tableWidget_statistics->isSortingEnabled();
        tableWidget_statistics->setSortingEnabled(false);
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget_statistics->item(0, 0);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("cDockStatistics", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableWidget_statistics->item(1, 0);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("cDockStatistics", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableWidget_statistics->item(2, 0);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("cDockStatistics", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableWidget_statistics->item(4, 0);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("cDockStatistics", "0", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableWidget_statistics->item(5, 0);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("cDockStatistics", "0", nullptr));
        tableWidget_statistics->setSortingEnabled(__sortingEnabled);

    } // retranslateUi

};

namespace Ui {
    class cDockStatistics: public Ui_cDockStatistics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOCK_STATISTICS_H
