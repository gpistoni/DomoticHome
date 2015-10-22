
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
      if (str.length() > 0)
      {
        String dataString;
        dataString = short_time();
        dataString += str;

        Serial.println(dataString);
        m_queue[index] = dataString + "\n";
        index++;
        if (index >= 60) index = 0;
      }
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
