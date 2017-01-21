#include <WiFiClientSecure.h>

class HTTPSClient : private WiFiClientSecure {
    String m_host;

  public:
    void Connect( const char* host, uint16_t httpsPort, const char* fingerprint)
    {
      m_host = host;
      Serial.flush();
      Serial.print("connecting to ");
      Serial.println(host);
      if (!connect(host, httpsPort))
      {
        Serial.println("connection failed");
        return;
      }
      Serial.flush();

      if (verify(fingerprint, host))
      {
        Serial.println("certificate matches");
      } else {
        Serial.println("certificate doesn't match");
      }
    };

    void Post( String url)
    {
      Serial.println("==========");
      Serial.print("requesting URL: ");
      Serial.println(url);

      print(String("GET ") + url + " HTTP/1.1\r\n" +
            "Host: " + m_host + "\r\n" +
            "User-Agent: BuildFailureDetectorESP8266\r\n" +
            "Connection: close\r\n\r\n");
      Serial.println("==========");
      Serial.println("request sent");
      while (connected())
      {
        String line = readStringUntil('\n');
        if (line == "\r")
        {
          Serial.println("==========");
          Serial.println("headers received");  
          Serial.println(line);
          break;
        }
      }

      Serial.println("==========");
      String line = readStringUntil('\n');
      Serial.println("==========");
      Serial.println("reply was:");
      Serial.println("==========");
      Serial.println(line);
      Serial.println("==========");
      Serial.println("closing connection");
      Serial.println("==========");
    };
};


