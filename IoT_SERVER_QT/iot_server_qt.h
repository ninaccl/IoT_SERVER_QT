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
	void sendLightControl(QString ip, QString data);	//���͵ƿ��źŸ������߳�

private slots:
	void startServer();	//���connectButton������/�رշ�����
	void recvData(QString ip, QString data);	//�յ������̷߳����źţ�����������ʾ
	void controlLight();	//���lightButton��������/��Ʋ���
	void showClient(QString ip, bool added);	//�յ������̷߳����źţ���ʾ��ɾ�������IP��ַ

private:
	Ui::IoT_SERVER_QTClass ui;
	ServerListenThread *listenThread;
};

#endif // IOT_SERVER_QT_H
