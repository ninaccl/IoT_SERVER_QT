#include "iot_server_qt.h"

IoT_SERVER_QT::IoT_SERVER_QT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//获取IP地址并显示
	QString ip = QNetworkInterface().allAddresses().at(0).toString();
	ui.ipLineEdit->setText(ip);

	connect(ui.connectPushButton, QPushButton::clicked, this, startServer);
}

IoT_SERVER_QT::~IoT_SERVER_QT()
{

}

/**
* @brief 开启服务器，接收客户端连接
*/
void IoT_SERVER_QT::startServer()
{
	//获取ip和端口
	QString ip = ui.ipLineEdit->text();
	QString port = ui.ipLineEdit->text();

	//判断listenThread的状态
	if (listenThread == NULL || !listenThread->isRunning())
	{
		//服务器初始化

		//修改按钮名称
	}
	else
	{
		//停止线程运行

		//修改按钮名称
	}

	

	
}