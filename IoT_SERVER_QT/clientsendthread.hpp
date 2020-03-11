#pragma once
#include <QThread>
#include"myclient.hpp"

class ClientSendThread : public QObject {
	Q_OBJECT

public:
	ClientSendThread(MyClient *pClient, QObject * parent = Q_NULLPTR);
	~ClientSendThread();
	QString getIPandPort();

//private slots:
	void sendDatatoClient(QString ip, QString data);	//收到服务器监听线程信号，指定客户端发送数据

signals:
	void disconnect(QString ip);	//发送信号给监听线程，指示客户端断联



private:
	MyClient *pClient;	//存储客户端基本信息
		
};
