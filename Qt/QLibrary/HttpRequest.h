#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class HttpRequest : public QObject
{
    Q_OBJECT

private:
    QNetworkAccessManager *mAccessManager;
    QNetworkReply *reply;

public:
    HttpRequest(QObject* parent = 0);

    void executeGet(const QUrl &requestedUrl);
    void executePost();
    void executeBlockingGet();

private slots:
    void replyFinished(QNetworkReply* reply);
    void replyReadyRead();   

    void httpFinished();
    void httpReadyRead();

};

#endif // HTTPREQUEST_H
