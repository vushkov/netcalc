#pragma once

#include <QTcpSocket>
#include <QtWidgets>
#include "widget.h"

//QLineEdit *ipLineEdit;
//QLineEdit *portLineEdit;
//QLabel *connectionStatus;
//QLineEdit *resultLineEdit;
//QPushButton *buttonConnect;
//QTextEdit *logTextEdit;
//QPushButton *buttonEqual;

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
