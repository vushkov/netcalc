#include "calcwidget.h"
#include "ui_widget.h"

using namespace timestamp;

CalcWidget::CalcWidget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Находим количество дочерних элементов gridLayout
    int gridLayoutChild = ui->gridLayout->count();

    // Прикрепляем к каждой кнопке слот, который будет вставлять нужный символ
    for (int i = 0; i < gridLayoutChild; i++) {
        QPushButton *pButton = qobject_cast<QPushButton *>(ui->gridLayout->itemAt(i)->widget());

        // Исключаем кнопку "=" и кнопку "С"
        if (pButton->text() != 'C' && pButton->text() != '=') {
            connect(pButton, &QPushButton::clicked, [=]() { ui->resultLineEdit->insert(QString(pButton->text())); });
        }
    }

    // Определяем поведение остальных кнопок
    connect(ui->buttonConnect, SIGNAL(clicked()), SLOT(startConnection()));
    connect(ui->buttonClear, SIGNAL(clicked()), ui->resultLineEdit, SLOT(clear()));
}

CalcWidget::~CalcWidget()
{
    delete ui;
}

void CalcWidget::startConnection()
{
    // Создаем сокет
    QTcpSocket *newSocket = new QTcpSocket(this);

    // Извлекаем ip адрес и порт из соответствующих полей ввода
    QString ipLE = ui->ipLineEdit->text();
    int port = ui->portLineEdit->text().toInt();

    // Коннектимся к серверу
    newSocket->connectToHost(ipLE, port);

    // Определяем поведение, в случае получения от сокета сигнала "Подключен" - по сигналу запускаем метод connectionState()
    connect(newSocket, SIGNAL(connected()), SLOT(connectedState()));

    // Определяем поведение, в случае получения от сокета сигнала "Отключен" -  по сигналу запускаем метод disconnectedState()
    connect(newSocket, SIGNAL(disconnected()), SLOT(disconnectedState()));

    // Определяем поведение кнопки для отправки данных
    connect(ui->buttonEqual, &QPushButton::clicked, [=] { this->sendData(newSocket); });
}

void CalcWidget::connectedState()
{
    // Получаем сокет с использованием отправителя сигнала
    QTcpSocket *newSocket = (QTcpSocket *) sender();

    // Получаем ip адрес сервера
    QString ip = newSocket->peerName();

    // Готовим переменную для лога
    QString logString = getTimeStamp() + " > Connected to " + ip + "\n";

    // Пишел лог в интерфейс
    ui->logTextEdit->insertPlainText(logString);

    // Меняем текст и цвет текста статус-лейбла при успешном подключении
    ui->connectionStatus->setText("Connected");
    ui->connectionStatus->setStyleSheet("QLabel{color:green;}");

    // Меняем текст кнопки подключения
    ui->buttonConnect->setText("Disconnect");

    // Включаем поле результата и кнопку "="
    ui->resultLineEdit->setDisabled(false);
    ui->buttonEqual->setDisabled(false);

    // Переопределяем поведение кнопки подключения в связи с тем, что он сменила свою функцию (стала кнопкой Отключения)
    disconnect(ui->buttonConnect, SIGNAL(clicked()), this, SLOT(startConnection()));
    connect(ui->buttonConnect, SIGNAL(clicked()), newSocket, SLOT(deleteLater()));
}

void CalcWidget::sendData(QTcpSocket *newSocket)
{
    // Если поле ввода пустое, то вообще ничего не делаем
    if (ui->resultLineEdit->text() != "") {
        // Если сокет существует и статус сокета "Подключен", то отправляем это выражение на сервер
        if (newSocket && newSocket->state() == QAbstractSocket::ConnectedState) {
            // Получаем введенное пользователем выражение
            QString data = ui->resultLineEdit->text();

            // Добавляем к данным символ \n, чтобы обозначить конец данных
            QByteArray byteArrayData = data.toUtf8().append('\n');

            // Записываем выражение в сокет
            newSocket->write(byteArrayData);

            // Пишем в поле лога какое выражение было отправлено на сервер
            ui->logTextEdit->insertPlainText(getTimeStamp() + " > Sent data: " + data + "\n");

        } else {
            // Иначе пишем в поле лога ошибку
            ui->logTextEdit->insertPlainText(getTimeStamp() + " > Connection error: " + newSocket->errorString() + "\n");
        }

        // Определяем поведение при получения от сокета сигнала "готов к чтению" - запускаем соответствующий метод
        connect(newSocket, SIGNAL(readyRead()), SLOT(readyReadSlot()));
    }
}

void CalcWidget::readyReadSlot()
{
    // Получаем сокет с использованием отправителя сигнала
    QTcpSocket *socket = (QTcpSocket *) sender();

    // Вычитываем из сокета данные, полученные от сервера
    QString recievedData = socket->readAll();

    // Делаем проверку на пустые данные
    if (recievedData != "") {
        // Устанавливаем полученный результат в соответствующее поле
        ui->resultLineEdit->setText(recievedData);

        // Пишем лог
        QString logString = getTimeStamp() + " > Recieved result: " + recievedData + "\n";
        ui->logTextEdit->insertPlainText(logString);
    }
}

void CalcWidget::disconnectedState()
{
    // Получаем сокет с использованием отправителя сигнала
    QTcpSocket *newSocket = (QTcpSocket *) sender();

    // Получаем ip адрес сервера
    QString ip = newSocket->peerName();

    // Готовим переменную для лога
    QString logString = getTimeStamp() + " > Disconnected from " + ip + "\n";

    // Пишел лог в интерфейс
    ui->logTextEdit->insertPlainText(logString);

    // Меняем текст и цвет текста статус-лейбла при успешном отключении
    ui->connectionStatus->setText("Disconnected");
    ui->connectionStatus->setStyleSheet("QLabel{color:red;}");

    // Меняем текст кнопки подключения
    ui->buttonConnect->setText("Connect");

    // Выключаем поле результата вычислений и кнопку "="
    ui->buttonEqual->setDisabled(true);
    ui->resultLineEdit->setDisabled(true);
    ui->resultLineEdit->setText("");

    // Вновь переопределяем поведение по нажатию кнопки подключения
    disconnect(ui->buttonConnect, SIGNAL(clicked()), newSocket, SLOT(deleteLater()));
    connect(ui->buttonConnect, SIGNAL(clicked()), SLOT(startConnection()));
}
