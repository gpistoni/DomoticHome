#pragma once
#include "qstring.h"

//********************************************************************************************
class Var
{
public:
    QString m_t;
    QString m_v;
    QString m_r;
    QString m_descr;

    Var( QString t, QString v, QString r, QString descr)
    {
        m_t = t;    //terminale
        m_v = v;    //valore letto
        m_r = r;    //relay
        m_descr = descr;
    }

    virtual ~Var()
    {}
    virtual QString svalue()=0;
    QString terminal()  {   return m_t;    }
    QString descr()     {   return m_descr ;   }
};

//********************************************************************************************
class VarB: public Var
{
private:
    bool m_value=0;

    bool m_newValue=0;
    bool m_modified=0;

public:
    VarB( QString t, QString r, QString descr):
        Var( t, "", r, descr )
    {}
    virtual ~VarB()override
    {}
    virtual QString svalue() override
    {
        return QString::number(m_value);
    }
    operator bool()
    {
        return m_value;
    }
    bool IsModifiedValue(bool &newValue)
    {
        newValue = m_newValue;

        if (m_modified && m_newValue!=m_value )
        {
            return true;
        }
        m_modified = false;
        return false;
    }
    void SetValue(bool v)
    {
        m_value = v;
    }
    void ModifyValue(bool v)
    {
        m_newValue = v;
        m_modified = true;
    }
};

//********************************************************************************************
class VarBf: public Var
{
public:
    enum class tValue
    {
        OFF =0,
        ON=1,
        FORCE_OFF = 2,
        FORCE_ON = 3
    };

private:
    tValue  m_value=tValue::OFF;         // se 0 = off, 1= on, 2=forceOFF, 3=forceON
    tValue  m_newValue=tValue::OFF;
    bool m_modified=0;

public:
    VarBf( QString t, QString r, QString descr):
        Var( t, "", r, descr )
    {}
    virtual ~VarBf()override
    {}
    virtual QString svalue() override
    {
        return QString::number(static_cast<int>(m_value));
    }
    operator bool()
    {
        return (m_value==tValue::ON || m_value==tValue::FORCE_ON);
    }
    bool isForceOn()
    {
        return (m_value==tValue::FORCE_ON);
    }
    bool isForceOff()
    {
        return (m_value==tValue::FORCE_OFF);
    }
    bool IsModifiedValue(int &newValue)
    {
        newValue = static_cast<int>(m_newValue);

        if (m_modified && m_newValue!=m_value )
        {
            return true;
        }
        m_modified = false;
        return false;
    }
    void SetValue(int v)
    {
        m_value = static_cast<tValue>(v);
    }
    void ModifyValue(bool v)
    { // solo se non sono in forced
        if (m_value==tValue::ON || m_value==tValue::OFF)
        {
            m_newValue = static_cast<tValue>(v);
            m_modified = true;
        }
    }
    void ModifyValue(tValue v)
    {
        m_newValue = v;
        m_modified = true;
    }
};

//********************************************************************************************
class VarI: public Var
{
public:
    int m_value=0;

    VarI( QString t, QString v, QString r, QString descr):
        Var( t, v, r, descr ),
        m_value(0)
    {
    }
    virtual ~VarI()override
    {}
    virtual QString svalue() override
    {
        return QString::number(m_value);
    }
    operator int()
    {
        return m_value;
    }
};

//********************************************************************************************
class VarF: public Var
{
public:
    float m_value=0;

    int m_min=0;
    int m_max=0;

    VarF( QString t, QString v, QString descr, int minval, int maxval ):
        Var( t, v, "", descr ),
        m_min(minval),
        m_max(maxval)
    {
    }
    virtual ~VarF()override
    {}
    virtual QString svalue() override
    {
        return QString::number(static_cast<double>(m_value));
    }
    operator float()
    {
        return m_value;
    }
};


//********************************************************************************************
class VarF3: public VarF
{
public:
    QString m_v1;
    QString m_v2;
public:
    float m_value1=0;
    float m_value2=0;
    float pad=0;

    VarF3( QString t, QString v0, QString v1, QString v2, QString descr, int minval, int maxval):
        VarF( t, v0, descr,  minval,  maxval ),
        m_v1(v1),
        m_v2(v2)
    {}

    virtual ~VarF3()override {}

    float value_1()
    {
        return m_value1;
    }
    float value_2()
    {
        return m_value2;
    }
    void operator +=(const VarF3 &add)
    {
        m_value += add.m_value;
        //m_value1 += add.m_value1;
        //m_value2 += add.m_value2;
    }
    void operator -=(const VarF3 &sub)
    {
        m_value -= sub.m_value;
        //m_value1 -= sub.m_value1;
        //m_value2 -= sub.m_value2;
    }
};

//********************************************************************************************
class VarF3SP : public VarF3
{
public:
    float m_adjust=0;
    float m_setpoint=0;

public:
    VarF3SP(QString t,
            QString v0, QString v1, QString v2,
            float adj, float setpoint, QString descr, int minval, int maxval) :
        VarF3( t, v0,v1,v2, descr, minval, maxval),
        m_adjust(adj),
        m_setpoint(setpoint)
    {}

    virtual ~VarF3SP() override
    {}

    //set
    void set( float value )
    {
        m_value = value + m_adjust;
    }
    void setSetPoint( float value )
    {
        m_setpoint = value;
    }
    void setAdjust( float adj)
    {
        m_adjust = adj;
    }
    //***************************************************************************************
    float setPoint(float add =0)
    {
        return m_setpoint + add;
    }
    QString ssetPoint(float add=0)
    {
        return QString::number(static_cast<double>(m_setpoint+add));
    }
    QString descrSetPoint()
    {
        return "p" + m_descr ;
    }
};
