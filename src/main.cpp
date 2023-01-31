#include "calcwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CalcWidget calc;
    calc.show();
    return a.exec();
}
