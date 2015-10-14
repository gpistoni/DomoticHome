#pragma once

#include <mutex>
#include <QString>
#include <map>
#include <QDebug>
#include <QReadWriteLock>

#define gData CData::m_pInstance

//*************************************************************************************************************
class CData : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(CData);

private:
    static const int cols=10;

    std::map<int, double> m_value;
    std::map<int, QString> m_label;
    std::map<QString, int> m_index;

    std::map< int, double> m_param;
    std::map< int, QString> m_labelParam;
    std::map<QString, int> m_indexParam;

    std::map< QString, std::map<double,double> > m_valueHisto;

    QReadWriteLock m_mutex;

    // Define signal:
signals:
    void sigValueChanged();
    void sigParamChanged( QString par );

public:
    static CData* m_pInstance;  // m_pInstance
    static void init();
    CData()
    {
        m_pInstance = NULL;
    }
    //********************************************************************/

    void _SetV( const int i, const QString &value )
    {
        SetV( i, value.toDouble() );
    }

    void _SetVparam( const int i, const QString &value )
    {
        SetVparam( i, value.toDouble() );
    }

    //********************************************************************/
    void SetV( const int i, const float val )
    {
        QWriteLocker m(&m_mutex);
        if ( m_value[i] != val )
        {
            m_value[i] = val;
            m_mutex.unlock();
            emit sigValueChanged();
        }
    }

    void SetVparam( const int i, const float val )
    {
        QWriteLocker m(&m_mutex);
        if ( m_param[i] != val )
        {
            m_param[i] = val;
            m_mutex.unlock();
            emit sigParamChanged( m_labelParam[i] );
        }
    }

    //********************************************************************/
    void SetL( const int i, const QString &label )
    {
        QWriteLocker m(&m_mutex);
        m_label[i] =  label;
        m_index[label] = i;
    }

    void SetLparam( const int i, const QString &label )
    {
        QWriteLocker m(&m_mutex);
        m_labelParam[i] = label;
        m_indexParam[label] = i;
    }

    //********************************************************************/
    double GetV( const int i )
    {
        QReadLocker m(&m_mutex);
        return m_value[i];
    }

    double GetVparam( const int i )
    {
        QReadLocker m(&m_mutex);
        return m_param[i];
    }

    double GetVparam( const QString &par )
    {
        QReadLocker m(&m_mutex);
        return m_param[m_indexParam[par]];
    }

    //********************************************************************/
    QString GetL( const int i )
    {
        QReadLocker m(&m_mutex);
        return m_label[i];
    }

    QString GetLparam( const int i )
    {
        QReadLocker m(&m_mutex);
        return m_labelParam[i];
    }

    //********************************************************************/
};






