#include "myclient.hpp"

MyClient::MyClient(SOCKET sClient, sockaddr_in addrClient, QObject * parent) : QObject(parent) {
	m_socket = sClient;
	m_addr = addrClient;

	//将套接字改为非阻塞
	unsigned long ul = 1;
	ioctlsocket(m_socket, FIONBIO, (unsigned long*)&ul);
}

MyClient::~MyClient() {
	closesocket(m_socket);			//关闭套接字
	m_socket = INVALID_SOCKET;		//套接字无效
}

/**
* @brief 获取Socket
* @return 返回Socket
*/
SOCKET MyClient::getSocket()
{
	return m_socket;
}

/**
* @brief 获取ip和port
* @return 返回ip和port
*/
QString MyClient::getIPandPort()
{
	return QString(inet_ntoa(m_addr.sin_addr)) + ":" + QString::number(m_addr.sin_port);
}
