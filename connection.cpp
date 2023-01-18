#include "Connection.h"
#include <QtWidgets>

MyConnection::MyConnection(): QTcpSocket()
{
}

void MyConnection::startConnection(QLineEdit *ipLE, QLineEdit *portLE)
{
    QString ip = ipLE->text();
    int port = portLE->text().toInt();
    connectToHost(ip, port);
}

