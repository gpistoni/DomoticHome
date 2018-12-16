#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList arg = a.arguments();
    qDebug() << arg;

    bool RunServer = false;
    bool RunGui = false;

    if ( arg.indexOf("+s") > 0 )
        RunServer = true;
    if ( arg.indexOf("+g") >0 )
        RunGui = true;

    // Server
    QThread serverthread;
    Server server(RunServer);

    server.moveToThread(&serverthread);
    server.connect(&serverthread, SIGNAL(started()), &server, SLOT(run()));
    server.connect(&server, SIGNAL(finished()), &serverthread, SLOT(quit()));
    server.connect(&server, SIGNAL(finished()), &server, SLOT(deleteLater()));
    server.connect(&serverthread, SIGNAL(finished()), &serverthread, SLOT(deleteLater()));
    serverthread.start();

    MainWindow *main = nullptr;

    if (RunGui)
    {
        try
        {
            main = new MainWindow( &server );
            main->show();
        }
        catch (std::exception &e )
        {
            qDebug() << e.what();
        }
    }

    return a.exec();
}
