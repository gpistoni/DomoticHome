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
    //*****************************************************************************************

    VarI3 wProduced             = { "T6", "v0", "v8", "v16", "Produced" };
    VarI wInput                = { "T6", "v1", "", "wInput" };
    VarI wL1                   = { "T6", "v2", "", "wL1" };
    VarI wL2                   = { "T6", "v3", "", "wL2" };
    VarI wL3                   = { "T6", "v4", "", "wL3" };

    VarI kwhProduced           = { "T6", "v8", "", "kwhProduced" };
    VarI kwhInput              = { "T6", "v9", "", "kwhInput"};
    VarI kwhL1                 = { "T6", "v10", "", "kwhL1" };
    VarI kwhL2                 = { "T6", "v11", "", "kwhL2"};
    VarI kwhL3                 = { "T6", "v12", "", "kwhL3" };

    VarI hProduced             = { "T6", "v16", "", "hProduced" };
    VarI hInput                = { "T6", "v17", "", "hInput" };
    VarI hL1                   = { "T6", "v18", "", "hL1" };
    VarI hL2                   = { "T6", "v19", "", "hL2" };
    VarI hL3                   = { "T6", "v20", "", "hL3" };

    std::vector<VarI*>    ampers = { &wProduced,
                                     &kwhProduced,
                                     &hProduced,
                                     &wInput,
                                     &kwhInput,
                                     &hInput,
                                     &wL1,
                                     &kwhL1,
                                     &hL1,
                                     &wL2,
                                     &kwhL2,
                                     &hL2,
                                     &wL3,
                                     &kwhL3,
                                     &hL3
                                   };
    //*****************************************************************************************
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
            for( VarI *elem : progs )
            {
                UpdateVal( elem );
            }
            for( VarI *elem : ampers )
            {
                UpdateVal( elem );
            }
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

    void UpdateVal(VarI *var)
    {
        var->m_value = GetValueI(var->m_t, var->m_v);
    }
};

