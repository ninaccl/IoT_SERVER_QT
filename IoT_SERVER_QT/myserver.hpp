#pragma once
#include <QObject>
#include <vector>
#include <winsock2.h>
#include <winbase.h>
#include "myclient.hpp"


// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")			//动态库函数

using namespace std;

#define CONN_NUM 7

class MyServer : public QObject {
	Q_OBJECT

public:
	MyServer(QString ip, QString port, QObject * parent = Q_NULLPTR);
	~MyServer();
	SOCKET getSocket();	//获取listen套接字

private:
	QString ip;	//IP
	QString port;	//PORT
	SOCKET listenSocket;	//监听套接字

	bool initServer();	//初始化服务器
	void initMember();	//初始化全局变量
	bool initSocket();	//初始化非阻塞套接字
	void exitServer();	//释放资源
};
