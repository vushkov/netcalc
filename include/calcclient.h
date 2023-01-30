#pragma once

#include <QTcpSocket>
#include <QtWidgets>
#include "calcwidget.h"

class MyConnection : QObject
{
    Q_OBJECT

private:
    //QTcpSocket *socket;

public:
    MyConnection();

public slots:
    void startConnection();
    void sendData();
    void disconnectedState();
    void readyRead();
    void connectedState();

};
