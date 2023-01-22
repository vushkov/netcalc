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
    ipLineEdit->setText("127.0.0.1");

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
    QLineEdit *resultLineEdit = new QLineEdit;
    resultLineEdit->setReadOnly(true);

    // Добавляем поле результата в общий вертикальный Layout
    vertLayout->addWidget(resultLineEdit);

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
    QTextEdit *logTextEdit = new QTextEdit;
    logTextEdit->setReadOnly(true);

    // Добавляем поле лога в общий вертикальный Layout
    vertLayout->addWidget(logTextEdit);

#define logGUIend }

#define connectSignalSlotStart {
    QObject::connect(buttonClear, SIGNAL(clicked()), resultLineEdit, SLOT(clear()));

    QObject::connect(button0, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("0")); });
    QObject::connect(button1, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("1")); });
    QObject::connect(button2, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("2")); });
    QObject::connect(button3, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("3")); });
    QObject::connect(button4, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("4")); });
    QObject::connect(button5, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("5")); });
    QObject::connect(button6, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("6")); });
    QObject::connect(button7, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("7")); });
    QObject::connect(button8, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("8")); });
    QObject::connect(button9, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("9")); });
    QObject::connect(buttonPlus, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("+")); });
    QObject::connect(buttonMinus, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("-")); });
    QObject::connect(buttonMult, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("*")); });
    QObject::connect(buttonDivid, &QPushButton::clicked, [=] { resultLineEdit->insert(QString("/")); });

#define connectSignalSlotEnd }

#define connectStart {
    // Создаем объект класса MyConnection
    MyConnection *myConnObj = new MyConnection();

    // Подключаемся к серверу по нажатию кнопки
    QObject::connect(buttonConnect, &QPushButton::clicked, [=] { myConnObj->startConnection(ipLineEdit, portLineEdit, connectionStatus, logTextEdit); });

#define connectEnd }

#define sendDataStart {
    // Отправляем выражение на сервер
    QObject::connect(buttonEqual, &QPushButton::clicked, [=] { myConnObj->sendData(resultLineEdit); });

#define sendDataEnd }
}

Widget::~Widget()
{
    delete ui;
}
