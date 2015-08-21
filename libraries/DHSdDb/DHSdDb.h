#include <SD.h>

class SDDB
{
  public:
    static String ReadValue( String section, String key)
    {
      String str;
      File dataFile = SD.open("/" + section + "/" + key  );

      if (dataFile)
      {
        while (dataFile.available())
        {
          char c = dataFile.read();
          str = str + c;
        }
      }
      dataFile.close();
      return str;
    }

    static String WriteValue( String section, String key, String value)
    {
      SD.mkdir( "/" + section );
      File dataFile = SD.open("/" + section + "/" + key , FILE_WRITE );

      if (dataFile)
      {
        dataFile.seek(0);
        dataFile.print(value);
      }
      dataFile.close();
    }
};