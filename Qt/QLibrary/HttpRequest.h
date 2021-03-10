#ifndef HTTPREQUEST_H
#define HTTPREQUEST_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "DataTable.h"

class HttpRequest : public QObject
{
    Q_OBJECT
private:
    QNetworkAccessManager mAccessManager;
    DataTable *m_dr;

public:
    HttpRequest(DataTable *dr, QObject* parent = 0);

    void executeGet(QUrl url);   //url = "http://httpbin.org/ip"
    void executePost();
    void executeBlockingGet();

private slots:
    void replyFinished(QNetworkReply* reply);
    void replyReadyRead();
};

#endif // HTTPREQUEST_H
