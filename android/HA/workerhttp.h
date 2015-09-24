#pragma once
#include "data.h"
#include <QThread>
#include "dhrequets.h"


//*************************************************************************************************************
class WorkerThread : public QThread
{
    Q_OBJECT

public:
    WorkerThread()
    {
       getDataLabels();
    }

    void run()
    {
        while(1)
        {
            msleep(1000);
            getDataValues();
            emit valueChanged();
            emit valueCh();
        }
    }

    void getDataLabels()
    {
    }

    void getDataValues()
    {
       QString str = DHRequets::sendRequest(  QUrl(QString("http://127.0.0.1/")) );

       QStringList list = str.split(".", QString::SkipEmptyParts);
      // data.values["val0"] = list[0].toDouble();

      // return data;


 //      DHRequets::sendRequest(  QUrl(QString("http://ip.jsontest.com/")) );

       /*

        QString str;
         // create custom temporary event loop on stack
        QEventLoop eventLoop;

        // "quit()" the event-loop, when the network request "finished()"
        QNetworkAccessManager mgr;
        QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

        // the HTTP request
        QNetworkRequest req( QUrl( QString("http://ip.jsontest.com/") ) );
        QNetworkReply *reply = mgr.get(req);
        eventLoop.exec();                       // blocks stack until "finished()" has been called

        if (reply->error() == QNetworkReply::NoError)
        {
            //success
            str = reply->readAll();
            qDebug() << str;

            QStringList list = str.split(".", QString::SkipEmptyParts);
            for ( auto sti : list)
            {
                data.values.push_back( sti.toDouble() );
            }
            delete reply;
        }
        else {
            //failure
            str = reply->errorString();
            qDebug() << str;
            delete reply;
        }*/
    }

    // Define signal:
signals:
    void valueChanged();
    void valueCh();
};

