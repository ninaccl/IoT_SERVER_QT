#pragma once
#include <QThread>

class ClientRecvThread : public QThread {
	Q_OBJECT

public:
	ClientRecvThread(QObject * parent = Q_NULLPTR);
	~ClientRecvThread();

signals:
	void Recv(QString ip, QString data);	//收到数据，发送信号给监听线程

protected:
	void run();

private:
	
};
