#include "functions.h"
#include "Logs.h"

//********************************************************************************************
// scompatta una lista in campi
String strValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++)
  {
    if (data.charAt(i) == separator || i == maxIndex)
    {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }
  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

double strValueD(String data, char separator, int index)
{
  return strValue( data, separator, index).toInt() / 10.0;
}

bool strValueB(String data, char separator, int index)
{
  return strValue( data, separator, index).toInt() > 0;
}

//********************************************************************************************
class cVar
{
  protected:
    byte m_t;
    byte m_signal;
    String m_descr;
    float m_value;
    float m_setpoint;

  public:
    cVar():
      m_t(0),
      m_signal(0),
      m_value(0),
      m_setpoint(0)
    {
    }

    cVar* setup(byte t, byte signal, String descr, float setpoint = 0)
    {
      m_t = t;
      m_signal = signal;
      m_descr = descr;
      m_value = setpoint;
      m_setpoint = setpoint;
      return this;
    }

    void set( float value )
    {
      m_value = value;
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
      String s =  String("@set(") + String(m_t) + "," + String(m_signal) + "=" + String(m_value)  + ")";
      wifi->HttpRequest( s );
      // log.add( String("Send Value ") + m_descr + ":" + String(m_value) );
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
        return "<td><a href=" + href + "> <input type='button' id='btn' value='AUTOMATICO'  class='fdis'/>";
      }
      else if ( m_setpoint == 1  )
      {
        String href = "'/set?" + descrSetPoint() + "=2'";
        return "<td><a href=" + href + ">  <input type='button' id='btn' value='FORCE ON' class='fon'/>";
      }
      else
      {
        String href = "'set?" + descrSetPoint() + "=0'";
        return "<td><a href=" + href + ">  <input type='button' id='btn' value='FORCE OFF' class='foff'/>";
      }
    }
};

//********************************************************************************************
class cFloat: public cVar
{
    float m_adjust;

  public:
    cFloat(): cVar(),
      m_adjust(0)
    {
    }

    void update( String stringlist )
    {
      float fval = strValueD(stringlist, ',', m_signal);
      fval += m_adjust;
      m_value = fval;

      //Serial.print(m_descr);
      //Serial.println(m_value);
    }

    void updateNz( String stringlist )
    {
      float fval = strValueD(stringlist, ',', m_signal);
      if (fval > 0)
      {
        fval += m_adjust;
        m_value = fval;
      }

      //Serial.print(m_descr);
      //Serial.println(m_value);
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

    void setAdjust( float adj)
    {
      m_adjust = adj;
    }

};

//********************************************************************************************
class cBool: public cVar
{
  public:
    cBool(): cVar()
    {
    }

    void update( String stringlist )
    {
      m_value = strValueB(stringlist, ',', m_signal);
    }

    operator bool()
    {
      return (bool) m_value;
    }

    int setPoint()
    {
      return (int)m_setpoint + 0.5;
    }

    void manualCheck( )
    {
      if ( setPoint() == 1 )   set( 1 );      //manual ON mode
      if ( setPoint() == 2 )   set( 0 );      //manual OFF mode
    }

    void send( DHwifi *wifi, BufferString &log)
    {
      String s =  String("@set(") + String(m_t) + "," + String(m_signal) + "=" + String(m_value)  + ")";
      wifi->HttpRequest( s );

      //if (m_value != 0)
      //   log.add( String("Send Value ") + m_descr + " (1)" );
      // else
      //   log.add( String("Send Value ") + m_descr + " (0)" );
    }
};

