#include "dbmanager.h"
#include "../QLibrary/HttpRequest.h"

DbManager::DbManager()
{

}

void DbManager::LogEnergy()
{
     QString url("http://pistonihome.altervista.org/data/set.php?");
    url += "Prod=";
    url += QString::number((int)m_dt->wProduced);
    url += "&Cons=";
    url += QString::number((int)m_dt->wConsumed);
    url += "&SCons=";
    url += QString::number((int)m_dt->wSelfConsumed);
    url += "&Surplus=";
    url += QString::number((int)fabs(m_dt->wSurplus));
    url += "&L1=";
    url += QString::number((int)m_dt->wL1);
    url += "&L2=";
    url += QString::number((int)m_dt->wL2);
    url += "&L3=";
    url += QString::number((int)m_dt->wL3);

    HttpRequest request2;
    QString result2 = request2.executeBlockingGet(url);

    m_dt->LogMessage(url);
    m_dt->LogMessage(result2);
}
