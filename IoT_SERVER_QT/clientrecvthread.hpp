#pragma once
#include <QThread>
#include "myclient.hpp"

#define MAX_NUM_BUF 64

class ClientRecvThread : public QThread {
	Q_OBJECT

public:
	ClientRecvThread(MyClient* pClient, QObject * parent = Q_NULLPTR);
	~ClientRecvThread();
	QString getIPandPort();
	void changestate();	//改变运行状态

signals:
	void Recv(QString ip, QString data);	//收到数据，发送信号给监听线程
signals:
	void disconnect(QString ip);	//发送信号给监听线程，指示客户端断联

protected:
	void run();

private:
	MyClient *pClient;	//存储客户端基本信息
	bool running = false;	//指示运行状态
};
