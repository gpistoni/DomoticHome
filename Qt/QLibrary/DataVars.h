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
};

//********************************************************************************************
class VarF : Var
{
public:

    float m_value;
    float m_adjust;
    float m_setpoint;

public:
    VarF(QString t, QString v, QString r, QString descr): Var( t, v, r, descr ),
        m_value(0),
        m_adjust(0),
        m_setpoint(0)
    {
    }

    ~VarF()
    {}

    //set
    void set( float value )
    {
        m_value = value + m_adjust;
    }

    void setNz( float value )
    {
        if (value > 0)
        {
            m_value = value + m_adjust;
            //  Serial.println(m_descr + ": " + sval() );
        }
    }

    void setSetPoint( float value )
    {
        m_setpoint = value;
        //    Serial.print(m_descr);
        //    Serial.print("=");
        //    Serial.println(m_setpoint);
    }

    void setAdjust( float adj)
    {
        m_adjust = adj;
    }

    /*   void sendRequest( DHwifi *wifi, BufferString &log)
   {
      // Sent set?T5-r4=0.00
      String s =  String("set?" ) + m_t + "-" + m_r + "=" + String(m_value);
      wifi->HttpRequest( s );
      log.add( String("Send Value ") + m_descr + " " + s );
    }
*/

    operator float()
    {
        return m_value;
    }

    /* QString sval()
    {
      return QString::to\(m_value,) ;
    }*/

    //***************************************************************************************
    //get
    float setPoint()
    {
        return m_setpoint;
    }

    QString terminal()
    {
        return m_t;
    }

    QString idxvalue()
    {
        return m_v;
    }

    QString descr()
    {
        return m_descr ;
    }

    QString descrSetPoint()
    {
        return "p" + m_descr ;
    }

};

//********************************************************************************************
class VarI: public Var
{
public:

    int m_value;

    VarI( QString t, QString v, QString r, QString descr):
        Var( t, v, r, descr ),
        m_value(0)
    {
    }

    operator int()
    {
        return m_value;
    }


    /*
    void manualCheck( )
    {
      if ( setPoint() == 1 )   set( 1 );      //manual ON mode
      if ( setPoint() == 2 )   set( 0 );      //manual OFF mode
    }
    */

};
