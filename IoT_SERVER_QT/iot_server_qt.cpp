#include "iot_server_qt.h"

IoT_SERVER_QT::IoT_SERVER_QT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	//��ȡIP��ַ����ʾ
	QString ip = QNetworkInterface().allAddresses().at(0).toString();
	ui.ipLineEdit->setText(ip);

	connect(ui.connectPushButton, QPushButton::clicked, this, startServer);
}

IoT_SERVER_QT::~IoT_SERVER_QT()
{

}

/**
* @brief ���������������տͻ�������
*/
void IoT_SERVER_QT::startServer()
{
	//��ȡip�Ͷ˿�
	QString ip = ui.ipLineEdit->text();
	QString port = ui.ipLineEdit->text();

	//�ж�listenThread��״̬
	if (listenThread == NULL || !listenThread->isRunning())
	{
		//��������ʼ��

		//�޸İ�ť����
	}
	else
	{
		//ֹͣ�߳�����

		//�޸İ�ť����
	}

	

	
}