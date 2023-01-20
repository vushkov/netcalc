#include "widget.h"
#include "connection.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);
}

void Widget::makeWidget()
{
    // Устанавливаем заголовок окна калькулятора
    this->setWindowTitle("Calculator");

#define verticalLayoutGUIstart {
    // Общий вертикальный Layout
    QVBoxLayout *vertLayout = new QVBoxLayout();

    // Добавляем вертикальный Layout в корневой виджет
    this->setLayout(vertLayout);

#define verticalLayoutGUIend }

#define statusGUIstart {
    // Поле статуса соединения
    QLabel *connectionStatus = new QLabel();
    connectionStatus->setText("Disconnected");
    connectionStatus->setStyleSheet("QLabel{color:red;}");

    // Добавляем виджет статуса в общий вертикальный Layout
    vertLayout->addWidget(connectionStatus);

#define statusGUIend }

#define connectionGUIstart {
    // Горизонтальный Layout для полей ip и port
    QHBoxLayout *connectLayout = new QHBoxLayout();

    // Поля для ввода сетевых реквизитов, и кнопка для установки соединения
    QLineEdit *ipLineEdit = new QLineEdit();
    ipLineEdit->setText("172.27.10.95");
    QLineEdit *portLineEdit = new QLineEdit();
    portLineEdit->setText("12345");
    QPushButton *buttonConnect = new QPushButton("Connect");

    // Добавляем поля сетевых реквизитов и кнопку в соответствующий Layout
    connectLayout->addWidget(ipLineEdit);
    connectLayout->addWidget(portLineEdit);
    connectLayout->addWidget(buttonConnect);

    // Добавляем Layout сетевых настроек в главный вертикальный Layout
    vertLayout->addLayout(connectLayout);

#define connectionGUIend }

#define resultGUIstart {
    // Поле для выведения результата вычисления
    QLineEdit *result = new QLineEdit;
    result->setReadOnly(true);

    // Добавляем поле результата в общий вертикальный Layout
    vertLayout->addWidget(result);

#define resultGUIend }

#define gridGUIstart {
    // Создаем табличный Layout для компоновки кнопок калькулятора
    QGridLayout *grid = new QGridLayout;

    // Создаем кнопки калькулятора
    QPushButton *button1 = new QPushButton("1");
    QPushButton *button2 = new QPushButton("2");
    QPushButton *button3 = new QPushButton("3");
    QPushButton *button4 = new QPushButton("4");
    QPushButton *button5 = new QPushButton("5");

    //MyPushButton *button5 = new MyPushButton('5');
    QPushButton *button6 = new QPushButton("6");
    QPushButton *button7 = new QPushButton("7");
    QPushButton *button8 = new QPushButton("8");
    QPushButton *button9 = new QPushButton("9");
    QPushButton *button0 = new QPushButton("0");
    QPushButton *buttonMinus = new QPushButton("-");
    QPushButton *buttonPlus = new QPushButton("+");
    QPushButton *buttonMult = new QPushButton("*");
    QPushButton *buttonDivid = new QPushButton("/");
    QPushButton *buttonEqual = new QPushButton("=");
    QPushButton *buttonClear = new QPushButton("C");

    // Добавляем кнопки в табличный Layout
    grid->addWidget(button1, 3, 0);
    grid->addWidget(button2, 3, 1);
    grid->addWidget(button3, 3, 2);
    grid->addWidget(button4, 2, 0);
    grid->addWidget(button5, 2, 1);
    grid->addWidget(button6, 2, 2);
    grid->addWidget(button7, 1, 0);
    grid->addWidget(button8, 1, 1);
    grid->addWidget(button9, 1, 2);
    grid->addWidget(button0, 4, 1);
    grid->addWidget(buttonDivid, 0, 3);
    grid->addWidget(buttonMult, 1, 3);
    grid->addWidget(buttonMinus, 2, 3);
    grid->addWidget(buttonPlus, 3, 3);
    grid->addWidget(buttonEqual, 4, 3);
    grid->addWidget(buttonClear, 0, 1);

    // Добавляем таблличный Layout в общий вертикальный Layout
    vertLayout->addLayout(grid);

#define gridGUIend }

#define logGUIstart {
    // Поле для получения лога от сервера
    QTextEdit *log = new QTextEdit;
    log->setReadOnly(true);

    // Добавляем поле лога в общий вертикальный Layout
    vertLayout->addWidget(log);

#define logGUIend }

#define socketStart {
    MyConnection *myConnObj = new MyConnection();

#define socketEnd }

#define connectSignalSlotStart {
    QObject::connect(buttonClear, SIGNAL(clicked()), result, SLOT(clear()));

    QObject::connect(button0, &QPushButton::clicked, [=] { result->insert(QString("0")); });
    QObject::connect(button1, &QPushButton::clicked, [=] { result->insert(QString("1")); });
    QObject::connect(button2, &QPushButton::clicked, [=] { result->insert(QString("2")); });
    QObject::connect(button3, &QPushButton::clicked, [=] { result->insert(QString("3")); });
    QObject::connect(button4, &QPushButton::clicked, [=] { result->insert(QString("4")); });
    QObject::connect(button5, &QPushButton::clicked, [=] { result->insert(QString("5")); });
    QObject::connect(button6, &QPushButton::clicked, [=] { result->insert(QString("6")); });
    QObject::connect(button7, &QPushButton::clicked, [=] { result->insert(QString("7")); });
    QObject::connect(button8, &QPushButton::clicked, [=] { result->insert(QString("8")); });
    QObject::connect(button9, &QPushButton::clicked, [=] { result->insert(QString("9")); });
    QObject::connect(buttonPlus, &QPushButton::clicked, [=] { result->insert(QString("+")); });
    QObject::connect(buttonMinus, &QPushButton::clicked, [=] { result->insert(QString("-")); });
    QObject::connect(buttonMult, &QPushButton::clicked, [=] { result->insert(QString("*")); });
    QObject::connect(buttonDivid, &QPushButton::clicked, [=] { result->insert(QString("/")); });
    QObject::connect(buttonEqual, &QPushButton::clicked, [=] { myConnObj->sendData(result); });

    // Подключаемся к серверу по нажатию кнопки
    QObject::connect(buttonConnect, &QPushButton::clicked, [=] {
        myConnObj->startConnection(ipLineEdit, portLineEdit, connectionStatus, log);
    });

    //    QObject::connect(buttonConnect, &QPushButton::clicked, [=]{
    //        connectionStatus->setText("Connected");
    //        connectionStatus->setStyleSheet("QLabel{color:green;}");
    //    });

#define connectSignalSlotEnd }
}

Widget::~Widget()
{
    delete ui;
}
