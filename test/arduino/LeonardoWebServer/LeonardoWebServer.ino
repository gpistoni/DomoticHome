// web server di interfaccia
// uso:
// http://172.31.11.175/@set(1,12=0)@get(4,23)

//#include <SoftwareSerial.h>
#include <SPI.h>
//#include <SD.h>
#include <Ethernet.h>


// MAC address for the ethernet controller.  -----------------------------
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xEE };

// IP address for the controller:  -----------------------------
IPAddress ip(172, 31, 11, 175);                       //<<-- IP
IPAddress gateway(172, 31, 8, 1);                     //<<-- GATEWAY
IPAddress subnet(255, 255, 255, 0);                   //<<-- SUBNET

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);

//SD      -----------------------------
#define SD_SELECT 4
const char *filename = "/net.ini";

//TRACING -----------------------------
#define TRACE(x) Serial.println(x)
//#define TRACE(x)

//-----------------------------
void setup()
{
  Serial.begin(9600);
  while (!Serial);
  TRACE("start!");

  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();

  // give the sensor and Ethernet shield time to set up:
  delay(1000);

  TRACE("server is at ");
  TRACE(Ethernet.localIP());

  //inifile ************************************************************
  /*
  TRACE("Initializing SD card...");
  if (!SD.begin(4))
  {
    Serial.println("initialization failed!");
    return;
  }
  TRACE("initialization done.");

  //write......
  File myFile;
  myFile = SD.open("test.txt", FILE_WRITE );
  if (myFile)
  {
    myFile.seek(0);
    myFile.write("var1=0");
    myFile.write("var2=1");
  }
  myFile.close();

  //read......
  myFile = SD.open("test.txt");
  if (myFile)
  {
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
  }
  myFile.close();
*/
}


//-----------------------------
void loop()
{
  delay(10);

  // listen for incoming Ethernet connections:
  listenForEthernetClients();
}

String readString;

void listenForEthernetClients()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client)
  {
    TRACE("Got a client");

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected())
    {
      if (client.available())
      {
        // Read the received command sent from client
        char c = client.read();
        if (readString.length() < 50 )
        {
          readString = readString + c;
        }

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n')
        {
          TRACE( readString.c_str() );
          //*************************************
          // comandi speciali
          int idx = readString.indexOf("@debug");
          if (idx > 0)
          {
            client.println("ALL CLIENT");
            break;
          }
          //*************************************
          int idxGET = readString.indexOf("@get(");
          int idxGET2 = readString.indexOf(",", idxGET);
          int idxGET3 = readString.indexOf(")", idxGET2);

          int GetParam[2] = {0, 0};
          GetParam[0] = readString.substring(idxGET + 5, idxGET2).toInt();
          GetParam[1] = readString.substring(idxGET2 + 1, idxGET3).toInt();

          int idxSET = readString.indexOf("@set(");
          int idxSET2 = readString.indexOf(",", idxSET);
          int idxSET3 = readString.indexOf("=", idxSET2);
          int idxSET4 = readString.indexOf(")", idxSET3);

          int SetParam[3] = {0, 0, 0};
          SetParam[0] = readString.substring(idxSET + 5, idxSET2).toInt();
          SetParam[1] = readString.substring(idxSET2 + 1, idxSET3).toInt();
          SetParam[2] = readString.substring(idxSET3 + 1, idxSET4).toInt();

          TRACE( "Get:" + String(GetParam[0]) + "," + String(GetParam[1]) );
          TRACE( "Set:" + String(SetParam[0]) + "," + String(SetParam[1]) + "=" + String(SetParam[2]) );

          //*************************************
          // client.println("HTTP/1.1 200 OK");
          // client.println("Content-Type: text/html");
          // client.println("Connection: close");        // the connection will be closed after completion of the response
          // client.println("Refresh: 1");               // refresh the page automatically every 5 sec

          client.println("100");

          //***************************************
          break;
        }
      }
    }

    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    readString = "";
    client.stop();
    TRACE("client disconnected");
  }
}


