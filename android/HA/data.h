#pragma once

#include <mutex>
#include <QString>
#include <map>
#include <QDebug>
#include <QMutex>


//*************************************************************************************************************
class CData
{
private:
    static const int c=10;

    std::map<int, double> m_value;
    std::map<int, QString> m_label;
    std::map< QString, int> m_index;

    QMutex m_mutex;

public:
    CData()
    {
    }

    CData( const CData &cp )
    {
        qDebug() << "Copy CAllData" ;
        m_value = cp.m_value;
        m_label = cp.m_label;
        m_index = cp.m_index;
    }

    void Set( const int x, const int y, const float val )
    {
        QMutexLocker m(&m_mutex);
        m_value[x + y*c] =  val;
    }

    void Set( const int i, const float val )
    {
        QMutexLocker m(&m_mutex);
        m_value[i] =  val;
    }

    void SetS( const int i, const QString &label )
    {
        QMutexLocker m(&m_mutex);
        m_label[i] =  label;
        m_index[label] = i;
    }

    float GetV( const int x, const int y)
    {
        QMutexLocker m(&m_mutex);
        return m_value[x + y*c];
    }

    float GetV( const QString &label )
    {
        QMutexLocker m(&m_mutex);
        return m_value[ m_index[label] ];
    }

    QString GetS( const int x, const int y)
    {
        QMutexLocker m(&m_mutex);
        return m_label[x + y*c];
    }
};




