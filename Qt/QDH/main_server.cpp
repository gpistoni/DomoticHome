#include <QApplication>
#include "watchdog.h"
#include "server.h"
#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication aCore(argc, argv);

    std::cerr << "Start SERVER "<< SERVER_VER << std::endl;

    /*
    QNetworkAccessManager qnam;
    QUrl url( "https://pistonihome.altervista.org/data/wattagerow.php?Prod=100&Cons=5010&L1=10&L2=20&L3=30");
    qnam.get(QNetworkRequest(url));
    */

    //HttpRequest pHttpRequest;
    //pHttpRequest = std::make_shared<HttpRequest>();
    //m_pHttpRequest->executeGet(url);

    // Primo giro a vuoto
    QUrl url( "http://pistonihome.altervista.org/data/set.php");
    HttpRequest request;
    request.executeGet(url);

    QThread::sleep(1);
    std::cerr << "Start WATCHDOG "<< std::endl;

    // Watchdog -------------------------------------------------------------
    Watchdog watchdog;

    QObject::connect(&watchdog, &QTimer::timeout, &watchdog, &Watchdog::run);
    //watchdog.connect(&watchdogthread, SIGNAL(started()), &watchdog, SLOT(run()));
    watchdog.start();

    QThread::sleep(1);
    std::cerr << "Start SERVER "<< std::endl;

    // Server -------------------------------------------------------------
    QThread serverthread;
    ServerDH server(true);

    server.moveToThread(&serverthread);
    server.connect(&serverthread, SIGNAL(started()), &server, SLOT(run()));
    server.connect(&server, SIGNAL(finished()), &serverthread, SLOT(quit()));
    server.connect(&server, SIGNAL(tickWatchdog()), &watchdog, SLOT(tick()));
    //QObject::connect(&server, &ServerDH::tickWatchdog, &watchdog, &Watchdog::tick);
    serverthread.start();

    aCore.exec();

    server.Stop();
    return 0;
}
