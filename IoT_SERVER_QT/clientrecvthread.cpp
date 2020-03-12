#include "clientrecvthread.hpp"

ClientRecvThread::ClientRecvThread(MyClient *pClient, QObject * parent) : QThread(parent) {
	this->pClient = pClient;
	running = TRUE;
}

ClientRecvThread::~ClientRecvThread() {
}

/**
* @brief 客户端接收线程
*/
void ClientRecvThread::run()
{
	int		reVal;							//返回值
	char	temp[MAX_NUM_BUF];				//临时变量

	while (running)				//连接状态
	{
		memset(temp, 0, MAX_NUM_BUF);
		reVal = recv(pClient->getSocket(), temp, MAX_NUM_BUF, 0);	//接收数据
		//处理错误返回值
		if (SOCKET_ERROR == reVal)
		{
			int err = WSAGetLastError();
			if (WSAETIMEDOUT == err || WSAENETDOWN == err || WSAECONNRESET == err)
			{
				running = false;
				break;
			}
		}
		//客户端关闭了连接
		if (reVal == 0)
		{
			running = false;
			break;
		}

		//收到数据
		if (reVal > 0)
		{
			temp[reVal] = '\0';
			QString data(temp);
			emit Recv(pClient->getIPandPort(), data);
		}
	}
	emit disconnect(pClient->getIPandPort());
}

/**
* @brief 获取ip
* @return 返回ip
*/
QString ClientRecvThread::getIPandPort() {
	return pClient->getIPandPort();
}

/**
* @brief 改变运行状态
*/
void ClientRecvThread::changestate()
{
	running = false;
}