/********************************************************************************
** Form generated from reading UI file 'rendering_netrender_tab.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RENDERING_NETRENDER_TAB_H
#define UI_RENDERING_NETRENDER_TAB_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "my_combo_box.h"
#include "my_line_edit.h"
#include "my_spin_box.h"

QT_BEGIN_NAMESPACE

class Ui_cRenderingNetrenderTab
{
public:
    QVBoxLayout *verticalLayout_5;
    QScrollArea *scrollArea_4;
    QWidget *scrollAreaWidgetContents_4;
    QVBoxLayout *verticalLayout_17;
    QGroupBox *group_netrender;
    QVBoxLayout *verticalLayout_60;
    QGridLayout *gridLayout_29;
    QLabel *label_176;
    MyComboBox *comboBox_netrender_mode;
    QGroupBox *groupBox_netrender_client_config;
    QVBoxLayout *verticalLayout_62;
    QGridLayout *gridLayout_31;
    MyLineEdit *text_netrender_client_remote_address;
    QLabel *label_178;
    QLabel *label_212;
    MySpinBox *spinboxInt_netrender_client_remote_port;
    QGridLayout *gridLayout_connect_to_server;
    QPushButton *bu_netrender_connect;
    QPushButton *bu_netrender_disconnect;
    QGridLayout *gridLayout_server_status;
    QLabel *label_client_status;
    QLabel *label_netrender_client_status;
    QLabel *label_client_connected_server;
    QLabel *label_netrender_client_connected_server;
    QGroupBox *groupBox_netrender_server_config;
    QVBoxLayout *verticalLayout_82;
    QGridLayout *gridLayout_local_server_port;
    MySpinBox *spinboxInt_netrender_server_local_port;
    QLabel *label_216;
    QGridLayout *gridLayout_launch_server;
    QPushButton *bu_netrender_start_server;
    QPushButton *bu_netrender_stop_server;
    QGridLayout *gridLayout_server_status_2;
    QLabel *label_;
    QLabel *label_netrender_server_status;
    QLabel *label_175;
    QTableWidget *tableWidget_netrender_connected_clients;

    void setupUi(QWidget *cRenderingNetrenderTab)
    {
        if (cRenderingNetrenderTab->objectName().isEmpty())
            cRenderingNetrenderTab->setObjectName(QString::fromUtf8("cRenderingNetrenderTab"));
        verticalLayout_5 = new QVBoxLayout(cRenderingNetrenderTab);
        verticalLayout_5->setSpacing(2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(2, 2, 2, 2);
        scrollArea_4 = new QScrollArea(cRenderingNetrenderTab);
        scrollArea_4->setObjectName(QString::fromUtf8("scrollArea_4"));
        scrollArea_4->setWidgetResizable(true);
        scrollAreaWidgetContents_4 = new QWidget();
        scrollAreaWidgetContents_4->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_4"));
        scrollAreaWidgetContents_4->setGeometry(QRect(0, 0, 417, 1082));
        verticalLayout_17 = new QVBoxLayout(scrollAreaWidgetContents_4);
        verticalLayout_17->setSpacing(2);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        verticalLayout_17->setContentsMargins(2, 2, 2, 2);
        group_netrender = new QGroupBox(scrollAreaWidgetContents_4);
        group_netrender->setObjectName(QString::fromUtf8("group_netrender"));
        group_netrender->setCheckable(false);
        group_netrender->setChecked(false);
        verticalLayout_60 = new QVBoxLayout(group_netrender);
        verticalLayout_60->setSpacing(2);
        verticalLayout_60->setObjectName(QString::fromUtf8("verticalLayout_60"));
        verticalLayout_60->setContentsMargins(2, 2, 2, 2);
        gridLayout_29 = new QGridLayout();
        gridLayout_29->setSpacing(2);
        gridLayout_29->setObjectName(QString::fromUtf8("gridLayout_29"));
        label_176 = new QLabel(group_netrender);
        label_176->setObjectName(QString::fromUtf8("label_176"));

        gridLayout_29->addWidget(label_176, 0, 0, 1, 1);

        comboBox_netrender_mode = new MyComboBox(group_netrender);
        comboBox_netrender_mode->addItem(QString());
        comboBox_netrender_mode->addItem(QString());
        comboBox_netrender_mode->setObjectName(QString::fromUtf8("comboBox_netrender_mode"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_netrender_mode->sizePolicy().hasHeightForWidth());
        comboBox_netrender_mode->setSizePolicy(sizePolicy);

        gridLayout_29->addWidget(comboBox_netrender_mode, 0, 1, 1, 1);


        verticalLayout_60->addLayout(gridLayout_29);

        groupBox_netrender_client_config = new QGroupBox(group_netrender);
        groupBox_netrender_client_config->setObjectName(QString::fromUtf8("groupBox_netrender_client_config"));
        groupBox_netrender_client_config->setEnabled(true);
        verticalLayout_62 = new QVBoxLayout(groupBox_netrender_client_config);
        verticalLayout_62->setSpacing(2);
        verticalLayout_62->setObjectName(QString::fromUtf8("verticalLayout_62"));
        verticalLayout_62->setContentsMargins(2, 2, 2, 2);
        gridLayout_31 = new QGridLayout();
        gridLayout_31->setSpacing(2);
        gridLayout_31->setObjectName(QString::fromUtf8("gridLayout_31"));
        text_netrender_client_remote_address = new MyLineEdit(groupBox_netrender_client_config);
        text_netrender_client_remote_address->setObjectName(QString::fromUtf8("text_netrender_client_remote_address"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(text_netrender_client_remote_address->sizePolicy().hasHeightForWidth());
        text_netrender_client_remote_address->setSizePolicy(sizePolicy1);

        gridLayout_31->addWidget(text_netrender_client_remote_address, 0, 1, 1, 1);

        label_178 = new QLabel(groupBox_netrender_client_config);
        label_178->setObjectName(QString::fromUtf8("label_178"));

        gridLayout_31->addWidget(label_178, 0, 0, 1, 1);

        label_212 = new QLabel(groupBox_netrender_client_config);
        label_212->setObjectName(QString::fromUtf8("label_212"));

        gridLayout_31->addWidget(label_212, 1, 0, 1, 1);

        spinboxInt_netrender_client_remote_port = new MySpinBox(groupBox_netrender_client_config);
        spinboxInt_netrender_client_remote_port->setObjectName(QString::fromUtf8("spinboxInt_netrender_client_remote_port"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinboxInt_netrender_client_remote_port->sizePolicy().hasHeightForWidth());
        spinboxInt_netrender_client_remote_port->setSizePolicy(sizePolicy2);
        spinboxInt_netrender_client_remote_port->setMinimum(1);
        spinboxInt_netrender_client_remote_port->setMaximum(99999);

        gridLayout_31->addWidget(spinboxInt_netrender_client_remote_port, 1, 1, 1, 1);


        verticalLayout_62->addLayout(gridLayout_31);

        gridLayout_connect_to_server = new QGridLayout();
        gridLayout_connect_to_server->setSpacing(2);
        gridLayout_connect_to_server->setObjectName(QString::fromUtf8("gridLayout_connect_to_server"));
        bu_netrender_connect = new QPushButton(groupBox_netrender_client_config);
        bu_netrender_connect->setObjectName(QString::fromUtf8("bu_netrender_connect"));
        sizePolicy2.setHeightForWidth(bu_netrender_connect->sizePolicy().hasHeightForWidth());
        bu_netrender_connect->setSizePolicy(sizePolicy2);
        QIcon icon;
        QString iconThemeName = QString::fromUtf8("media-playback-start");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QString::fromUtf8(":/system/icons/media-playback-start.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        bu_netrender_connect->setIcon(icon);

        gridLayout_connect_to_server->addWidget(bu_netrender_connect, 0, 0, 1, 1);

        bu_netrender_disconnect = new QPushButton(groupBox_netrender_client_config);
        bu_netrender_disconnect->setObjectName(QString::fromUtf8("bu_netrender_disconnect"));
        bu_netrender_disconnect->setEnabled(false);
        sizePolicy2.setHeightForWidth(bu_netrender_disconnect->sizePolicy().hasHeightForWidth());
        bu_netrender_disconnect->setSizePolicy(sizePolicy2);
        QIcon icon1;
        iconThemeName = QString::fromUtf8("edit-delete");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QString::fromUtf8(":/system/icons/edit-delete.svg"), QSize(), QIcon::Normal, QIcon::Off);
        }
        bu_netrender_disconnect->setIcon(icon1);

        gridLayout_connect_to_server->addWidget(bu_netrender_disconnect, 1, 0, 1, 1);


        verticalLayout_62->addLayout(gridLayout_connect_to_server);

        gridLayout_server_status = new QGridLayout();
        gridLayout_server_status->setSpacing(2);
        gridLayout_server_status->setObjectName(QString::fromUtf8("gridLayout_server_status"));
        label_client_status = new QLabel(groupBox_netrender_client_config);
        label_client_status->setObjectName(QString::fromUtf8("label_client_status"));

        gridLayout_server_status->addWidget(label_client_status, 0, 0, 1, 1);

        label_netrender_client_status = new QLabel(groupBox_netrender_client_config);
        label_netrender_client_status->setObjectName(QString::fromUtf8("label_netrender_client_status"));
        label_netrender_client_status->setStyleSheet(QString::fromUtf8("color: darkgrey; font-weight: bold; border: 2px solid darkgray;\n"
"border-radius: 3px; background: white; text-align: center; qproperty-alignment: AlignCenter;"));

        gridLayout_server_status->addWidget(label_netrender_client_status, 0, 1, 1, 1);

        label_client_connected_server = new QLabel(groupBox_netrender_client_config);
        label_client_connected_server->setObjectName(QString::fromUtf8("label_client_connected_server"));

        gridLayout_server_status->addWidget(label_client_connected_server, 1, 0, 1, 1);

        label_netrender_client_connected_server = new QLabel(groupBox_netrender_client_config);
        label_netrender_client_connected_server->setObjectName(QString::fromUtf8("label_netrender_client_connected_server"));

        gridLayout_server_status->addWidget(label_netrender_client_connected_server, 1, 1, 1, 1);


        verticalLayout_62->addLayout(gridLayout_server_status);


        verticalLayout_60->addWidget(groupBox_netrender_client_config);

        groupBox_netrender_server_config = new QGroupBox(group_netrender);
        groupBox_netrender_server_config->setObjectName(QString::fromUtf8("groupBox_netrender_server_config"));
        verticalLayout_82 = new QVBoxLayout(groupBox_netrender_server_config);
        verticalLayout_82->setSpacing(2);
        verticalLayout_82->setObjectName(QString::fromUtf8("verticalLayout_82"));
        verticalLayout_82->setContentsMargins(2, 2, 2, 2);
        gridLayout_local_server_port = new QGridLayout();
        gridLayout_local_server_port->setSpacing(2);
        gridLayout_local_server_port->setObjectName(QString::fromUtf8("gridLayout_local_server_port"));
        spinboxInt_netrender_server_local_port = new MySpinBox(groupBox_netrender_server_config);
        spinboxInt_netrender_server_local_port->setObjectName(QString::fromUtf8("spinboxInt_netrender_server_local_port"));
        sizePolicy2.setHeightForWidth(spinboxInt_netrender_server_local_port->sizePolicy().hasHeightForWidth());
        spinboxInt_netrender_server_local_port->setSizePolicy(sizePolicy2);
        spinboxInt_netrender_server_local_port->setMinimum(1);
        spinboxInt_netrender_server_local_port->setMaximum(99999);

        gridLayout_local_server_port->addWidget(spinboxInt_netrender_server_local_port, 0, 1, 1, 1);

        label_216 = new QLabel(groupBox_netrender_server_config);
        label_216->setObjectName(QString::fromUtf8("label_216"));

        gridLayout_local_server_port->addWidget(label_216, 0, 0, 1, 1);


        verticalLayout_82->addLayout(gridLayout_local_server_port);

        gridLayout_launch_server = new QGridLayout();
        gridLayout_launch_server->setSpacing(2);
        gridLayout_launch_server->setObjectName(QString::fromUtf8("gridLayout_launch_server"));
        bu_netrender_start_server = new QPushButton(groupBox_netrender_server_config);
        bu_netrender_start_server->setObjectName(QString::fromUtf8("bu_netrender_start_server"));
        sizePolicy2.setHeightForWidth(bu_netrender_start_server->sizePolicy().hasHeightForWidth());
        bu_netrender_start_server->setSizePolicy(sizePolicy2);
        bu_netrender_start_server->setIcon(icon);

        gridLayout_launch_server->addWidget(bu_netrender_start_server, 0, 0, 1, 1);

        bu_netrender_stop_server = new QPushButton(groupBox_netrender_server_config);
        bu_netrender_stop_server->setObjectName(QString::fromUtf8("bu_netrender_stop_server"));
        bu_netrender_stop_server->setEnabled(false);
        sizePolicy2.setHeightForWidth(bu_netrender_stop_server->sizePolicy().hasHeightForWidth());
        bu_netrender_stop_server->setSizePolicy(sizePolicy2);
        bu_netrender_stop_server->setIcon(icon1);

        gridLayout_launch_server->addWidget(bu_netrender_stop_server, 1, 0, 1, 1);


        verticalLayout_82->addLayout(gridLayout_launch_server);

        gridLayout_server_status_2 = new QGridLayout();
        gridLayout_server_status_2->setSpacing(2);
        gridLayout_server_status_2->setObjectName(QString::fromUtf8("gridLayout_server_status_2"));
        label_ = new QLabel(groupBox_netrender_server_config);
        label_->setObjectName(QString::fromUtf8("label_"));

        gridLayout_server_status_2->addWidget(label_, 0, 0, 1, 1);

        label_netrender_server_status = new QLabel(groupBox_netrender_server_config);
        label_netrender_server_status->setObjectName(QString::fromUtf8("label_netrender_server_status"));
        label_netrender_server_status->setStyleSheet(QString::fromUtf8("color: darkgrey; font-weight: bold; border: 2px solid darkgray;\n"
"border-radius: 3px; background: white; text-align: center; qproperty-alignment: AlignCenter;"));

        gridLayout_server_status_2->addWidget(label_netrender_server_status, 0, 1, 1, 1);


        verticalLayout_82->addLayout(gridLayout_server_status_2);

        label_175 = new QLabel(groupBox_netrender_server_config);
        label_175->setObjectName(QString::fromUtf8("label_175"));

        verticalLayout_82->addWidget(label_175);

        tableWidget_netrender_connected_clients = new QTableWidget(groupBox_netrender_server_config);
        tableWidget_netrender_connected_clients->setObjectName(QString::fromUtf8("tableWidget_netrender_connected_clients"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tableWidget_netrender_connected_clients->sizePolicy().hasHeightForWidth());
        tableWidget_netrender_connected_clients->setSizePolicy(sizePolicy3);
        tableWidget_netrender_connected_clients->setSizeAdjustPolicy(QAbstractScrollArea::AdjustToContents);

        verticalLayout_82->addWidget(tableWidget_netrender_connected_clients);


        verticalLayout_60->addWidget(groupBox_netrender_server_config);


        verticalLayout_17->addWidget(group_netrender);

        scrollArea_4->setWidget(scrollAreaWidgetContents_4);

        verticalLayout_5->addWidget(scrollArea_4);


        retranslateUi(cRenderingNetrenderTab);

        comboBox_netrender_mode->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(cRenderingNetrenderTab);
    } // setupUi

    void retranslateUi(QWidget *cRenderingNetrenderTab)
    {
#if QT_CONFIG(tooltip)
        group_netrender->setToolTip(QCoreApplication::translate("cRenderingNetrenderTab", "<html><head/><body><p>This feature allows the connection of multiple computers into a network to share rendering.</p><p>The same image or animation can be rendered using an unlimited number of computers. The increased computing power will reduce rendering time.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        group_netrender->setTitle(QCoreApplication::translate("cRenderingNetrenderTab", "NetRender", nullptr));
        label_176->setText(QCoreApplication::translate("cRenderingNetrenderTab", "Mode:", nullptr));
        comboBox_netrender_mode->setItemText(0, QCoreApplication::translate("cRenderingNetrenderTab", "Client", nullptr));
        comboBox_netrender_mode->setItemText(1, QCoreApplication::translate("cRenderingNetrenderTab", "Server", nullptr));

#if QT_CONFIG(tooltip)
        comboBox_netrender_mode->setToolTip(QCoreApplication::translate("cRenderingNetrenderTab", "<html><head/><body><p>Switches between server and client.</p><p><span style=\" font-weight:600;\">Server</span> is the main application in the network. It controls rendering process, sends data to all clients and collects data from them. <br/>Server compiles parts of images received from the clients and finally displays the whole image. It also renders image.</p><p><span style=\" font-weight:600;\">Client</span> receives jobs from server. It renders only the parts of the image which the server ask for. It displays only partial image.</p><p>To start rendering process on all computers you need to press Render button on Server.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_netrender_client_config->setTitle(QCoreApplication::translate("cRenderingNetrenderTab", "Client configuration:", nullptr));
#if QT_CONFIG(tooltip)
        text_netrender_client_remote_address->setToolTip(QCoreApplication::translate("cRenderingNetrenderTab", "<html><head/><body><p>IP address or name of the computer where Mandelbulber  is launched in server mode.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_178->setText(QCoreApplication::translate("cRenderingNetrenderTab", "Remote server address:", nullptr));
        label_212->setText(QCoreApplication::translate("cRenderingNetrenderTab", "Remote server port:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_netrender_client_remote_port->setToolTip(QCoreApplication::translate("cRenderingNetrenderTab", "<html><head/><body><p>Port number which is set on Mandelbulber which runs in server mode.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        bu_netrender_connect->setToolTip(QCoreApplication::translate("cRenderingNetrenderTab", "<html><head/><body><p>Establish connection with server.</p><p>When connection is established, status should change to READY</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_netrender_connect->setText(QCoreApplication::translate("cRenderingNetrenderTab", "Connect to server", nullptr));
        bu_netrender_disconnect->setText(QCoreApplication::translate("cRenderingNetrenderTab", "Disconnect", nullptr));
        label_client_status->setText(QCoreApplication::translate("cRenderingNetrenderTab", "Status:", nullptr));
        label_netrender_client_status->setText(QCoreApplication::translate("cRenderingNetrenderTab", "DISABLED", nullptr));
        label_client_connected_server->setText(QCoreApplication::translate("cRenderingNetrenderTab", "Connected Server:", nullptr));
        label_netrender_client_connected_server->setText(QCoreApplication::translate("cRenderingNetrenderTab", "---", nullptr));
        groupBox_netrender_server_config->setTitle(QCoreApplication::translate("cRenderingNetrenderTab", "Server configuration:", nullptr));
#if QT_CONFIG(tooltip)
        spinboxInt_netrender_server_local_port->setToolTip(QCoreApplication::translate("cRenderingNetrenderTab", "<html><head/><body><p>Internet port number which will be used for server. This port has to not be blocked by a firewall or  passed through a router.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_216->setText(QCoreApplication::translate("cRenderingNetrenderTab", "Local server port:", nullptr));
#if QT_CONFIG(tooltip)
        bu_netrender_start_server->setToolTip(QCoreApplication::translate("cRenderingNetrenderTab", "<html><head/><body><p>Starts Mandelbulber to work as server.</p><p>After pressing this button, application starts to watch clients and connect to them. </p><p>If connection with a client is established, then this client is displayed in the table below.</p><p>To establish a connection with a client, the Connect button must be pressed on the client side </p><p>If all needed computers are already connected, then the server is ready for operation. If you press Render button, then the server and all the clients will start rendering of the same image.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        bu_netrender_start_server->setText(QCoreApplication::translate("cRenderingNetrenderTab", "Launch server and watch for clients", nullptr));
        bu_netrender_stop_server->setText(QCoreApplication::translate("cRenderingNetrenderTab", "Stop Server", nullptr));
        label_->setText(QCoreApplication::translate("cRenderingNetrenderTab", "Status:", nullptr));
        label_netrender_server_status->setText(QCoreApplication::translate("cRenderingNetrenderTab", "DISABLED", nullptr));
        label_175->setText(QCoreApplication::translate("cRenderingNetrenderTab", "List of connected clients", nullptr));
        (void)cRenderingNetrenderTab;
    } // retranslateUi

};

namespace Ui {
    class cRenderingNetrenderTab: public Ui_cRenderingNetrenderTab {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RENDERING_NETRENDER_TAB_H
