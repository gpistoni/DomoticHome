#include "functions.h"
#include "Logs.h"

//********************************************************************************************
class cVar
{
  protected:
    String m_t;
    String m_v;
    String m_descr;
    float m_value;
    float m_adjust;
    float m_setpoint;

  public:
    cVar():
      m_value(0),
      m_adjust(0),
      m_setpoint(0)
    {
    }

    ~cVar()
    {}

    cVar* setup(String t, String v, String descr, float setpoint = 0)
    {
      m_t = t;
      m_v = v;
      m_descr = descr;
      m_value = setpoint;
      m_setpoint = setpoint;
      return this;
    }
   
    //***************************************************************************************
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
        Serial.println(m_descr +": "+ sval() );
      }
    }

    void setSetPoint( float value )
    {
      m_setpoint = value;
      Serial.print(m_descr);
      Serial.print("=");
      Serial.println(m_setpoint);
    }

    void setAdjust( float adj)
    {
      m_adjust = adj;
    }

    void sendRequest( DHwifi *wifi, BufferString &log)
    {
      String s =  String("@set(") + m_t + "," + m_v + "=" + String(m_value)  + ")";
      wifi->HttpRequest( s );
      //log.add( String("Send Value ") + m_descr + ":" + String(m_value) );
    }

    operator float()
    {
      return m_value;
    }

    float val()
      {
      return m_value ;
      }
      
    String sval()
      {
      return String(m_value) ;
      }

    //***************************************************************************************
    //get
    float setPoint()
    {
      return m_setpoint;
    }

    String terminal()
    {
      return m_t;
    }

    String idxvalue()
    {
      return m_v;
    }

    String descr()
    {
      return m_descr ;
    }

    String descrSetPoint()
    {
      return "p" + m_descr ;
    }

    //***************************************************************************************
    //web
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

    operator bool()
    {
      return (bool) m_value;
    }

    int setPoint()
    {
      return (int)(m_setpoint + 0.5);
    }

    void manualCheck( )
    {
      if ( setPoint() == 1 )   set( 1 );      //manual ON mode
      if ( setPoint() == 2 )   set( 0 );      //manual OFF mode
    }

};
