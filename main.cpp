#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowTitle("Сапёр");
    w.setFixedSize(440, 460);
    w.show();
    return a.exec();
}
