#pragma once
#include "../QLibrary/HttpClient.h"

#include "qdebug.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "DataVars.h"

class DataValues
{
   public:
    VarI progBoilerACS          = VarI( "PRG", "", "r0", "progBoilerACS" );
    VarI progSummerAC           = VarI( "PRG", "", "r1", "progSummerAC" );
    VarI progSummerAC_NIGHT     = VarI( "PRG", "", "r2", "progSummerAC_NIGHT" );
    VarI progWinterFIRE         = VarI( "PRG", "", "r3", "progWinterFIRE" );
    VarI progWinterPDC          = VarI( "PRG", "", "r4", "progWinterPDC" );
    VarI progWinterPDC_ALLROOMS = VarI( "PRG", "", "r5", "progWinterPDC_ALLROOMS" );
    VarI progWinterPDC_FOTOV    = VarI( "PRG", "", "r6", "progWinterPDC_FOTOV" );
    VarI progAllRooms           = VarI( "PRG", "", "r7", "progAllRooms" );
    VarI progExternalLight      = VarI( "PRG", "", "r8", "progExternalLight" );

    std::vector<VarI*>    progs = {&progBoilerACS,
                                   &progSummerAC,
                                   &progSummerAC_NIGHT,
                                   &progWinterFIRE,
                                   &progWinterPDC,
                                   &progWinterPDC_ALLROOMS,
                                   &progWinterPDC_FOTOV,
                                   &progAllRooms,
                                   &progExternalLight };

};

class DataTable: public DataValues
{    
public:
    QVariantMap m_map;

private:
    QString m_host;
    quint16 m_port;

public:
    DataTable( QString host, quint16 port  )
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
            QJsonDocument jsonDoc = QJsonDocument::fromJson(str.toUtf8());
            QJsonObject jsonRoot = jsonDoc.object();

            m_map = jsonRoot.toVariantMap();
            //****************************************
            UpdateVal( progBoilerACS );
        }
        catch(...)
        {
        }
    }

    QString PrintTree()
    {
        return ""; //   return m_jsonDoc.toJson( QJsonDocument::Indented );
    }

    QString GetValue(QString name1, QString name2)
    {
        QVariantMap vmap1 = qvariant_cast<QVariantMap>(m_map[name1]);
        QVariant vmap2 = vmap1[name2];
        return vmap2.toString();
    }

    double GetValueF(QString name1, QString name2)
    {
        QVariantMap vmap1 = qvariant_cast<QVariantMap>(m_map[name1]);
        QVariant vmap2 = vmap1[name2];
        return vmap2.toDouble();
    }

    int GetValueI(QString name1, QString name2)
    {
        QVariantMap vmap1 = qvariant_cast<QVariantMap>(m_map[name1]);
        QVariant vmap2 = vmap1[name2];
        return vmap2.toInt();
    }

    void SetValue(QString name1, QString name2, QString value)
    {
        QVariantMap vmap1 = qvariant_cast<QVariantMap>(m_map[name1]);
        vmap1[name2] = value;
        m_map[name1] = vmap1;
    }

    void SetValue(QString name1, QString name2, double value)
    {
        QVariantMap vmap1 = qvariant_cast<QVariantMap>(m_map[name1]);
        vmap1[name2] = value;
        m_map[name1] = vmap1;
    }

    void UpdateVal(VarI v)
    {
        v.m_value = GetValueI(v.m_t, v.m_v );
    }
};

