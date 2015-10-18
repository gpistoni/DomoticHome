#include "functions.h"

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
};

//********************************************************************************************
class cVar
{
  public:
    int m_t;
    int m_s;
    String m_descr;
    float m_value;

    cVar():
      m_t(0),
      m_s(0),
      m_value(0)
    {
    }

    cVar* setup(int t, int s, String descr)
    {
      m_t = t;
      m_s = s;
      m_descr = descr;
      return this;
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
      m_value = value;
    }

    void update( String stringlist )
    {
      m_value = strValueD(stringlist, ',', m_s);
      Serial.print(m_descr );
      Serial.print(":");
      Serial.println( m_value );
    }

    String getS()
    {
      return String("@set(") + String(m_t) + "," + String(m_s) + "=" + String(m_value)  + ")";
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
      m_value = value;
    }

    void update( String stringlist )
    {
      m_value = strValueB(stringlist, ',', m_s);
      Serial.print(m_descr );
      Serial.print(":");
      Serial.println( m_value );
    }

    String getS()
    {
      return String("@set(") + String(m_t) + "," + String(m_s) + "=" + String(m_value)  + ")";
    }

    operator bool()
    {
      return (bool) m_value;
    }
};

class BufferString
{
    String m_queue[60];
    unsigned int index;

  public:
    BufferString():
      index(0)
    {
    }

    void add( const String &str )
    {
      String dataString;
      dataString = short_time();
      dataString += str;

      Serial.println(dataString);
      m_queue[index] = dataString + "\n";
      index++;
      if (index >= 60) index = 0;
    }

    String get( )
    {
      String str;
      for (int i = index; i < 60; i++)
        str += m_queue[i];
      for (int i = 0; i < index; i++)
        str += m_queue[i];
      return str;
    }
};
