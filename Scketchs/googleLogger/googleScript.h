

class GoogleScript {
    String m_host;
    WiFiClientSecure m_cli;

  public:
    GoogleScript( const char* host, const char* fingerprint)
    {
      m_host = host;
      Serial.flush();
      Serial.print("connecting to ");
      Serial.println(host);

      if (!m_cli.connect(host, 443))
      {
        Serial.println("connection failed");
        return;
      }
      Serial.flush();
      m_cli.flush();
      /*
            Serial.print("check fingerptint: ");
            if (m_cli.verify(fingerprint, host))
            {
              Serial.println("matches");
            } else {
              Serial.println("doesn't match");
            }
      */
    };

    ~GoogleScript(){ };

    void Post( String url)
    {
      Serial.println("==========");
      Serial.print("requesting URL: ");
      Serial.println(url);

      String getURL = String("GET ") + url + " HTTP/1.1\r\n" +
                      "Host: " + m_host + "\r\n" +
                      "User-Agent: BuildFailureDetectorESP8266\r\n" +
                      "Connection: close\r\n\r\n";

      m_cli.print( getURL );
      m_cli.flush();

      Serial.println("request sent");
      Serial.println("==========");
      /*
        Serial.println("reply was:");
        Serial.println("==========");
        Serial.flush();

        int c = 0;
        while (m_cli.available())
        {
        String line = m_cli.readStringUntil('\n');
        Serial.println(line);
        delay(10);
        }
        Serial.println("==========");*/
    };
};


