#ifndef IOT_SERVER_QT_H
#define IOT_SERVER_QT_H

#include <QtWidgets/QMainWindow>
#include "ui_iot_server_qt.h"

class IoT_SERVER_QT : public QMainWindow
{
	Q_OBJECT

public:
	IoT_SERVER_QT(QWidget *parent = 0);
	~IoT_SERVER_QT();

private:
	Ui::IoT_SERVER_QTClass ui;
};

#endif // IOT_SERVER_QT_H
