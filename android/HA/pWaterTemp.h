#ifndef PWATERTEMP_H
#define PWATERTEMP_H
#include <memory>

#include <QScrollArea>
#include <QLabel>
#include <QLCDNumber>
#include <QThread>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QEventLoop>
#include <QStringList>

namespace Ui {
class WaterTemp;
class WorkerThread;
}

//*************************************************************************************************************
class pWaterTempData
{
   public:
    std::vector<double> values;
};


//*************************************************************************************************************
class WorkerThread : public QThread
{
    Q_OBJECT
    void run()
    {
        while(1)
        {
            msleep(1000);
            pWaterTempData values =  sendRequest( );
            emit valueChanged( values );
        }
    }

    pWaterTempData sendRequest( )
    {
        pWaterTempData data;

        QString str;
         // create custom temporary event loop on stack
        QEventLoop eventLoop;

        // "quit()" the event-loop, when the network request "finished()"
        QNetworkAccessManager mgr;
        QObject::connect(&mgr, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));

        // the HTTP request
        QNetworkRequest req( QUrl( QString("http://www.google.it/") ) );
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
        }
        return data;
    }

    // Define signal:
signals:
    void valueChanged( pWaterTempData values );
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
};

#endif // PWATERTEMP_H
