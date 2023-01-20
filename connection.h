#pragma once

#include <QTcpSocket>
#include <QtWidgets>

class MyConnection : QObject
{
    Q_OBJECT

public:
    MyConnection();

public slots:
    void startConnection(QLineEdit *ipLE,
                         QLineEdit *portLE,
                         QLabel *connectionStatus,
                         QTextEdit *log);
    void connectionState();
    void sendData(QLineEdit *result);
    void readyRead(QLineEdit *result);
};
