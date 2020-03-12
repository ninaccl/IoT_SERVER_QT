#include "clientsendthread.hpp"

ClientSendThread::ClientSendThread(MyClient *pClient, QObject * parent) : QObject(parent) {
	this->pClient = pClient;
}

ClientSendThread::~ClientSendThread() {
}


/**
* @brief 客户端发送数据
* @param ip 发送数据的客户端ip
* @param data 发送的数据
*/
void ClientSendThread::sendDatatoClient(QString ip, QString data)
{
	if (pClient->getIPandPort() == ip)
	{
		//加上ODOA回车换行
		data.append('\r');
		data.append('\n');
		//QString转char*
		char*  dataBuf;
		QByteArray ba = data.toLatin1();
		dataBuf = ba.data();
		//发送数据
		int val = send(pClient->getSocket(), dataBuf, strlen(dataBuf), 0);
		//处理返回错误
		if (SOCKET_ERROR == val)
		{
			int nErrCode = WSAGetLastError();
			if (nErrCode == WSAEWOULDBLOCK)//发送数据缓冲区不可用
			{
				sendDatatoClient(ip, data);
			}
			else if (WSAENETDOWN == nErrCode ||
				WSAETIMEDOUT == nErrCode ||
				WSAECONNRESET == nErrCode)//客户端关闭了连接
			{
				emit disconnect(ip);
			}
			else {
				emit disconnect(ip);
			}
		}
	}
}

/**
* @brief 获取ip
* @return 返回ip
*/
QString ClientSendThread::getIPandPort() {
	return pClient->getIPandPort();
}