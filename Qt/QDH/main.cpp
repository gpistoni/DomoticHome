#include "mainwindow.h"
#include <QApplication>
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication aGui(argc, argv);

    QStringList arg = aGui.arguments();
    qDebug() << arg;

    bool RunPrograms = false;

    // Server
    QThread serverthread;
    Server server(RunPrograms);

    server.moveToThread(&serverthread);
    server.connect(&serverthread, SIGNAL(started()), &server, SLOT(run()));
    server.connect(&server, SIGNAL(finished()), &serverthread, SLOT(quit()));
    serverthread.start();

    try
    {
        MainWindow *main = nullptr;
        main = new MainWindow( &server );
        main->show();
    }
    catch (std::exception &e )
    {
        qDebug() << e.what();
    }

    aGui.exec();

    server.Stop();
    return 0;
}
