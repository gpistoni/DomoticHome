#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    CData::init();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
