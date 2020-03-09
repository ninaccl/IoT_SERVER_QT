#include "serverlistenthread.hpp"

ServerListenThread::ServerListenThread(QString ip, QString port, QObject * parent) : QThread(parent) {
	this->ip = ip;
	this->port = port;
	bConning = false;
	myserver = new MyServer(ip, port);
	clientvector.clear();
	clientRecvVector.clear();
	clientSendVector.clear();
}

ServerListenThread::~ServerListenThread() {
	delete myserver;
}

/**
* @brief 接收客户端连接线程
*/
void ServerListenThread::run() {
	//检查myserver是否存在
	if (myserver == NULL)
	{
		myserver = new MyServer(ip, port);
	}
	bConning = TRUE;//设置服务器为运行状态
	SOCKET  acceptSocket;	//接受客户端连接的套接字
	sockaddr_in addrClient;	//客户端SOCKET地址
	SOCKET listenSocket = myserver->getSocket();	//取出服务器SOCKET
	while (bConning)	//判断服务器状态
	{
		int	lenClient = sizeof(sockaddr_in);	//地址长度
		memset(&addrClient, 0, lenClient);	//初始化
		acceptSocket = accept(listenSocket, (sockaddr*)&addrClient, &lenClient); //接受客户请求
		if (acceptSocket == INVALID_SOCKET)
		{
			int nErrCode = GetLastError();
			if (nErrCode == WSAEWOULDBLOCK)	//无法立即完成一个非阻挡性套接字操作
			{
				Sleep(TIMEFOR_ACCEPTTHREAD_SLEEP);
				continue;	//继续等待
			}
			else
			{
				bConning = false;	//线程退出
			}
		}
		else//接受客户端的请求
		{
			MyClient *pClient = new MyClient(acceptSocket, addrClient);
			//显示客户端的ip和端口
			char *pClientIP = inet_ntoa(addrClient.sin_addr);
			u_short clientPort = ntohs(addrClient.sin_port);
			clientvector.push_back(pClient);

			//将对应客户端的发送和接收线程加入容器
			ClientRecvThread* recvthread = new ClientRecvThread(pClient);
			ClientSendThread* sendthread = new ClientSendThread(pClient);
			clientRecvVector.push_back(recvthread);
			clientSendVector.push_back(sendthread);

			//连入客户端，发送信号给ui线程
			emit showRecvIP(QString(pClientIP), true);
		}
	}
}