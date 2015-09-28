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
        getDataLabels();
    }

    void run()
    {
        m_mgr = new QNetworkAccessManager( this );

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
        QByteArray arr = sendRequest(  QUrl(QString("http://127.0.0.1:9999/@value")) );

        QString str(arr);
        QStringList list = str.split(",", QString::SkipEmptyParts);

        for( int i=0; i<list.size(); i++ )
            g_data.Set(i, list.at(i).toDouble() );

        str ="";


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
            qDebug() << "Success" <<reply->readAll();
            ret = reply->readAll();
            delete reply;

        }
        else {
            //failure
            qDebug() << "Failure" <<reply->errorString();
            delete reply;
        }
        return ret;
    }


    // Define signal:
signals:
    void valueChanged();
    void valueCh();
};

