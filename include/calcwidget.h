#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include "timestamp.h"
#include <QTcpSocket>
#include <QWidget>

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

private slots:
    void startConnection();
    void connectedState();
    void sendData();
    void readyRead();
    void disconnectedState();

private:
    QString ip;
    QTcpSocket *newSocket;

public:
    Ui::Widget *ui;
};

#endif // CALCWIDGET_H
