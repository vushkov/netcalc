#include "connection.h"
#include "timestamp.h"
#include <QTcpSocket>
#include <QtWidgets>

QTcpSocket *newSocket;
QLabel *statusLabel;
QTextEdit *logTextEdit;
QString ip;

MyConnection::MyConnection() {}

void MyConnection::startConnection(QLineEdit *ipLE, QLineEdit *portLE, QLabel *connectionSL, QTextEdit *logTE)
{
    // Проверка есть ли уже созданный сокет или сокет есть, но он не подключен
    if (!newSocket || (newSocket && newSocket->state() != QAbstractSocket::ConnectedState) ) {
        // Получаем статус-лейбл из виджета
        statusLabel = connectionSL;

        // Получаем поле для отображения лога калькулятора
        logTextEdit = logTE;

        // Извлекаем ip адрес и порт из соответствующих полей ввода
        ip = ipLE->text();
        int port = portLE->text().toInt();

        // Создаем сокет и коннектимся к серверу
        newSocket = new QTcpSocket;
        newSocket->connectToHost(ip, port);

        // Если соединение успешно установлено, то сокет отправляет сигнал, по сигналу запускаем метод connectionState()
        QObject::connect(newSocket, &QTcpSocket::connected, [=] { this->connectedState(); });
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
    statusLabel->setText("Connected");
    statusLabel->setStyleSheet("QLabel{color:green;}");
}

void MyConnection::sendData(QLineEdit *result)
{
    // Если сокет существует и пользователь ввел какое-либо выражение, то отправляем это выражение на сервер
    if (newSocket && result->text() != "") {
        // Получаем введенное пользователем выражение
        QString data = result->text();
        const char *charData = data.toStdString().c_str();

        // Определяем поведение в зависимости от статуса сокета
        if (newSocket->state() == QAbstractSocket::ConnectedState) {
            // Записываем выражение в сокет
            newSocket->write(charData);

            // Пишем в поле лога какое выражение было отправлено на сервер
            logTextEdit->insertPlainText(getTimeStamp() + " > Sent data: " + data + "\n");

        } else {
            // Иначе пишем в поле лога ошибку
            logTextEdit->insertPlainText(getTimeStamp() + " > Error: " + newSocket->errorString() + "\n");
        }

        // Если в сокете появляются данные, которые можно вычитать, запускаем соответствующий слоты
        QObject::connect(newSocket, &QTcpSocket::readyRead, [=] { this->readyRead(result); });
    }
}

void MyConnection::readyRead(QLineEdit *result)
{
    // Вычитываем из сокета данные, полученные от сервера
    QString recievedData = newSocket->readAll();

    // Делаем проверку на пустые данные
    if (recievedData != "") {
        // Устанавливаем полученный результат в соответствующее поле
        result->setText(recievedData);

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
    statusLabel->setText("Disconnected");
    statusLabel->setStyleSheet("QLabel{color:red;}");
}
