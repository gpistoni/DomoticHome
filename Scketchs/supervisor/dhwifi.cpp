#include "dhwifi.h"

//************************************************************************************************************************
void  DHwifi::setup( IPAddress ip, IPAddress gateway, IPAddress subnet, String ssid, String pass, String remoteServer )
{
  unsigned int localPortUDP = 2390;     // local port to listen for UDP packets

  m_remoteServer = remoteServer;

  // We start by connecting to a WiFi network
  Serial.print("WIFI LINK to ");
  Serial.println(ssid);

  WiFi.config(ip, gateway, subnet);
  WiFi.begin(ssid.c_str(), pass.c_str());

  // disable access point // set mode to WIFI_AP, WIFI_STA, or WIFI_AP_STA.
  WiFi.mode(WIFI_STA);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(5000);
    Serial.println(ssid + " not Linked.");
  }
  Serial.println(ssid + " Linked.");

  Serial.print("WiFi connected. ");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("Starting UDP.");
  udp.begin(localPortUDP);
  Serial.print("Local port: ");
  Serial.println(udp.localPort());
}

//************************************************************************************************************************
time_t DHwifi::GetSystemTime()
{
  IPAddress timeServerIP; // time.nist.gov NTP server address
  const char* ntpServerName = "time.nist.gov";
  //const char* ntpServerName = "it.pool.ntp.org";

  //get a random server from the pool
  WiFi.hostByName(ntpServerName, timeServerIP);

  sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  // wait to see if a reply is available
  delay(2000);

  int cb = udp.parsePacket();
  if (!cb)
  {
    Serial.println("no packet yet");
    Serial.println(timeServerIP);
  }
  else
  {
    Serial.print("NTP packet received, length=");
    Serial.println(cb);
    // We've received a packet, read the data from it
    udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

    //the timestamp starts at byte 40 of the received packet and is four bytes,
    // or two words, long. First, esxtract the two words:

    unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
    unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
    // combine the four bytes (two words) into a long integer
    // this is NTP time (seconds since Jan 1 1900):
    unsigned long secsSince1900 = highWord << 16 | lowWord;

    // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
    const unsigned long seventyYears = 2208988800UL;
    // subtract seventy years:
    unsigned long epoch = secsSince1900 - seventyYears;
    return epoch + 3600;

  }
  // wait ten seconds before asking for the time again
  return 0;
}

//************************************************************************************************************************
// send an NTP request to the time server at the given address
unsigned long DHwifi::sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

//************************************************************************************************************************
String DHwifi::HttpRequest( String req )
{
  WiFiClient client;

  char host[99];
  m_remoteServer.toCharArray( host, 99);
  const int httpPort = 80;

  if (client.connect(host, httpPort))
  {
    String sreq = String("GET ") + req + " HTTP/1.1\r\n" +
                  "Host: " + host + "\r\n" +
                  "Connection: close\r\n\r\n";
    client.print(sreq);
    //Serial.print(sreq);
    //delay(200);

    String result;
    while (client.connected())
    {
      if (client.available())
      {
        result += client.readStringUntil('\r');
      }
    }
    client.stop();

    Serial.println("-- HttpRequest -- Recived" + String(result.length()) + " Bytes");
    return result;
  }
  else
  {
    client.stop();
    Serial.print( host );
    Serial.println("-- HttpRequest -- connection failed");
  }
  return "";
}
