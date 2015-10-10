#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    CData::init();

    QApplication a(argc, argv);

    Q_INIT_RESOURCE(icons);

    MainWindow w;
    w.show();

    return a.exec();
}
