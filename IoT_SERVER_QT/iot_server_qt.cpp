#include "iot_server_qt.h"

IoT_SERVER_QT::IoT_SERVER_QT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//获取IP地址并显示
	QString localHostName = QHostInfo::localHostName();
	QHostInfo info = QHostInfo::fromName(localHostName);
	QString ip;
	foreach(QHostAddress address, info.addresses())
	{
		if (address.protocol() == QAbstractSocket::IPv4Protocol)
			ip = address.toString();
	}
	//QString ip = QNetworkInterface::allAddresses().first().toString();
	ui.ipLineEdit->setText(ip);

	connect(ui.connectPushButton, &QPushButton::clicked, this, &IoT_SERVER_QT::startServer);

	ui.tableWidget->setColumnCount(2);
	ui.tableWidget->setHorizontalHeaderLabels(QStringList() << "ip" << "lightbutton");
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
	QString port = ui.portLineEdit->text();

	if (listenThread != NULL)
		qDebug() << listenThread->isRunning();

	//判断listenThread的状态
	if (listenThread == NULL || !listenThread->isRunning())
	{
		//服务器初始化
		listenThread = new ServerListenThread(ip, port);
		connect(this, SIGNAL(sendLightControl(QString, QString)), listenThread, SLOT(getSendLightData(QString, QString)));
		connect(listenThread, SIGNAL(showRecvData(QString, QString)), this, SLOT(recvData(QString, QString)));
		connect(listenThread, SIGNAL(showRecvIP(QString, bool)), this, SLOT(showClient(QString, bool)));
		listenThread->start();
		//修改按钮名称
		ui.connectPushButton->setText("Disconnect");
	}
	else
	{
		//停止线程运行
		listenThread->quit();
		delete listenThread;
		//修改按钮名称
		ui.connectPushButton->setText("Connect");
	}
}

/**
* @brief 显示从客户端收到的数据
* @param ip 收到数据的客户端ip
* @param data 收到的数据
*/
void IoT_SERVER_QT::recvData(QString ip, QString data) {
	QString recvText = "Receive from" + ip +": "+ data;
	ui.recvTextEdit->append(recvText);
}

/**
* @brief 显示或删除连入的IP地址
* @param ip 收到数据的客户端ip
* @param added 是删除还是连入
*/
void IoT_SERVER_QT::showClient(QString ip, bool added) {
	if (added == true)
	{
		int row = ui.tableWidget->rowCount();
		ui.tableWidget->insertRow(row);
		//显示连入客户端ip
		ui.tableWidget->setItem(row, 0, new QTableWidgetItem(ip));
		//在右侧动态创建light按钮
		QPushButton *lightbutton = new QPushButton(ui.tableWidget);
		lightbutton->setText("Light");
		ui.tableWidget->setCellWidget(row, 1, lightbutton);
		connect(lightbutton, SIGNAL(clicked()), this, SLOT(controlLight()));
	}
	else
	{
		//删除ip和按钮
		for (int i = 0; i < ui.tableWidget->rowCount(); i++)
		{
			QString currentIP = ui.tableWidget->item(i, 0)->text();
			if (currentIP == ip)
			{
				ui.tableWidget->removeRow(i);
			}
		}
	}
}

/**
* @brief 点击lightButton进行亮灯/灭灯操作
*/
void IoT_SERVER_QT::controlLight()
{
	QString ip;
	//判断是哪一行IP
	QPushButton *editButton = (QPushButton*)(sender());
	for (int i = 0; i < ui.tableWidget->rowCount(); i++)
	{
		QPushButton* editButtonIter = (QPushButton*)(ui.tableWidget->cellWidget(i, 1));
		if (editButton == editButtonIter)
		{
			ip = ui.tableWidget->item(i, 0)->text();
		}
	}
	//发出LIGHT信号
	emit sendLightControl(ip, "light");
}