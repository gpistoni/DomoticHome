#include "dhrequets.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>
#include <QUrl>
#include <QUrlQuery>


DHRequets::DHRequets()
{

}

QString DHRequets::sendRequest( QUrl url )
{
    /*
    QTcpSocket socket;
    QHostAddress hostAddr( mIP );
    socket.connectToHost( hostAddr, mPort );
    if (socket.waitForConnected( CONNECT_TIME_OUT ))
    {
        QHostAddress hostAddr = socket.localAddress();
        QString addr = "";
        if (hostAddr != QHostAddress::Null)
        {
            addr = hostAddr.toString();
        }
        printf("Client connected");
        if (addr.length() > 0)
        {
            qDebug() << QString(" on address %s:%04d").arg( addr.toLatin1().data(), socket.localPort() );
        }
        printf("\n");
        int ix = 0;
        while (socket.state() == QAbstractSocket::ConnectedState && ix < mNumStrings)
        {
            QString line( mStrings[ix] );
            writeLine(&socket, line);
            QString echoedLine = readLine( &socket );
            if (echoedLine.length() > 0) {
                if (line != echoedLine)
                {
                    qDebug() << "line and echoed line doesn't match\n";
                }
                else
                {
                    qDebug() << QString("%s\n").arg( line.toLatin1().data() );
                }
            }
            ix++;
        } // while
    }
    else {
        qDebug() << "Client socket failed to connect\n";
    }
    setDone( true );
    */
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( url );

    QNetworkReply *reply = mgr.get( req );
    eventLoop.exec();                                // blocks stack until "finished()" has been called

    QString str;
    if (reply->error() == QNetworkReply::NoError)
    {
        //success
        str = reply->readAll();
        qDebug() << str;

        /*QStringList list = str.split(".", QString::SkipEmptyParts);
        for ( auto sti : list)
        {
            data.values.push_back( sti.toDouble() );
        }
        delete reply;*/
    }
    else {
        //failure
        str = reply->errorString();
        qDebug() << str;
        delete reply;
    }
    return str;
}
