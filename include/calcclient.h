#pragma once

#include <QTcpSocket>
#include <QtWidgets>
#include "calcwidget.h"

class MyConnection : QObject
{
    Q_OBJECT

public:
    MyConnection();

public slots:
    void startConnection();
    void sendData();
    void disconnectedState();
    void readyRead();
    void connectedState();

};
