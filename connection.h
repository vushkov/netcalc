#pragma once

#include <QTcpSocket>
#include <QtWidgets>

class MyConnection : QObject
{
    Q_OBJECT

public:
    MyConnection();

public slots:
    void startConnection(QLineEdit *ipLE, QLineEdit *portLE, QLabel *connectionSL, QTextEdit *logTE);
    void sendData(QLineEdit *result);

private slots:
    void connectedState();
    void readyRead(QLineEdit *result);
    void disconnectedState();
};
