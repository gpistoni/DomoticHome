#include "functions.h"
#include "Logs.h"

String strValue(String data, char separator, int index);
double strValueD(String data, char separator, int index);
bool strValueB(String data, char separator, int index);

String srcIcon(String name)
{
  return "src='http://www.fancyicons.com/free-icons/123/onebit-2/png/32/" + name + "_32.png'";
}

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
      String href = "'http://192.168.0.201/set?" + m_descr + "=" + String( m_value == 0 ) + "'";

      if ( m_value == 0  )
      {
        String href = "'http://192.168.0.201/set?" + m_descr + "=1'";
        return "<td><a href=" + href + "> <img " + srcIcon("star_3") + " alt='OFF'>  </a> </td>";
      }
      else
      {
        String href = "'http://192.168.0.201/set?" + m_descr + "=0'";
        return "<td><a href=" + href + "> <img " + srcIcon("star_3") + " alt='OFF'>  </a> </td>";
      }
    }
};


//********************************************************************************************
class cVar
{
  public:
    int m_t;
    int m_s;
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

    cVar* setup(int t, int s, String descr)
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
      return String("<td>") + m_descr + String("</td>");
    }

    String td_valueF()
    {
      return String("<td>") + m_value + String("</td>");
    }

    String td_valueB()
    {
      return String("<td>") + (int)m_value + String("</td>");
    }

    String td_bulb()
    {
      if ( m_value )
        return "<td><input type='button' id='btn' class='on'/></td>";
      else
        return "<td><input type='button' id='btn' class='off'/></td>";
     /* 
      if ( m_value )
        return "<td> <img " + srcIcon("bulb_1") + " alt='ON'></td>";
      else
        return "<td> <img " + srcIcon("bulb_2") + " alt='OFF'></td>";
     */
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
      Serial.print(m_descr );
      Serial.print(":");
      Serial.println( m_value );
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
      Serial.print(m_descr );
      Serial.print(":");
      Serial.println( m_value );
    }

    operator bool()
    {
      return (bool) m_value;
    }
};

