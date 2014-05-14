#include "vkstartwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    vkStartWindow w;
    w.show();

    return a.exec();
}
