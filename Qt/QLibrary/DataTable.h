#pragma once
#include "../QLibrary/HttpClient.h"

#include <iostream>
#include "qdebug.h"
#include "QJsonDocument"
#include "QJsonObject"
#include "DataVars.h"
#include "QFile"


class DataValues
{
public:
    //*****************************************************************************************
    VarB progBoilerACS          = VarB( "T0", "r0", "pBoilerACS" );
    VarB progSummerAC           = VarB( "T0", "r1", "EstateAC" );
    VarB progWinterFIRE         = VarB( "T0", "r2", "InverinoCAMINO" );
    VarB progWinterPDC          = VarB( "T0", "r3", "InvernoPDC" );
    VarB progExternalLight      = VarB( "T0", "r4", "LuciEsterno" );

    VarB progAllRooms           = VarB( "T0", "r7", "TutteLeStanze" );
    VarB progFotoV              = VarB( "T0", "r8", "SurplusFotoV" );

    std::vector<VarB*>    progs = {&progBoilerACS,
                                   &progSummerAC,
                                   &progWinterFIRE,
                                   &progWinterPDC,
                                   &progExternalLight,
                                   &progAllRooms,
                                   &progFotoV
                                  };
    //*****************************************************************************************
    VarF3SP tCucina                   = { "T1", "v0", "v8", "v16", -0.5, 22, "tCucina",   10, 30 };
    VarF3SP tSala                     = { "T1", "v1", "v9", "v17",  1.5, 23, "tSala",     10, 30 };
    VarF3SP tCameraS                  = { "T1", "v2", "v10", "v18", 1.5, 18, "tCameraS",  10, 30 };
    VarF3SP tCameraD                  = { "T1", "v3", "v11", "v19", 0.5, 18, "tCameraD" , 10, 30 };
    VarF3SP tCameraM                  = { "T1", "v4", "v12", "v20", 1,   16, "tCameraM" , 10, 30 };
    VarF3SP tBagno                    = { "T1", "v5", "v13", "v21", 2.5, 23, "tBagno" ,   10, 30 };

    std::vector<VarF3SP*>    temps = {  &tCucina,
                                        &tSala,
                                        &tCameraS,
                                        &tCameraD,
                                        &tCameraM,
                                        &tBagno
                                     };
    //*****************************************************************************************
    VarB lampAngoli                    = { "T2", "r0", "lampAngoli" };
    VarB lampLati                      = { "T2", "r1", "lampLati" };
    VarB lampPalo                      = { "T2", "r2", "lampPalo" };
    VarB lampExtra                     = { "T2", "r3", "lampExtra" };

    std::vector<VarB*>    lights = {  &lampAngoli,
                                      &lampLati,
                                      &lampPalo,
                                      &lampExtra
                                   };
    //*****************************************************************************************
    VarB rPdc                           = { "T3", "r0", "Pdc" };
    VarB rPdcHeat                       = { "T3", "r1", "rPdcHeat" };
    VarB rPdcPompa                      = { "T3", "r2", "rPdcPompa" };
    VarB rPdcNightMode                  = { "T3", "r3", "rPdcNightMode" };
    VarB rPompaPianoPrimo               = { "T3", "r4", "rPompaPianoPrimo" };
    VarB rPompaPianoTerra               = { "T3", "r5", "rPompaPianoTerra" };
    VarB rBoilerACS                     = { "T3", "r6", "rBoilerACS" };
    VarB rPompaCamino                   = { "T3", "r7", "rPompaCamino" };

    std::vector<VarB*>    rcaldaia = {  &rPdc,
                                        &rPdcHeat,
                                        &rPdcPompa,
                                        &rPdcNightMode,
                                        &rPompaPianoPrimo,
                                        &rPompaPianoTerra,
                                        &rBoilerACS,
                                        &rPompaCamino
                                     };
    //*****************************************************************************************
    VarF tPufferHi          = { "T4", "v0", "PufferHi",0,60 };
    VarF tPufferLow         = { "T4", "v1", "PufferLow",0,60 };
    VarF tInputMixer        = { "T4", "v2", "InputMixer",0,60 };
    VarF tReturnFireplace   = { "T4", "v3", "ReturnFireplace",0,60 };
    VarF tReturnFloor       = { "T4", "v4", "ReturnFloor",0,60 };
    VarF tInletFloor        = { "T4", "v5", "InletFloor",0,60 };
    VarF tExternal          = { "T4", "v6", "External",-10,40 };
    VarF darkExternal       = { "T4", "v8", "darkExternal",0,40 };

    std::vector<VarF*>    tcaldaia = { &tPufferHi,
                                       &tPufferLow,
                                       &tInputMixer,
                                       &tReturnFireplace,
                                       &tReturnFloor,
                                       &tInletFloor,
                                       &tExternal,
                                       &darkExternal
                                     };
    //*****************************************************************************************
    VarB evCameraM1         = { "T5", "r0", "CameraM1" };
    VarB evCameraM2         = { "T5", "r1", "CameraM2" };
    VarB evSala1            = { "T5", "r2", "Sala1" };
    VarB evSala2            = { "T5", "r3", "Sala2" };
    VarB evCucina           = { "T5", "r4", "Cucina" };
    VarB evCameraS          = { "T5", "r5", "CameraS" };
    VarB evCameraD1         = { "T5", "r6", "CameraD1" };
    VarB evCameraD2         = { "T5", "r7", "CameraD2" };

    std::vector<VarB*>    evStanze = { &evCameraM1,
                                       &evCameraM2,
                                       &evSala1,
                                       &evSala2,
                                       &evCucina,
                                       &evCameraS,
                                       &evCameraD1,
                                       &evCameraD2
                                     };
    //*****************************************************************************************
    VarF3 wPowergrid            = { "T6", "v0", "v8", "v16", "PowerGrid" , 0, 4000};
    VarF3 wProduced             = { "T6", "v1", "v9", "v17", "Produced" , 0, 4000};
    VarF3 wL1                   = { "T6", "v2", "v10", "v18", "L1" , 0, 4000};
    VarF3 wL2                   = { "T6", "v3", "v11", "v19", "L2" , 0, 4000};
    VarF3 wL3                   = { "T6", "v4", "v12", "v20", "L3" , 0, 4000};

    // dato calcolato
    VarF3 wConsumed             = { "T6", "", "", "", "Consumed" , 0, 4000};
    VarF3 wSurplus              = { "T6", "", "", "", "Surplus" , 0, 4000};

    std::vector<VarF3*>    ampers = { &wPowergrid,
                                      &wProduced,
                                      &wL1,
                                      &wL2,
                                      &wL3,
                                      &wConsumed,
                                      &wSurplus
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

    QString m_logMessage;

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
            QString str = client.Request_Json();
            //****************************************
            QJsonDocument jsonDoc = QJsonDocument::fromJson(str.toUtf8());
            QJsonObject jsonRoot = jsonDoc.object();

            m_map = jsonRoot.toVariantMap();
            //****************************************
            for( VarB *elem : progs )
            {
                UpdateRelay( elem );
            }
            for( VarF3SP *elem : temps )
            {
                UpdateVal( elem );
            }
            for( VarB *elem : lights )
            {
                UpdateRelay( elem );
            }
            for( VarB *elem : rcaldaia )
            {
                UpdateRelay( elem );
            }
            for( VarF *elem : tcaldaia )
            {
                UpdateVal( elem );
            }
            for( VarB *elem : evStanze )
            {
                UpdateRelay( elem );
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

    bool SendModifiedData()
    {
        bool modifiedProg = false;
        try
        {
            //****************************************
            for( VarB *elem : progs )
            {
                modifiedProg |= SendModifiedValue( elem );
            }
            /*
            for( VarF3SP *elem : temps )
            {
                UpdateVal( elem );
            }*/
            for( VarB *elem : lights )
            {
                SendModifiedValue( elem );
            }
            for( VarB *elem : rcaldaia )
            {
                SendModifiedValue( elem );
            }
            /*
            for( VarF *elem : tcaldaia )
            {
                UpdateVal( elem );
            }*/
            for( VarB *elem : evStanze )
            {
                SendModifiedValue( elem );
            }
            /*
            for( VarF3 *elem : ampers )
            {
                UpdateVal( elem );
            }
            */
        }
        catch(...)
        {
        }
        return  modifiedProg;
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

    void SetValue(QString name1, QString name2, float value)
    {
        QVariantMap vmap1 = qvariant_cast<QVariantMap>(m_map[name1]);
        vmap1[name2] = value;
        m_map[name1] = vmap1;
    }
    //******************************************************************************************

    void UpdateVal(VarI *var)
    {
        var->m_value = GetValueI(var->m_t, var->m_v);
    }

    void UpdateVal(VarF *var)
    {
        var->m_value = GetValueF(var->m_t, var->m_v);
    }

    void UpdateRelay(VarB *var)
    {
        var->Value( GetValueI(var->m_t, var->m_r));
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
    //******************************************************************************************

    bool SendModifiedValue(VarB *var)
    {
        try
        {
            bool newval;
            if (var->IsModifiedValue(newval))
            {
                CQHttpClient client(m_host, m_port, 10000 );
                QString str = var->m_t.toLower() + "." + var->m_r.toLower() + "=" + QString::number(newval);
                client.Request_Set(str);
                return true;
            }
        }
        catch(...)
        {}
        return false;
    }

    /*
    void SendValue(VarF3 *var)
    {
        var->m_value = SetValueF(var->m_t, var->m_r);
        var->m_value1 = SetValueF(var->m_t, var->m_v1);
        var->m_value2 = SetValueF(var->m_t, var->m_v2);
    }

    void SendValue(VarF3SP *var)
    {
        var->m_value = SetValueF(var->m_t, var->m_v);
        var->m_value1 = SetValueF(var->m_t, var->m_v1);
        var->m_value2 = SetValueF(var->m_t, var->m_v2);
    }
    */

    void LogPoint()
    {
        // std::cerr << ".";
    }

    void LogMessage(QString s, bool logtofile = true)
    {
        m_logMessage += "\n";
        m_logMessage += s;
        std::cerr <<  "\n" << s.toStdString();

        if (logtofile)
        {
            QFile f("/var/log/dh.log");
            if (f.open(QIODevice::WriteOnly | QIODevice::Append))
            {
                f.write(s.toLatin1());
                f.write("\n\r");
            }
        }
    }

    bool GetLogMessage( QString &s )
    {
        s = m_logMessage;
        m_logMessage.clear();
        return s.size();
    }
};

