#include "calcwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    // Строим интерфейс
    w.makeWidget();

    // Показываем главный виджет
    w.show();

    return a.exec();
}
