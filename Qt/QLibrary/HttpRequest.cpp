#include "HttpRequest.h"
#include <QDebug>
#include <QUrlQuery>
#include <QEventLoop>
#include <QThread>
#include <QProgressDialog>
#include <unistd.h>

HttpRequest::HttpRequest(QObject* parent) :
    QObject(parent)
{
   //connect(&mAccessManager, &QNetworkAccessManager::finished, this, &HttpRequest::replyFinished);
}

void HttpRequest::executeGet(const QUrl &url)
{
    //url =             // "https://pistonihome.altervista.org/data/wattagerow.php?Prod=10&Cons=5010&L1=10&L2=20&L3=30";

//    if ( QThread::currentThread()!= this->thread())  qDebug()<<"ERR";
//    reply = mAccessManager.get(QNetworkRequest(url));

    //connect(reply, &QNetworkReply::finished, this, &HttpRequest::httpFinished);
    //connect(reply, &QIODevice::readyRead, this, &HttpRequest::httpReadyRead);
    qDebug()<<"";
    qDebug()<<url;

    mAccessManager = new QNetworkAccessManager();
    connect(mAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT( replyFinished(QNetworkReply*) ));
    reply = mAccessManager->get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::finished, this, &HttpRequest::httpFinished);
    connect(reply, &QIODevice::readyRead, this, &HttpRequest::httpReadyRead);
    sleep(1);
    qDebug() << " GET result:" << reply->readAll();
    reply->deleteLater();
}

void HttpRequest::httpFinished()
{
     qDebug()<<"httpFinished";

    if (reply->error())
    {
        reply->deleteLater();
        reply = nullptr;
        return;
    }

    reply->deleteLater();
    reply = nullptr;
}

void HttpRequest::httpReadyRead()
{
    // this slot gets called every time the QNetworkReply has new data.
    // We read all of its new data and write it into the file.
    // That way we use less RAM than when reading it at the finished()
    // signal of the QNetworkReply
    qDebug()<< "Test" << QString(reply->readAll());
}


void HttpRequest::executePost()
{
//    QNetworkRequest request(QUrl("http://httpbin.org/post"));
//    request.setHeader(QNetworkRequest::ContentTypeHeader,
//                      "application/x-www-form-urlencoded");
//    QUrlQuery urlQuery;
//    urlQuery.addQueryItem("book", "Mastering Qt 5");

//    QUrl params;
//    params.setQuery(urlQuery);

//    QNetworkReply* reply = mAccessManager.post(request, params.toEncoded());
//    connect(reply, &QNetworkReply::readyRead, [reply] ()
//    {
//        qDebug() << "Ready to read from reply";
//    });
//    connect(reply, &QNetworkReply::sslErrors, [this] (QList<QSslError> errors)
//    {
//        qWarning() << "SSL errors" << errors;
//    });
}

void HttpRequest::executeBlockingGet()
{
    QNetworkAccessManager localManager;
    QEventLoop eventLoop;
    QObject::connect(&localManager, &QNetworkAccessManager::finished,
                     &eventLoop, &QEventLoop::quit);

    QNetworkRequest request(QUrl("http://httpbin.org/user-agent"));
    request.setHeader(QNetworkRequest::UserAgentHeader, "MasteringQt5Browser 1.0");

    QNetworkReply* reply = localManager.get(request);
    eventLoop.exec();

    qDebug() << "Blocking GET result:" << reply->readAll();
    reply->deleteLater();
}

void HttpRequest::replyFinished(QNetworkReply* reply)
{
    int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "Reponse network error" << reply->error();
    qDebug() << "Reponse HTTP status code" << statusCode;
    qDebug() << "Reply content:" << reply->readAll();

    {
        if (reply->error())
        {
            QString err = reply->errorString();
            qDebug() << err;
            //m_dr->LogMessage(err);
        }

        QString answer = reply->readAll();
           qDebug() << answer;
        //m_dr->LogMessage(answer);
    }

    reply->deleteLater();
}

void HttpRequest::replyReadyRead()
{

}

