#include "mainwindow.h"
#include <QApplication>

#ifdef USE_GUI

int main(int argc, char *argv[])
{
    QApplication aGui(argc, argv);

    QStringList arg = aGui.arguments();
    qDebug() << arg;

    bool RunPrograms = false;

    if ( arg.indexOf("+s") > 0 )
        RunPrograms = true;

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

#else

int main(int argc, char *argv[])
{
    QCoreApplication aCore(argc, argv);

    QStringList arg = aCore.arguments();
    qDebug() << arg;

    bool RunPrograms = false;

    if ( arg.indexOf("+s") > 0 )
        RunPrograms = true;


    // Server
    QThread serverthread;
    Server server(RunPrograms);

    server.moveToThread(&serverthread);
    server.connect(&serverthread, SIGNAL(started()), &server, SLOT(run()));
    server.connect(&server, SIGNAL(finished()), &serverthread, SLOT(quit()));
    serverthread.start();

    aCore.exec();

    server.Stop();
    return 0;
}

#endif
