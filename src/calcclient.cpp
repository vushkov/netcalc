#include "calcclient.h"
#include "calcwidget.h"
#include "timestamp.h"
#include <QTcpSocket>
#include <QtWidgets>

QTcpSocket *newSocket;
QString ip;

MyConnection::MyConnection() {}

void MyConnection::startConnection()
{
    // Проверка есть ли уже созданный сокет или сокет есть, но он не подключен
    if (!newSocket || (newSocket && newSocket->state() != QAbstractSocket::ConnectedState)) {
        // Извлекаем ip адрес и порт из соответствующих полей ввода
        ip = ipLineEdit->text();
        int port = portLineEdit->text().toInt();

        // Создаем сокет и коннектимся к серверу
        newSocket = new QTcpSocket;
        newSocket->connectToHost(ip, port);

        // Определяем поведение, в случае получения от сокета сигнала "Подключен" - по сигналу запускаем метод connectionState()
        QObject::connect(newSocket, &QTcpSocket::connected, [=] { this->connectedState(); });

        // Определяем поведение, в случае получения от сокета сигнала "Отключен" -  по сигналу запускаем метод disconnectedState()
        QObject::connect(newSocket, &QTcpSocket::disconnected, [=] { this->disconnectedState(); });
    }
}

void MyConnection::connectedState()
{
    // Готовим переменную для лога
    QString logString = getTimeStamp() + " > Connected to " + ip + "\n";

    // Пишел лог в интерфейс
    logTextEdit->insertPlainText(logString);

    // Меняем текст и цвет текста статус-лейбла при успешном подключении
    connectionStatus->setText("Connected");
    connectionStatus->setStyleSheet("QLabel{color:green;}");

    // Меняем текст кнопки подключения
    buttonConnect->setText("Disconnect");

    // Включаем поле результата и кнопку "="
    resultLineEdit->setDisabled(false);
    buttonEqual->setDisabled(false);

    // Переопределяем поведение кнопки подключения в связи с тем, что он сменила свою функцию (стала кнопкой Отключения)
    QObject::connect(buttonConnect, &QPushButton::clicked, [=] { newSocket->~QTcpSocket(); });
}

void MyConnection::sendData()
{

    // logTextEdit->setText("");

     // Если поле ввода пустое, то вообще ничего не делаем
    if (resultLineEdit->text() != "") {
        // Если сокет существует и статус сокета "Подключен", то отправляем это выражение на сервер
        if (newSocket && newSocket->state() == QAbstractSocket::ConnectedState) {
            // Получаем введенное пользователем выражение
            QString data = resultLineEdit->text();

            // Добавляем к данным символ \n, чтобы обозначить конец данных
            QByteArray byteArrayData = data.toUtf8().append('\n');

            // Записываем выражение в сокет
            newSocket->write(byteArrayData);

            // Пишем в поле лога какое выражение было отправлено на сервер
            logTextEdit->insertPlainText(getTimeStamp() + " > Sent data: " + data + "\n");

        } else {
            // Иначе пишем в поле лога ошибку
            logTextEdit->insertPlainText(getTimeStamp() + " > Connection error: " + newSocket->errorString() + "\n");
        }

        // Определяем поведение при получения от сокета сигнала "готов к чтению" - запускаем соответствующий метод
        QObject::connect(newSocket, &QTcpSocket::readyRead, [=] { this->readyRead(); });
    }

}

void MyConnection::readyRead()
{
    // Вычитываем из сокета данные, полученные от сервера
    QString recievedData = newSocket->readAll();

    // Делаем проверку на пустые данные
    if (recievedData != "") {
        // Устанавливаем полученный результат в соответствующее поле
        resultLineEdit->setText(recievedData);

        // Пишем лог
        QString logString = getTimeStamp() + " > Recieved result: " + recievedData + "\n";
        logTextEdit->insertPlainText(logString);
    }
}

void MyConnection::disconnectedState()
{
    // Готовим переменную для лога
    QString logString = getTimeStamp() + " > Disconnected from " + ip + "\n";

    // Пишел лог в интерфейс
    logTextEdit->insertPlainText(logString);

    // Меняем текст и цвет текста статус-лейбла при успешном подключении
    connectionStatus->setText("Disconnected");
    connectionStatus->setStyleSheet("QLabel{color:red;}");

    // Меняем текст кнопки подключения
    buttonConnect->setText("Connect");

    // Выключаем поле результата вычислений и кнопку "="
    buttonEqual->setDisabled(true);
    resultLineEdit->setDisabled(true);
    resultLineEdit->setText("");

    // Вновь переопределяем поведение по нажатию кнопки подключения
    QObject::connect(buttonConnect, &QPushButton::clicked, [=] { this->startConnection(); });
}
