#include <dhwifi.h>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


DHwifi dhWifi;


// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  IPAddress ip(192, 168, 0, 178);
        
  dhWifi.setup( ip );
}

void loop()
{
  dhWifi.PrintTime();
}
