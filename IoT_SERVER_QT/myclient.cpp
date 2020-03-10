#include "myclient.hpp"

MyClient::MyClient(SOCKET sClient, sockaddr_in addrClient, QObject * parent) : QObject(parent) {
	m_socket = sClient;
	m_addr = addrClient;
}

MyClient::~MyClient() {
	closesocket(m_socket);			//关闭套接字
	m_socket = INVALID_SOCKET;		//套接字无效
}

SOCKET MyClient::getSocket()
{
	return m_socket;
}

QString MyClient::getIP()
{
	return QString(inet_ntoa(m_addr.sin_addr));
}