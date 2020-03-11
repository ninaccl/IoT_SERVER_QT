#pragma once
#include <QObject>
#include <winsock2.h>
#include <winbase.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")			//动态库函数

class MyClient : public QObject {
	Q_OBJECT

public:
	MyClient(SOCKET sClient, sockaddr_in addrClient, QObject * parent = Q_NULLPTR);
	~MyClient();
	SOCKET getSocket();
	QString getIPandPort();

private:
	SOCKET m_socket;	//套接字
	sockaddr_in m_addr;	//地址
	
	
};
