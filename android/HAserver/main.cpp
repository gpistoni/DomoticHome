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
#include <QPixmap>
#include <QScreen>
#include <QtGui>

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
            if (line.contains("@val"))
            {
                writeLine( client, QString("HTTP/1.1 200 OK\r\nContent-Type: text/html \r\n\r\n") );
                for (int i=0; i<10; i++)
                {
                    for (int j=0; j<10; j++)
                    {
                        if (j!=0)  writeLine( client, ",");
                        writeLine( client, QString::number(i*10+j) );
                    }
                }
            }
            else if (line.contains("@labels"))
            {
                writeLine( client, QString("HTTP/1.1 200 OK\r\nContent-Type: text/html \r\n\r\n") );
                for (int i=0; i<10; i++)
                {
                    for (int j=0; j<10; j++)
                    {
                        if (j!=0)  writeLine( client, ",");
                        writeLine( client, "lab_" + QString::number(i*10+j) );
                    }
                }
            }
            else if (line.contains("@img"))
            {
                //win
                //QPixmap pm( QPixmap::grabWidget( this ) );
                //pm.save("\\screen.png");

                QFile transferedFile("\\screen.png");
                transferedFile.open(QIODevice::ReadOnly);

                writeLine( client, QString("HTTP/1.1 200 OK\r\nContent-Type: image/png \r\n\r\n") );
                QByteArray block = transferedFile.readAll();
                client->write(block);
                writeLine( client, QDateTime::currentDateTime().toString() );

                // screenshot
                QScreen *QSCREEN = QGuiApplication::primaryScreen();
                QPixmap qpix = QSCREEN->grabWindow( 0, 0, 0, QSCREEN->size().width(), QSCREEN->size().height() );
                qpix.save("\\screen.png");
            }
            else if (line.contains("@live"))
            {
                writeLine( client, QString("HTTP/1.1 200 OK\r\nContent-Type: text/html \r\n\r\n") );
                writeLine( client, QString("<html>" "\r\n"
                                           "<head>""\r\n"
                                           "\r\n"
                                           "<script src='http://code.jquery.com/jquery-latest.js'></script>"
                                           "<script>""\r\n"
                                           "$(document).ready(function(){""\r\n"
                                           "     setInterval(timedRefresh, 1000);""\r\n"
                                           " });""\r\n"
                                           "function timedRefresh(timeoutPeriod) {""\r\n"
                                           "var d = new Date();""\r\n"
                                           "$('img').attr('src', $('img').attr('src') + '?_=' + d.getMilliseconds());""\r\n"
                                           "}""\r\n"
                                           "</script>""\r\n"
                                           "\r\n"
                                           "</head>""\r\n""\r\n"
                                           "<body onload='JavaScript:timedRefresh(1000);'>""\r\n"
                                           "<img src='/@img' alt='connection Error' />""\r\n"
                                           "</body>""\r\n"
                                           "</html>""\r\n"
                                           ));
            }
            else
            {
                writeLine( client, QDateTime::currentDateTime().toString() );
            }

        }
    }
};




int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qDebug() << "Primary screen:" << QGuiApplication::primaryScreen()->name();

    const QString IP =  "127.0.0.1";
    //const QString IP =  "192.168.56.1";
    const ushort port = 9999;

    myServer server(IP, port );
    server.startThread();

    QWindow window;
    window.show();

    return app.exec();
}
