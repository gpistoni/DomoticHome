String strValue(String data, char separator, int index);
double strValueD(String data, char separator, int index);
bool strValueB(String data, char separator, int index);

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
      m_s(0)
    {
    }

    cVar* setup(int t, int s, String descr)
    {
      m_t = t;
      m_s = s;
      m_descr = descr;
      m_value = 0;
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
