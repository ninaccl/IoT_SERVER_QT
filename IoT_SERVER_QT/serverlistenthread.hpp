#pragma once
#include <QThread>
#include <vector>
#include "myserver.hpp"
#include "myclient.hpp"
#include "clientrecvthread.hpp"
#include "clientsendthread.hpp"

using namespace std;

#define TIMEFOR_ACCEPTTHREAD_SLEEP 500	//等待客户端请求线程睡眠时间

class ServerListenThread : public QThread {
	Q_OBJECT

public:
	ServerListenThread(QString ip, QString port, QObject * parent = Q_NULLPTR);
	~ServerListenThread();

signals:
	void showRecvData(QString ip, QString data);	//收到数据，发送信号给ui线程
	void showRecvIP(QString ip, bool added);	//连入客户端，发送信号给ui线程
	void sendData(QString ip, QString data);	//有数据发送，发送信号给clientsend线程

protected:
	void run();

private:
	MyServer *myserver;
	bool bConning;	//服务器开启状态
	QString ip;	//IP
	QString port;	//PORT
	vector<MyClient* > clientvector;	//客户端容器
	vector<ClientRecvThread* > clientRecvVector;	//客户端接收线程容器
	vector<ClientSendThread* > clientSendVector;	//客户端发送线程容器

private slots :
	void getRecvData(QString ip, QString data);	//收到clientrecv线程传来的信号，得到客户端收到数据
	void clientDisconnect(QString ip);	//收到clientsend线程传来的信号，指示客户端断联
	void getSendLightData(QString ip, QString data);	//收到ui线程传来的灯控信号，转发给clientsend线程
	
};
