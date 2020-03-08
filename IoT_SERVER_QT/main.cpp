#include "iot_server_qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	IoT_SERVER_QT w;
	w.show();
	return a.exec();
}
