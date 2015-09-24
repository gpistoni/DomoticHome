#include "mainwindow.h"
#include <QApplication>


CData g_data;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
