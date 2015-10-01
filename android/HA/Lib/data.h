#pragma once

#include <mutex>
#include <QString>
#include <map>
#include <QDebug>
#include <QMutex>

class CData;
extern CData g_data;

//*************************************************************************************************************
class CData : public QObject
{
   Q_OBJECT
   Q_DISABLE_COPY(CData);

private:
    static const int cols=10;

    std::map<int, double> m_value;
    std::map<int, QString> m_label;
    std::map< QString, int> m_index;

    std::map<int, double> m_valueSetpoint;

    QMutex m_mutex;

// Define signal:
signals:
    void sigChanged();

public:
    CData()
    {
    }

    void SetV( const int x, const int y, const float val )
    {
        QMutexLocker m(&m_mutex);
        m_value[x + y*cols] =  val;
    }

    void SetV( const int i, const float val )
    {
        QMutexLocker m(&m_mutex);
        m_value[i] =  val;
    }

    void SetVsetpoint( const int i, const float val )
    {
        QMutexLocker m(&m_mutex);
        m_valueSetpoint[i] =  val;
    }

    void SetV( const int i, const QString &value )
    {
        QMutexLocker m(&m_mutex);
        m_value[i] =  value.toDouble();
    }

    void SetL( const int i, const QString &label )
    {
        QMutexLocker m(&m_mutex);
        m_label[i] =  label;
        m_index[label] = i;
    }

    float GetV( const int x, const int y)
    {
        QMutexLocker m(&m_mutex);
        return m_value[x + y*cols];
    }

    float GetV( const int i )
    {
        QMutexLocker m(&m_mutex);
        return m_value[i];
    }

    float GetV( const QString &label )
    {
        QMutexLocker m(&m_mutex);
        return m_value[ m_index[label] ];
    }

    float GetVsetpoint( const int i )
    {
        QMutexLocker m(&m_mutex);
        return m_value[i];
    }

    QString GetL( const int x, const int y)
    {
        QMutexLocker m(&m_mutex);
        return m_label[x + y*cols];
    }

    QString GetL( const int i )
    {
        QMutexLocker m(&m_mutex);
        return m_label[i];
    }
};




