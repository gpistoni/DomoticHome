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

    virtual ~Var() {}

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
    {
    }

    virtual ~VarB()override{}

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
        if (m_modified)
        {
            newValue = m_newValue;
            m_modified = false;
            return true;
        }
else
            return false;
    }
    void Value(bool v)
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
class VarI: public Var
{
public:
    int m_value=0;

    VarI( QString t, QString v, QString r, QString descr):
        Var( t, v, r, descr ),
        m_value(0)
    {
    }
    virtual ~VarI()override {}


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

    VarF( QString t, QString v, QString descr):
        Var( t, v, "", descr )
    {
    }

    virtual ~VarF()override {}

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

    VarF3( QString t, QString v0, QString v1, QString v2, QString descr):
        VarF( t, v0, descr ),
        m_v1(v1),
        m_v2(v2)
    {
    }

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
        m_value1 += add.m_value1;
        m_value2 += add.m_value2;
    }
    void operator -=(const VarF3 &sub)
    {
        m_value -= sub.m_value;
        m_value1 -= sub.m_value1;
        m_value2 -= sub.m_value2;
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
            float adj, float setpoint, QString descr) :
        VarF3( t, v0,v1,v2, descr ),
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
    float setPoint()
    {
        return m_setpoint;
    }
    QString ssetPoint()
    {
        return QString::number(static_cast<double>(m_setpoint));
    }

    QString descrSetPoint()
    {
        return "p" + m_descr ;
    }
};
