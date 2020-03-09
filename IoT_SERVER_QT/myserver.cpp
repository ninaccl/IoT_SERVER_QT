#include "myserver.hpp"

MyServer::MyServer(QString ip, QString port, QObject * parent = Q_NULLPTR) : QObject(parent) {
	initServer();
}

MyServer::~MyServer() {
	exitServer();
}

/**
* @brief 初始化服务器
* @return 返回初始化结果，初始化是否成功
*      @retval true 正常
*      @retval false 异常
*/
bool MyServer::initServer() {
	//初始化全局变量
	initMember();

	//初始化SOCKET
	if (!initSocket())
		return FALSE;

	return TRUE;
}

/**
* @brief 初始化成员变量
*/
void MyServer::initMember() {
	listenSocket = INVALID_SOCKET;	//设置为无效的套接字
}

/**
* @brief 初始化非阻塞套接字
* @return 返回初始化结果，初始化是否成功
*      @retval true 正常
*      @retval false 异常
*/
bool MyServer::initSocket() {
	//返回值
	int reVal;

	//初始化Windows Sockets DLL
	WSADATA  wsData;
	reVal = WSAStartup(MAKEWORD(2, 2), &wsData);

	//创建套接字
	listenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == listenSocket)
	{
		wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
		//WSACleanup();
		return FALSE;
	}

	//绑定套接字
	sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(port.toUShort());
	serAddr.sin_addr.S_un.S_addr = inet_addr(ip.toStdString().c_str());
	reVal = bind(listenSocket, (struct sockaddr*)&serAddr, sizeof(serAddr));
	if (SOCKET_ERROR == reVal)
		return FALSE;

	//监听
	reVal = listen(listenSocket, CONN_NUM);
	if (SOCKET_ERROR == reVal)
		return FALSE;

	return TRUE;
}

/**
* @brief 释放资源
*/
void MyServer::exitServer() {
	closesocket(listenSocket);	//关闭SOCKET
	WSACleanup();	//卸载Windows Sockets DLL
}

/**
* @brief 获取listen套接字
* @return 返回listenSocket
*/
SOCKET MyServer::getSocket() {
	return listenSocket;
}