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
    // create custom temporary event loop on stack
    QEventLoop eventLoop;

    // "quit()" the event-loop, when the network request "finished()"
    QNetworkAccessManager mgr;
    QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

    // the HTTP request
    QNetworkRequest req( url );


    QNetworkReply *reply = mgr.get( req );
    eventLoop.exec();                       // blocks stack until "finished()" has been called

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
