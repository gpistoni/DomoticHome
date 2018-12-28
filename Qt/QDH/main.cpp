#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QStringList arg = a.arguments();
    qDebug() << arg;

    bool RunPrograms = false;
    bool RunGui = false;

    if ( arg.indexOf("+s") > 0 )
        RunPrograms = true;
    if ( arg.indexOf("+g") >0 )
        RunGui = true;

    // Server
    QThread serverthread;
    Server server(RunPrograms);

    server.moveToThread(&serverthread);
    server.connect(&serverthread, SIGNAL(started()), &server, SLOT(run()));
    server.connect(&server, SIGNAL(finished()), &serverthread, SLOT(quit()));
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
    a.exec();

    server.Stop();
    return 0;
}
