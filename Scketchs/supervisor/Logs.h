#define LOG_LEN 100

class BufferString
{
    String m_queue[LOG_LEN];
    unsigned int index;

  public:
    BufferString():
      index(0)
    {
    }

    void add( const String &str )
    {
      if (str.length() > 0)
      {
        String dataString;
        dataString = short_time();
        dataString += str;

        Serial.println(dataString);
        m_queue[index] = dataString + "\n";
        index++;
        if (index >= LOG_LEN) index = 0;
      }
    }

    String getHTML( )
    {
      String str;
      for (int i = index-1; i>=0; i--)
        str += m_queue[i] + "<br>";
       for (int i = LOG_LEN-1; i>index; i--)
        str += m_queue[i] + "<br>";
      return str;
    }

    String get( int i )
    {
      return  m_queue[i];
    }
};
