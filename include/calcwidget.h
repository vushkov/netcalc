#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

extern QLineEdit *ipLineEdit;
extern QLineEdit *portLineEdit;
extern QLineEdit *resultLineEdit;
extern QLabel *connectionStatus;
extern QPushButton *buttonConnect;
extern QPushButton *buttonEqual;
extern QTextEdit *logTextEdit;

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void makeWidget();

public:
    Ui::Widget *ui;
};

#endif // CALCWIDGET_H