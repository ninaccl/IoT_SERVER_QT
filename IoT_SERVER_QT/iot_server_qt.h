#ifndef IOT_SERVER_QT_H
#define IOT_SERVER_QT_H

#include <QtWidgets/QMainWindow>
#include <QtNetwork>
#include "ui_iot_server_qt.h"
#include "myserver.hpp"
#include "serverlistenthread.hpp"

class IoT_SERVER_QT : public QMainWindow
{
	Q_OBJECT

public:
	IoT_SERVER_QT(QWidget *parent = 0);
	~IoT_SERVER_QT();

signals:
	void sendLightControl(QString ip, QString data);	//发送灯控信号给监听线程

private slots:
	void startServer();	//点击connectButton，开启/关闭服务器
	void recvData(QString ip, QString data);	//收到监听线程发送信号，接收数据显示
	void controlLight();	//点击lightButton进行亮灯/灭灯操作
	void showClient(QString ip, bool added);	//收到监听线程发送信号，显示或删除连入的IP地址

private:
	Ui::IoT_SERVER_QTClass ui;
	ServerListenThread *listenThread;
};

#endif // IOT_SERVER_QT_H
