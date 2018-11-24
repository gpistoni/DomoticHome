#pragma once
#include "../QLibrary/HttpClient.h"

#include "qdebug.h"
#include "QJsonDocument"
#include "QJsonObject"

class DataReader
{
    QJsonDocument m_jsonDoc;

    QString m_host = "10.0.2.2";
    quint16 m_port = 8080;

public:
    DataReader( QString host, quint16 port  )
    {
        m_host = host;
        m_port = port;
    }

    void ReadData()
    {
        CQHttpClient client(m_host, m_port, 10000 );
        try
        {
            QString str = client.GetValue_Json();
            //****************************************
            m_jsonDoc = QJsonDocument::fromJson(str.toUtf8());
            QJsonObject jsonRoot = m_jsonDoc.object();

            QJsonObject jT1 = jsonRoot["T1"].toObject();
            QJsonValue v1 = jT1["name"];
            QJsonValue v2 = jT1["extra"];
            QJsonValue v3 = jT1["nonextra"];
            //****************************************
        }
        catch(...)
        {
        }
    }

    std::map<QString, QVariant> ToMap()
    {
        QJsonObject jsonRoot = m_jsonDoc.object();
        return jsonRoot.toVariantMap().toStdMap();
    }

    QString PrintTree()
    {
        return m_jsonDoc.toJson( QJsonDocument::Indented );
    }

    QJsonValue GetValue(QString terminal, QString name)
    {
        QJsonObject jsonRoot = m_jsonDoc.object();
        QJsonObject jT = jsonRoot[terminal].toObject();
        return jT[name];
    }
};

