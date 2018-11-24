#include "../QLibrary/DataTable.h"
#include "../QLibrary/HttpServer.h"
#include <QCoreApplication>
#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //HTTP server
   // CQHttpServer webserver(8080, true);

    //In questo punto apro la comunicazione
    DataTable DR("192.168.1.200", 80);
    DR.ReadData();

    qDebug() << "PROVA: " << DR.GetValue("T1", "Name").toString();
    //std::puts(  DR.PrintTree().toStdString().c_str() );

   // std::map< QString, QVariant>  map = DR.ToMap();
   // for(auto v: map)
   // {
   //     qDebug() << v.first << v.second;
   // }

   // webserver.startServer();
    return a.exec();
}
