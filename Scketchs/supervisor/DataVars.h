#include "functions.h"
#include "Logs.h"

String strValue(String data, char separator, int index);
double strValueD(String data, char separator, int index);
bool strValueB(String data, char separator, int index);

//********************************************************************************************
class cParam
{
  public:
    String m_descr;
    float m_value;

    cParam():
      m_value(0)
    {
    }

    cParam* setup( String descr, float def )
    {
      m_descr = descr;
      m_value = def;
      return this;
    }

    operator float()
    {
      return m_value;
    }

    String td_valueF()
    {
      return String("<td>") + m_value + String("</td>");
    }

    String td_star()
    {
      if ( m_value == 0  )
      {
        String href = "'http://192.168.0.201/set?" + m_descr + "=1'";
        return "<td><a href=" + href + "> <input type='button' id='btn' value='DIS'  class='fdis'/>";
      }
      else if ( m_value == 1  )
      {
        String href = "'http://192.168.0.201/set?" + m_descr + "=2'";
        return "<td><a href=" + href + ">  <input type='button' id='btn' value='ON' class='fon'/>";
      }
      else
      {
        String href = "'http://192.168.0.201/set?" + m_descr + "=0'";
        return "<td><a href=" + href + ">  <input type='button' id='btn' value='OFF' class='foff'/>";
      }
    }
};


//********************************************************************************************
class cVar
{
  public:
    byte m_t;
    byte m_s;
    String m_descr;
    float m_value;
    bool m_modified;

    cVar():
      m_t(0),
      m_s(0),
      m_value(0),
      m_modified(false)
    {
    }

    cVar* setup(byte t, byte s, String descr)
    {
      m_t = t;
      m_s = s;
      m_descr = descr;
      return this;
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

    String td_descr()
    {
      return String("<td>") + m_descr ;
    }

    String td_valueF()
    {
      return String("<td>") + m_value;
    }

    String td_bulb()
    {
      if ( m_value )
        return "<td><input type='button' id='btn' class='on'/>";
      else
        return "<td><input type='button' id='btn' class='off'/>";
    }
};

//********************************************************************************************
class cFloat: public cVar
{
  public:
    cFloat(): cVar()
    {
    }

    void set( float value )
    {
      if ( m_value != value)
      {
        m_value = value;
        m_modified = true;
      }
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
};

