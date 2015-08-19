#include <FileIO.h>
#include <DHT.h>
#include <OneWire.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>

#include <dhprotocol.h>

DHProtocol T2;
DHProtocol T3;
DHProtocol T4;
DHProtocol T5;

SoftwareSerial mySerial(10, 12, TRUE);  //RX, TX, inverse logic


byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 177);
EthernetServer server(80);

void setup()
{ 
  T2.setup(0, 2, &mySerial, 9600);  // nc
  T3.setup(0, 3, &mySerial, 9600);  // rele pdc
  T4.setup(0, 4, &mySerial, 9600);  // temp caldaie
  T5.setup(0, 5, &mySerial, 9600);  // rele pavimento

  Serial.begin(9600);
  Serial.println("System Start");

  /*
   Ethernet.begin(mac, ip);
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  */
    
}

unsigned long old_Update[10] = {-1000, -1000, -1000, 0, 0, 0, 0, 0, 0, 0};
int count = 0;

void loop()
{
  unsigned long now = millis();
  count++;
  Serial.println("");
  Serial.print(now);
  if ( now - old_Update[3] >= 5000)
  {
    old_Update[3] = now;

    T3.relay[0] = 0;
    T3.relay[1] = 0;
    T3.relay[2] = 1;
    T3.relay[3] = 1;
    T3.relay[4] = 0;
    T3.relay[5] = 0;
    T3.relay[6] = 0;
    T3.relay[7] = 0;
    T3.sendRequest();
    T3.waitData( 100 );
  };
  if ( now - old_Update[4] >= 4000)
  {
    old_Update[4] = now;

    T4.relay[0] = 0;
    T4.relay[1] = 0;
    T4.relay[2] = 0;
    T4.relay[3] = 0;
    T4.relay[4] = 0;
    T4.relay[5] = 0;
    T4.relay[6] = 0;
    T4.relay[7] = 0;
    T4.sendRequest();
    T4.waitData( 100 );
  };
  if ( now - old_Update[5] >= 10000)
  {
    old_Update[5] = now;

    T5.relay[0] = 0;
    T5.relay[1] = 0;
    T5.relay[2] = 1;
    T5.relay[3] = 0;
    T5.relay[4] = 0;
    T5.relay[5] = 0;
    T5.relay[6] = 0;
    T5.relay[7] = 0;
    T5.sendRequest();
    T5.waitData( 100 );
  };
/*
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            client.print(sensorReading);
            client.println("<br />");
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
*/

  delay(200);
}


