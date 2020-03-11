/********************************************************************************
** Form generated from reading UI file 'iot_server_qt.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IOT_SERVER_QT_H
#define UI_IOT_SERVER_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IoT_SERVER_QTClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *ipLabel;
    QLineEdit *ipLineEdit;
    QLabel *portLabel;
    QLineEdit *portLineEdit;
    QPushButton *connectPushButton;
    QTableWidget *tableWidget;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *dataLabel;
    QTextEdit *recvTextEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *IoT_SERVER_QTClass)
    {
        if (IoT_SERVER_QTClass->objectName().isEmpty())
            IoT_SERVER_QTClass->setObjectName(QStringLiteral("IoT_SERVER_QTClass"));
        IoT_SERVER_QTClass->resize(600, 400);
        centralWidget = new QWidget(IoT_SERVER_QTClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, -1, -1);
        ipLabel = new QLabel(centralWidget);
        ipLabel->setObjectName(QStringLiteral("ipLabel"));
        ipLabel->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(ipLabel);

        ipLineEdit = new QLineEdit(centralWidget);
        ipLineEdit->setObjectName(QStringLiteral("ipLineEdit"));
        ipLineEdit->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(ipLineEdit);

        portLabel = new QLabel(centralWidget);
        portLabel->setObjectName(QStringLiteral("portLabel"));
        portLabel->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(portLabel);

        portLineEdit = new QLineEdit(centralWidget);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));
        portLineEdit->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(portLineEdit);

        connectPushButton = new QPushButton(centralWidget);
        connectPushButton->setObjectName(QStringLiteral("connectPushButton"));
        connectPushButton->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(connectPushButton);

        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setMaximumSize(QSize(200, 16777215));

        verticalLayout->addWidget(tableWidget);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, -1, -1, -1);
        dataLabel = new QLabel(centralWidget);
        dataLabel->setObjectName(QStringLiteral("dataLabel"));

        verticalLayout_2->addWidget(dataLabel);

        recvTextEdit = new QTextEdit(centralWidget);
        recvTextEdit->setObjectName(QStringLiteral("recvTextEdit"));

        verticalLayout_2->addWidget(recvTextEdit);


        horizontalLayout->addLayout(verticalLayout_2);

        IoT_SERVER_QTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(IoT_SERVER_QTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        IoT_SERVER_QTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(IoT_SERVER_QTClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        IoT_SERVER_QTClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(IoT_SERVER_QTClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        IoT_SERVER_QTClass->setStatusBar(statusBar);

        retranslateUi(IoT_SERVER_QTClass);

        QMetaObject::connectSlotsByName(IoT_SERVER_QTClass);
    } // setupUi

    void retranslateUi(QMainWindow *IoT_SERVER_QTClass)
    {
        IoT_SERVER_QTClass->setWindowTitle(QApplication::translate("IoT_SERVER_QTClass", "IoT_SERVER_QT", Q_NULLPTR));
        ipLabel->setText(QApplication::translate("IoT_SERVER_QTClass", "IP", Q_NULLPTR));
        portLabel->setText(QApplication::translate("IoT_SERVER_QTClass", "Port", Q_NULLPTR));
        portLineEdit->setText(QApplication::translate("IoT_SERVER_QTClass", "8081", Q_NULLPTR));
        connectPushButton->setText(QApplication::translate("IoT_SERVER_QTClass", "Connect", Q_NULLPTR));
        dataLabel->setText(QApplication::translate("IoT_SERVER_QTClass", "Data", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class IoT_SERVER_QTClass: public Ui_IoT_SERVER_QTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IOT_SERVER_QT_H
