#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(time(0));
    MainWindow w;
    w.setFixedSize(440, 460);
    w.show();
    return a.exec();
}
