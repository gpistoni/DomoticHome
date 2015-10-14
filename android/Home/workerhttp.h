#pragma once
#include <QThread>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QByteArray>
#include <QNetworkReply>
#include <QMessageBox>
#include <QEventLoop>
#include "../libraries/data.h"

//*************************************************************************************************************
class WorkerHTTP : public QThread
{
    Q_OBJECT

    QNetworkAccessManager * m_mgr;

public slots:
    void onParamChanged()
    {
        sendDataPars();
        requestDataValues();
    }

public:
    WorkerHTTP()
    {
         connect( gData, SIGNAL(sigParamChanged()), this, SLOT(onParamChanged()) );
    }

    void run()
    {
        m_mgr = new QNetworkAccessManager( );
        msleep(1000);
        requestDataLabels();
        requestDataLabelsPars();
        requestDataPars();
        emit gData->sigValueChanged();

        while(1)
        {
            requestDataValues();
            msleep(2500);
        }
    }

    void requestDataLabels()
    {
        QByteArray arr = sendRequest(  QUrl(QString("http://192.168.0.201/labels")) );

        QString str(arr);
        QStringList list = str.split(",", QString::SkipEmptyParts);

        for( int i=0; i<list.size(); i++ )
            gData->SetL( i, list.at(i) );
    }

    void requestDataValues()
    {
        QByteArray arr = sendRequest(  QUrl(QString("http://192.168.0.201/values")) );

        QString str(arr);
        QStringList list = str.split(",", QString::SkipEmptyParts);

        for( int i=0; i<list.size(); i++ )
            gData->_SetV( i, list.at(i) );
    }

    void requestDataPars()
    {
        QByteArray arr = sendRequest(  QUrl(QString("http://192.168.0.201/pars")) );

        QString str(arr);
        QStringList list = str.split(",", QString::SkipEmptyParts);

        for( int i=0; i<list.size(); i++ )
            gData->_SetVparam( i, list.at(i) );
    }

    void requestDataLabelsPars()
    {
        QByteArray arr = sendRequest(  QUrl(QString("http://192.168.0.201/labelspars")) );

        QString str(arr);
        QStringList list = str.split(",", QString::SkipEmptyParts);

        for( int i=0; i<list.size(); i++ )
            gData->SetLparam( i, list.at(i) );
    }

    void sendDataPars()
    {
        QByteArray arr = "http://192.168.0.201/setPars=";

        for( int i=0; i<100; i++ )
        {
            arr += gData->GetVparam(i);
            arr += ',';
        }

        sendRequest(  QUrl( arr ) );
    }

  private:
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
};

