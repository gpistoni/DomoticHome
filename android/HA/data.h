#pragma once
#include <mutex>
#include <QString>
#include <map>
#include <QDebug>


//*************************************************************************************************************
class CData
{
private:
    std::map< QString, double> values;
    QMutex m_mutex;

public:
    CData()
    {
    }

    CData( const CData &cp )
    {
        qDebug() << "Copy CAllData" ;
        values = cp.values;
    }
};

// Q_DECLARE_METATYPE(pWaterTempData);         // necessario i gli eventi e gli slot



