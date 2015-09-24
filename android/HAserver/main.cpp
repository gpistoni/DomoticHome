/**
   This is a model for threaded client/server communication using the Qt QtNetwork class library.

   A threaded server is created that waits for a client connection.  When the client
   connects, the client sends a string (terminated by a \r) to the server.  The server
   reads the string and echos it back to the client.  The client then prints out the string.
*/

#include "lib/SocketThreadBase.h"
#include "QDateTime"
#include <QImage>
#include <QBuffer>
#include <QImageWriter>
#include <QFile>

class myServer: public GenericServer
{
public:
    myServer( const QString &ipAddr, const ushort port ):
        GenericServer( ipAddr, port )
    {

    };

    void Reply(QTcpSocket *client )
    {
        QString line;
        line = readLine( client );
        if (line.length() > 0)
        {
            if (line.contains("@data"))
            {
                for (int i=0; i<10; i++)
                {
                    if (i!=0)  writeLine( client, "\n");
                    for (int j=0; j<10; j++)
                    {
                        if (j!=0)  writeLine( client, ",");
                        writeLine( client, QString::number(i*10+j) );
                    }
                }
            }
            else if (line.contains("@labels"))
            {
                for (int i=0; i<10; i++)
                {
                    if (i!=0)  writeLine( client, "\n");
                    for (int j=0; j<10; j++)
                    {
                        if (j!=0)  writeLine( client, ",");
                        writeLine( client, "lab_" + QString::number(i*10+j) );
                    }
                }
            }
            else if (line.contains("@img"))
            {
                QFile transferedFile("\\jump.png");
                transferedFile.open(QIODevice::ReadOnly);

                writeLine( client, QString("HTTP/1.1 200 OK\r\nContent-Type: image/png \r\n\r\n") );
                QByteArray block = transferedFile.readAll();
                client->write(block);
                writeLine( client, QDateTime::currentDateTime().toString() );
            }
            //else
            {
               writeLine( client, QDateTime::currentDateTime().toString() );
            }

        }
    }
};




int main(int argc, char *argv[])
{
    const QString IP =  "127.0.0.1";
    const ushort port = 9999;

    myServer server(IP, port );
    server.startThread();

    //EchoClient client(IP, port );
    //client.startThread();
    while (1) // ! client.isDone())
    {
        Sleep( 100 );
    }
    return 0;
}
