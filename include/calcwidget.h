#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include "timestamp.h"
#include <QTcpSocket>
#include <QWidget>
#include <QString>
#include <QSignalMapper>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class CalcWidget : public QWidget
{
    Q_OBJECT

public:
    CalcWidget(QWidget *parent = nullptr);
    ~CalcWidget();

public slots:
    void startConnection();
    void sendData();
    void disconnectedState();
    void readyRead();
    void connectedState();

private:
    QString ip;
    //QTcpSocket *newSocket;

public:
    Ui::Widget *ui;
};

#endif // CALCWIDGET_H
