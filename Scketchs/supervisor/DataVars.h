#include "functions.h"
#include "Logs.h"

String strValue(String data, char separator, int index);
double strValueD(String data, char separator, int index);
bool strValueB(String data, char separator, int index);

//********************************************************************************************
class cVar
{
  protected:
    byte m_t;
    byte m_s;
    String m_descr;
    float m_value;
    float m_setpoint;
    bool m_modified;

  public:
    cVar():
      m_t(0),
      m_s(0),
      m_value(0),
      m_setpoint(0),
      m_modified(false)
    {
    }

    cVar* setup(byte t, byte s, String descr, float setpoint = 0)
    {
      m_t = t;
      m_s = s;
      m_descr = descr;
      m_value = setpoint;
      m_setpoint = setpoint;
      return this;
    }


    void set( float value )
    {
      if ( m_value != value)
      {
        m_value = value;
        m_modified = true;
      }
    }

    void setSetPoint( float value )
    {
      m_setpoint = value;
      Serial.print(m_descr);
      Serial.print("=");
      Serial.println(m_setpoint);
    }

    void send( DHwifi *wifi, BufferString &log)
    {
      if (m_modified)
      {
        String s =  String("@set(") + String(m_t) + "," + String(m_s) + "=" + String(m_value)  + ")";
        wifi->HttpRequest( s );
        m_modified = false;
        log.add( String("Send Value ") + m_descr + ":" + String(m_value) );
      }
    }

    float value()
    {
      return m_value ;
    }

    float setPoint()
    {
      return m_setpoint;
    }

    String descr()
    {
      return m_descr ;
    }

    String descrSetPoint()
    {
      return "p" + m_descr ;
    }

    String td_descr()
    {
      return String("<td>") + m_descr ;
    }

    String td_valueF()
    {
      return String("<td>") + m_value;
    }

    String td_setpointF()
    {
      return String("<td>") + m_setpoint;
    }

    String td_bulb()
    {
      if ( m_value )
        return "<td><input type='button' id='btn' class='on'/>";
      else
        return "<td><input type='button' id='btn' class='off'/>";
    }

    String td_star()
    {
      if ( m_setpoint == 0  )
      {
        String href = "'/set?" + descrSetPoint() + "=1'";
        return "<td><a href=" + href + "> <input type='button' id='btn' value='DIS'  class='fdis'/>";
      }
      else if ( m_setpoint == 1  )
      {
        String href = "'/set?" + descrSetPoint() + "=2'";
        return "<td><a href=" + href + ">  <input type='button' id='btn' value='ON' class='fon'/>";
      }
      else
      {
        String href = "'set?" + descrSetPoint() + "=0'";
        return "<td><a href=" + href + ">  <input type='button' id='btn' value='OFF' class='foff'/>";
      }
    }
};

//********************************************************************************************
class cFloat: public cVar
{
  public:
    cFloat(): cVar()
    {
    }

    void update( String stringlist )
    {
      m_value = strValueD(stringlist, ',', m_s);
      //Serial.print(m_descr );
      //Serial.print(":");
      //Serial.println( m_value );
    }

    operator float()
    {
      return m_value;
    }

    String webColor()
    {
      int v = (int)(m_value - 10 * 20);
      if ( v > 255 ) v = 255;
      return String("rgb(") + String(v) + String(",255,") + String(255 - v) + String(")");
    }

};

//********************************************************************************************
class cBool: public cVar
{
  public:
    cBool(): cVar()
    {
    }

    void set( bool value )
    {
      if (  m_value != value)
      {
        m_value = value;
        m_modified = true;
      }
    }

    void update( String stringlist )
    {
      m_value = strValueB(stringlist, ',', m_s);
      //Serial.print(m_descr );
      //Serial.print(":");
      //Serial.println( m_value );
    }

    operator bool()
    {
      return (bool) m_value;
    }

    int setPoint()
    {
      return (int)m_setpoint;
    }

    void manualCheck( bool autoValue )
    {
      if ( setPoint() == 1 )   set( true );       //manual mode
      else if ( setPoint() == 2 )   set( false );
      else set( autoValue );
    }
};

