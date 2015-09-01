#ifndef PWATERTEMP_H
#define PWATERTEMP_H
#include <memory>

#include <QScrollArea>
#include <QLabel>
#include <QLCDNumber>
#include <QThread>
#include <QDebug>
#include <QStringList>

#include "dhrequets.h"

namespace Ui {
class WaterTemp;
class WorkerThread;
}

//*************************************************************************************************************
class pWaterTempData
{
public:
    std::map< QString, double> values;

public:
    pWaterTempData()
    {

    }

    pWaterTempData( const pWaterTempData &cp )
    {
        qDebug() << "Copy pWaterTempData" ;
        values = cp.values;
    }
};


//*************************************************************************************************************
class WorkerThread : public QThread
{
    pWaterTempData data;

    Q_OBJECT
    void run()
    {
        while(1)
        {
            msleep(1000);
            getWaterTemp( );
            emit valueChanged( data );
            emit valueCh();
        }
    }

    void getWaterTemp( )
    {
       QString res = DHRequets::sendRequest(  QUrl(QString("https://www.google.com")) );


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
    void valueChanged( pWaterTempData values );
    void valueCh();
};

//*************************************************************************************************************
class pWaterTemp : public QScrollArea
{
    Q_OBJECT

public:
    explicit pWaterTemp(QWidget *parent = 0);
    ~pWaterTemp();

private:
    std::vector<std::shared_ptr<QLabel>>        m_Labels;
    std::vector<std::shared_ptr<QLCDNumber>>    m_LcdNumber;

    Ui::WaterTemp *ui;

    // Worker Thread
    WorkerThread m_work;

public slots:
    void onValueChagned(pWaterTempData data);
    void onValueCh();

private slots:
    void on_pushUpdate_clicked();
};

#endif // PWATERTEMP_H
