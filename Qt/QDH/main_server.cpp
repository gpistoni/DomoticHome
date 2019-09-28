#include <QApplication>
#include "server.h"
#include <QThread>


int main(int argc, char *argv[])
{
    QCoreApplication aCore(argc, argv);

    std::cerr << "Start SERVER"<< std::endl;

    // Server
    QThread serverthread;
    Server server(true);

    server.moveToThread(&serverthread);
    server.connect(&serverthread, SIGNAL(started()), &server, SLOT(run()));
    server.connect(&server, SIGNAL(finished()), &serverthread, SLOT(quit()));
    serverthread.start();

    aCore.exec();

    server.Stop();
    return 0;
}
