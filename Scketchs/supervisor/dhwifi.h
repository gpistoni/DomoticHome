#ifndef dhwifi_h
#define dhwifi_h

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

class DHwifi
{
  private:

    WiFiUDP udp;        			                // A UDP instance to let us send and receive packets over UDP
    static const int NTP_PACKET_SIZE = 48;  	// NTP time stamp is in the first 48 bytes of the message
    byte packetBuffer[ NTP_PACKET_SIZE];  	  // buffer to hold incoming and outgoing packets

    String m_host;

  public:
    DHwifi() {};

    void setup( IPAddress ip, IPAddress gateway, IPAddress subnet, String remoteServer = "192.168.0.200" );
    String HttpRequest( String req );
    time_t GetSystemTime();

  private:
    // send an NTP request to the time server at the given address
    unsigned long sendNTPpacket(IPAddress& address);
};

#endif
