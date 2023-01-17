#pragma once

#include <QTcpSocket>
#include <QtWidgets>

class MyConnection : public QTcpSocket {
    Q_OBJECT

public:
    MyConnection();

public slots:
    void startConnection(QLineEdit *ipLE, QLineEdit *portLE);
};
