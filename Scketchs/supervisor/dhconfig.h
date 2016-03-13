// Example: storing JSON configuration file in flash file system

#include <ArduinoJson.h>
#include "FS.h"

class DHFile
{
    File m_File;
    StaticJsonBuffer<200> jsonBuffer;

  public:
    JsonObject&  root()
    {
      return jsonBuffer.createObject();
    }

    bool LoadFile( String filename = "/config.json" )
    {
      Serial.print("Mounting FS....");

      if (!SPIFFS.begin())

        Serial.println("Success");

      m_File = SPIFFS.open(filename, "r");
      if (!m_File)
      {
        Serial.println("Failed to open config file");
        return false;
      }

      size_t size = m_File.size();
      if (size > 1024)
      {
        Serial.println("Config file size is too large");
        return false;
      }

      // Allocate a buffer to store contents of the file.
      std::unique_ptr<char[]> buf(new char[size]);

      // We don't use String here because ArduinoJson library requires the input
      // buffer to be mutable. If you don't use ArduinoJson, you may as well
      // use configFile.readString instead.
      m_File.readBytes(buf.get(), size);
      jsonBuffer.parseObject(buf.get());
    }

    String ReadValue( String param )
    {
      JsonObject& root = jsonBuffer.createObject();

      if (!root.success())
        return root[ param ];
      return "";
    }

    bool WriteValue(String param, String value, bool save)
    {
      JsonObject& root = jsonBuffer.createObject();

      root[ param ] = value;
    }

    bool SaveFile(String filename = "/config.json" )
    {
      File configFile = SPIFFS.open(filename, "w");
      if (!configFile)
      {
        Serial.println("Failed to open config file for writing");
        return false;
      }

      JsonObject& root = jsonBuffer.createObject();
      root.printTo(configFile);
      return true;
    }


    /*
        const char* serverName = json["serverName"];
        const char* accessToken = json["accessToken"];

        // Real world application would store these values in some variables for
        // later use.

        Serial.print("Loaded serverName: ");
        Serial.println(serverName);
        Serial.print("Loaded accessToken: ");
        Serial.println(accessToken);
        return true;
    */


};
