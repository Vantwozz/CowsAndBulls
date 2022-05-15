#include "widgetcows.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WidgetCows w;
    w.show();
    return a.exec();
}
