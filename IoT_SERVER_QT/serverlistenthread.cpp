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
	for (auto it = clientRecvVector.begin(); it != clientRecvVector.end(); it++)
	{
		(*it)->changestate();
		(*it)->quit();
		(*it)->wait();
	}
	clearVector(clientRecvVector);
	clearVector(clientSendVector);
	clearVector(clientvector);
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
			//char *pClientIP = inet_ntoa(addrClient.sin_addr);
			//u_short clientPort = ntohs(addrClient.sin_port);
			clientvector.push_back(pClient);

			//将对应客户端的发送和接收线程加入容器
			ClientRecvThread* recvthread = new ClientRecvThread(pClient);
			ClientSendThread* sendthread = new ClientSendThread(pClient);
			clientRecvVector.push_back(recvthread);
			clientSendVector.push_back(sendthread);
			connect(recvthread, SIGNAL(Recv(QString, QString)), this, SLOT(getRecvData(QString,QString)));
			connect(recvthread, SIGNAL(disconnect(QString)), this, SLOT(clientDisconnect(QString)));
			connect(sendthread, SIGNAL(disconnect(QString)), this, SLOT(clientDisconnect(QString)));
//			connect(this, SIGNAL(sendData(QString, QString)), sendthread, SLOT(sendDatatoClient(QString, QString)),Qt::QueuedConnection);

			recvthread->start();

			//连入客户端，发送信号给ui线程
			emit showRecvIP(pClient->getIPandPort(), true);
		}
	}
}

/**
* @brief 收到客户端数据
* @param ip 收到数据的客户端ip
* @param data 收到的数据
*/
void ServerListenThread::getRecvData(QString ip, QString data)
{
	emit showRecvData(ip, data);
	if(!data.compare(PING))
	{
		QString dataSend(data);
//		emit sendData(ip, dataSend);
		getSendLightData(ip, dataSend);
	}
}

/**
* @brief 清理断联客户端
* @param ip 收到数据的客户端ip
* @param data 收到的数据
*/
void ServerListenThread::clientDisconnect(QString ip)
{
	//若没有已连接客户端
	if (clientvector.size() == 0)
	{
		return;
	}
	else
	{
		clearDisconnectClient(clientRecvVector, ip);
		clearDisconnectClient(clientSendVector, ip);
		clearDisconnectClient(clientvector, ip);
	}
	emit showRecvIP(ip, false);
}

/**
* @brief 清理容器，析构其中元素
* @param v 存放线程或类的容器
*/
template<class T>
void ServerListenThread::clearVector(vector<T*> &v)
{
	for (auto iter = v.begin(); iter != v.end();)
	{
		T* pEle = (T*)*iter;
		iter = v.erase(iter);
		delete pEle;
		pEle = NULL;
		iter++;
	}
}

/**
* @brief 清理容器，析构其中元素
* @param v 存放线程或类的容器
*/
template<class T>
void ServerListenThread::clearDisconnectClient(vector<T*> &v, QString ip) {
	//清理已断开的连接客户端内存空间
	for(auto iter = v.begin(); iter != v.end(); iter++)
	{
		T* pClient = (T*)*iter;
		if (pClient->getIPandPort() == ip)	//客户端断联
		{
			//删除节点
			T* pEle = (T*)*iter;
			iter = v.erase(iter);
			delete pEle;
			pEle = NULL;
			break;
		}
	}
}

void ServerListenThread::getSendLightData(QString ip, QString data) {
//	emit sendData(ip, data);
	for (auto it = clientSendVector.begin(); it != clientSendVector.end(); it++)
	{
		if ((*it)->getIPandPort() == ip)
		{
			(*it)->sendDatatoClient(ip, data);
		}
	}
}

/**
* @brief 改变运行状态
*/
void ServerListenThread::changeState()
{
	bConning = false;
}