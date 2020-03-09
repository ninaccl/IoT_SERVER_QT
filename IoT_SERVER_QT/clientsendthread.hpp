#pragma once
#include <QThread>

class ClientSendThread : public QThread {
	Q_OBJECT

public:
	ClientSendThread(QObject * parent = Q_NULLPTR);
	~ClientSendThread();

signals:
	void disconnect(QString ip);	//发送信号给监听线程，指示客户端断联

private:
	private slots:
		void send(QString ip, QString data);	//收到服务器监听线程信号，指定客户端发送数据

protected:
	void run();
	
};
