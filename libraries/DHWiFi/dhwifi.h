#ifndef dhwifi_h
#define dhwifi_h

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

class DHwifi
{
private:

    WiFiUDP udp;        			// A UDP instance to let us send and receive packets over UDP
    static const int NTP_PACKET_SIZE = 48;  	// NTP time stamp is in the first 48 bytes of the message
    byte packetBuffer[ NTP_PACKET_SIZE];  	// buffer to hold incoming and outgoing packets

   String m_host;

public:
    DHwifi()
    {
    };

    void setup( IPAddress ip, IPAddress gateway, IPAddress subnet, String remoteServer = "192.168.1.200" )
    {
        char ssid[] = "PistoniHomeT";     	// your network SSID (name)
        char pass[] = "giaco.iren.dario";       	// your network password
        unsigned int localPort = 2390;      	// local port to listen for UDP packets

	m_host = remoteServer;

        // We start by connecting to a WiFi network
        Serial.print("Connecting to ");
        Serial.println(ssid);

        WiFi.config(ip, gateway, subnet);
        WiFi.begin(ssid, pass);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
        Serial.println("");

        Serial.print("WiFi connected. ");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());

        Serial.print("Starting UDP.");
        udp.begin(localPort);
        Serial.print("Local port: ");
        Serial.println(udp.localPort());
    }

    String HttpRequest( String req = "@get(0,0)" );

    time_t GetSystemTime();

private:
    // send an NTP request to the time server at the given address
    unsigned long sendNTPpacket(IPAddress& address);

};

 void printDigits(int digits);

#endif
