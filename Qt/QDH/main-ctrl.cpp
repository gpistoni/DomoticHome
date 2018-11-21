#include "DataReader.h"
#include "../QLibrary/QHttpServer.h"
#include <QCoreApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //HTTP server
    CQHttpServer webserver(8008, true);

    //DATA_READER_STORAGE
    DataReader DR("10.0.2.2", 8080);
    DR.ReadData();

    qDebug() << "PROVA: " << DR.GetValue("T1", "name").toString();
    qDebug() << DR.PrintTree();

    std::map< QString, QVariant>  map = DR.ToMap();
    for(auto v: map)
    {
        qDebug() << v.first << v.second;
    }

    webserver.startServer();
    return a.exec();
}
