#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class HttpRequest : public QObject
{
    Q_OBJECT

private:
    static QNetworkAccessManager mAccessManager;
public:
    HttpRequest(QObject* parent = 0);

    QString executeGet(const QUrl &requestedUrl);
    void executePost();
    QString executeBlockingGet(const QUrl &requestedUrl);

//private slots:
//    void replyFinished(QNetworkReply* reply);
//    void replyReadyRead();

//    void httpFinished();
//    void httpReadyRead();

};

#endif // HTTPREQUEST_H
