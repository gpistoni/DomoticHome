#pragma once
#include "data.h"
#include <QThread>
#include "dhrequets.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QByteArray>
#include <QNetworkReply>
#include <QMessageBox>
#include <QEventLoop>
#include "data.h"

extern CData g_data;


//*************************************************************************************************************
class WorkerThread : public QThread
{
    Q_OBJECT

    QNetworkAccessManager * m_mgr;

public:
    WorkerThread()
    {
    }

    void run()
    {
        m_mgr = new QNetworkAccessManager( );
        msleep(1000);
        getDataLabels();

        while(1)
        {
            msleep(1000);
            getDataValues();
            getDataLabels();
            emit valueChanged();
        }
    }

    void getDataLabels()
    {
        //QByteArray arr = sendRequest(  QUrl(QString("http://127.0.0.1:9999/@label")) );
        QByteArray arr = sendRequest(  QUrl(QString("http://196.168.0.201/labels")) );

        QString str(arr);
        QStringList list = str.split(",", QString::SkipEmptyParts);

        for( int i=0; i<list.size(); i++ )
            g_data.SetS(i, list.at(i) );
    }

    void getDataValues()
    {
        //QByteArray arr = sendRequest(  QUrl(QString("http://127.0.0.1:9999/@value")) );
         QByteArray arr = sendRequest(  QUrl(QString("http://196.168.0.201/values")) );


        QString str(arr);
        QStringList list = str.split(",", QString::SkipEmptyParts);

        for( int i=0; i<list.size(); i++ )
            g_data.Set(i, list.at(i).toDouble() );
    }



    QByteArray sendRequest( QUrl url)
    {
        QByteArray ret;

        // create custom temporary event loop on stack
        QEventLoop eventLoop;

        // "quit()" the event-loop, when the network request "finished()"
        QNetworkAccessManager mgr;
        QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

        // the HTTP request
        QNetworkRequest req( url );
        QNetworkReply *reply = mgr.get(req);
        eventLoop.exec(); // blocks stack until "finished()" has been called

        if (reply->error() == QNetworkReply::NoError)
        {
            //success
            qDebug() <<  "Success: " << url;
            ret = reply->readAll();
            delete reply;

        }
        else {
            //failure
            qDebug() << "Failure: " << url;
            delete reply;
        }
        return ret;
    }


    // Define signal:
signals:
    void valueChanged();
};

