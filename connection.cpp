#include "connection.h"
#include "timestamp.h"
#include <QTcpSocket>
#include <QtWidgets>

QTcpSocket *newSocket;
QLabel *statusLabel;
QTextEdit *logTextEdit;
QString ip;

MyConnection::MyConnection() {}

void MyConnection::startConnection(QLineEdit *ipLE,
                                   QLineEdit *portLE,
                                   QLabel *connectionStatus,
                                   QTextEdit *logTE)
{
    // Проверка есть ли уже созданный сокет
    if (!newSocket) {
        // Получаем статус-лейбл из виджета
        statusLabel = connectionStatus;

        // Получаем поле для отображения лога калькулятора
        logTextEdit = logTE;

        // Извлекаем ip адрес и порт из соответствующих полей ввода
        ip = ipLE->text();
        int port = portLE->text().toInt();

        // Создаем сокет и коннектимся к серверу
        newSocket = new QTcpSocket;
        newSocket->connectToHost(ip, port);

        // Если соединение успешно установлено, то сокет отправляет сигнал, по сигналу запускаем метод connectionState()
        QObject::connect(newSocket, &QTcpSocket::connected, [=] { this->connectionState(); });
    }
}

void MyConnection::connectionState()
{
    // Готовим переменную для лога
    QString logString = getTimeStamp() + " > Connected to " + ip + "\n";

    // Пишем лог в консоль
    QTextStream(stdout) << logString;

    // Пишел лог в интерфейс
    logTextEdit->insertPlainText(logString);

    // Меняем текст и цвет текста статус-лейбла при успешном подключении
    statusLabel->setText("Connected");
    statusLabel->setStyleSheet("QLabel{color:green;}");
};
