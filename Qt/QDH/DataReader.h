#include "SQHttpClient.h"
#include "qdebug.h"
#include "QJsonDocument"
#include "QJsonObject"

class DataReader
{
    QJsonDocument m_jData;
    const QString m_host = "127.0.0.1";
    const quint16 m_port = 8080;

public:
    void ReadData()
    {
        CSQHttpClient::Setup(m_host, m_port, 10000 );
        try
        {
            QString str = CSQHttpClient::GetValue_Json();

            //****************************************
            m_jData = QJsonDocument::fromJson(str.toUtf8());
            QJsonObject jsonRoot = m_jData.object();

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

    QJsonValue GetValue(QString terminal, QString name)
    {
        QJsonObject jsonRoot = m_jData.object();
        QJsonObject jT = jsonRoot[terminal].toObject();
        return jT[name];
    }
};

