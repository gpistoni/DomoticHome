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

    VarF3SP tCucina                   = { "T1", "v0", "v8", "v16", -0.5, 21, "tCucina" };
    VarF3SP tSala                     = { "T1", "v1", "v9", "v17",  1.5, 23, "tSala" };
    VarF3SP tCameraS                  = { "T1", "v2", "v10", "v18", 1,   18, "tCameraS" };
    VarF3SP tCameraD                  = { "T1", "v3", "v11", "v19", 0.5, 18, "tCameraD" };
    VarF3SP tCameraM                  = { "T1", "v4", "v12", "v20", 1,   16, "tCameraM" };
    VarF3SP tBagno                    = { "T1", "v5", "v13", "v21", 2.5, 23, "tBagno" };

    std::vector<VarF3SP*>    temps = {  &tCucina,
                                        &tSala,
                                        &tCameraS,
                                        &tCameraD,
                                        &tCameraM,
                                        &tBagno
                                        };

    VarF3 wPowergrid            = { "T6", "v0", "v8", "v16", "PowerGrid" };
    VarF3 wProduced             = { "T6", "v1", "v9", "v17", "Produced" };
    VarF3 wL1                   = { "T6", "v2", "v10", "v18", "L1" };
    VarF3 wL2                   = { "T6", "v3", "v11", "v19", "L2" };
    VarF3 wL3                   = { "T6", "v4", "v12", "v20", "L3" };

    std::vector<VarF3*>    ampers = { &wPowergrid,
                                      &wProduced,
                                      &wL1,
                                      &wL2,
                                      &wL3
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
            for( VarF3SP *elem : temps )
            {
                UpdateVal( elem );
            }
            for( VarF3 *elem : ampers )
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

    float GetValueF(QString name1, QString name2)
    {
        QVariantMap vmap1 = qvariant_cast<QVariantMap>(m_map[name1]);
        QVariant vmap2 = vmap1[name2];
        return vmap2.toFloat();
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

    void UpdateVal(VarF3 *var)
    {
        var->m_value = GetValueF(var->m_t, var->m_v);
        var->m_value1 = GetValueF(var->m_t, var->m_v1);
        var->m_value2 = GetValueF(var->m_t, var->m_v2);
     }

    void UpdateVal(VarF3SP *var)
    {
        var->m_value = GetValueF(var->m_t, var->m_v);
        var->m_value1 = GetValueF(var->m_t, var->m_v1);
        var->m_value2 = GetValueF(var->m_t, var->m_v2);
     }
};

