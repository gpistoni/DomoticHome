#include <ESP8266WiFi.h>

extern WiFiServer httpServer;
extern cDataTable DT;
extern DHFile Config;

String LastPage;

String Menu();
void S_header( WiFiClient &client);
void S_page_progs( WiFiClient &client, String page);
void S_page_rooms( WiFiClient &client, String page);
void S_page_amp( WiFiClient &client, String page);
void S_page_valves( WiFiClient &client , String page);
void S_page_probes( WiFiClient &client, String page);
void S_page_log( WiFiClient &client, String page);
void S_page_json( WiFiClient &client, JsonObject& json, String page );
void S_page_all( WiFiClient &client);
String Menu();

void initHttpServer()
{
  httpServer.begin();
  Serial.println("HTTP server started");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

bool handleHttpServer()
{
  // Check if a client has connected
  WiFiClient client = httpServer.available();
  if (client)
  {
    // Wait until the client sends some data
    if (client.available())
    {
      // Read the first line of the request
      String readString = client.readStringUntil('\r');

      Serial.println("New Request:" +  readString);
      // Match the request
      int value = 0;
      if (readString.indexOf("/set?") != -1)
      {
        int idxSET = readString.indexOf("/set?");
        int idxSET2 = readString.indexOf("=", idxSET);
        String name = readString.substring(idxSET + 5, idxSET2);
        String val = readString.substring(idxSET2 + 1, 999);

        //Serial.println(name);
        //Serial.println(val);
        DT.setPars( name, val );
        readString = LastPage;
        S_page_all(client);
      }
      else if (readString.indexOf("/get?") != -1)
      {
        int idxGET = readString.indexOf("/get?");
        int idxGET2 = readString.indexOf(" ", idxGET);

        String name = readString.substring(idxGET + 5, idxGET2);

        Serial.println(name + "--");
        float val = DT.getValue( name );
        client.println(val);
        readString = LastPage;
      }
      else if (readString.indexOf("/progs") != -1)
      {
        S_header( client );
        S_page_progs( client , Menu() );
      }
      else if (readString.indexOf("/rooms") != -1)
      {
        S_header( client );
        S_page_rooms( client , Menu() );
      }
      else if (readString.indexOf("/amp") != -1)
      {
        S_header( client );
        S_page_amp( client , Menu() );
      }
      else if (readString.indexOf("/valves") != -1)
      {
        S_header( client );
        S_page_valves( client , Menu() );
      }
      else if (readString.indexOf("/probes") != -1)
      {
        S_header( client );
        S_page_probes( client , Menu() );
      }
      else if (readString.indexOf("/log") != -1)
      {
        S_header( client );
        S_page_log( client , Menu() );
      }
      else if (readString.indexOf("/json") != -1)
      {
        JsonObject& root = Config.root();
        S_header( client );
        S_page_json( client, root, Menu()  );
      }
      else if (readString.indexOf("/favicon.ico") != -1)
      {
        client.println(0);
      }
      else
      {
        S_page_all(client);
      }

      LastPage = readString;
      return true;
    }
    delay(10);
    client.stop();
  }
  return false;
}

void S_header( WiFiClient &client)
{
  String page;
  page = "HTTP/1.1 200 OK"
         "Content-Type: text/html";
  client.println(page);
  client.println(""); //  do not forget this one
  page = "<!DOCTYPE html><html xmlns='http://www.w3.org/1999/xhtml' dir='ltr'>"
         "<head>"
         "<meta http-equiv='refresh' content='10';url='http://192.168.1.201/' >"
         "<meta http-equiv='Pragma' content='no-cache'>"
         "<title>Home</title>"
         "\n<script>"
         "function myButton( str )"
         "{"
         "window.location='http://192.168.1.201/set?' + str;"
         "}"
         "</script>"
         // <!-- define on/off styles -->
         "\n<style type='text/css'>"
         ".on  { background:yellow; }"
         ".off { background:gray; }"
         ".fon { background:lightgreen; }"
         ".foff { background:red; }"
         ".fdis { background:lightyellow; }"
         "</style>"
         "</head>";
  client.println(page);
  //***************************************************************************************************************/

  page = "\n<style>"
         "body {"
         "font-family:verdana;"
         "font-size:120%;}"
         "h1 {"
         "color:blue;"
         "font-family:verdana;"
         "font-size:120%;}"
         "p  {"
         "color:red;"
         "font-family:verdana;"
         "font-size:160%;}"
         "a  {"
         "font-family:verdana;"
         "font-size:110%;}"
         "table, th, td {"
         "border: 1px solid black;"
         "border-collapse: collapse;}"
         "th, td {"
         "padding: 4px;"
         "text-align: center;}"
         "</style>";
  client.println(page);
  //***************************************************************************************************************/

  page =  "\n<body>"
          "<p><title> Home</span></title></p>";
  client.println(page);
  //***************************************************************************************************************/
}

String Menu()
{
  String page;
  //***************************************************************************************************************/
  page = "<h3><a href=progs> Programmi </a> |"
         "<a href=rooms> Stanze </a> |"
         "<a href=amp> Consumi </a> |"
         "<a href=valves> Attuatori </a> |"
         "<a href=probes> Caldaia </a> |"
         "<a href=log> Log </a> |"
         "<a href=json> Json </a> |"
         "</h3>";
  return page;
}

void S_page_progs( WiFiClient &client, String page)
{
  //***************************************************************************************************************/
  page +=  "\n<h1> Programmi </h1>"
           "<table>"
           "<tbody>"
           "<tr>"
           "<th>Programma"
           "<th>Stato"
           "<th>Set"
           "</tr>";
  client.println(page);

  //***************************************************************************************************************/
  for (int i = 90; i < 99; i++)
  {
    if ( DT.webVar[i] )
    {
      page = "\n<tr>";
      page += DT.webVar[i]->td_descr();
      page += DT.webVar[i]->td_bulb();
      page += DT.webVar[i]->td_star();
      page += "</tr>";
      client.println(page);
    }
  }
  //***************************************************************************************************************/

  page =  "</tbody>"
          "</table>"  ;
  client.println(page);
  //***************************************************************************************************************/
}

void S_page_rooms( WiFiClient &client, String page)
{
  /***************************************************************************************************************/
  page +=  "\n<h1> Stanze </h1>"
           "<table>"
           "<tbody>"
           "<tr>"
           "<th>Stanza"
           "<th>Temperatura"
           "<th>Umidita"
           "<th>TPercepita"
           "<th>"
           "<th>Target"
           "<th>"
           "</tr>";
  client.println(page);
  //***************************************************************************************************************/

  page = "";
  for (int i = 0; i < 8; i++)
  {
    if ( DT.webVar[i] )
    {
      page += "\n<tr>";
      page += DT.webVar[i]->td_descr();
      page += DT.webVar[i]->td_valueF();
      page += DT.webVar[8 + i]->td_valueF();
      page += DT.webVar[16 + i]->td_valueF();

      String req_p = DT.webVar[i]->descrSetPoint() + "=" + String(DT.webVar[i]->setPoint() + 0.5 );
      page += "<td><button onclick='myButton(\"" + req_p + "\")'> -UP- </button></td>";

      page += DT.webVar[i]->td_setpointF();

      String req_m = DT.webVar[i]->descrSetPoint() + "=" + String(DT.webVar[i]->setPoint() - 0.5 );
      page += "<td><button onclick='myButton(\"" + req_m + "\")'> -DW- </td>";
      page += "</tr>";
    }
  }
  client.println(page);
  //***************************************************************************************************************/

  page =  "</tbody>"
          "</table>"  ;
  client.println(page);
  //***************************************************************************************************************/
}

void S_page_amp( WiFiClient &client, String page)
{
  /***************************************************************************************************************/
  page +=  "\n<h1> Consumi </h1>"
           "<table>"
           "<tbody>"
           "<tr>"
           "<th>Settore"
           "<th>Ampere"
           "<th>Watt"
           "<th>KWh"
           "<th>h"
           "<th>"
           "</tr>";
  client.println(page);
  //***************************************************************************************************************/

  page = "";
  for (int i = 60; i <= 65; i++)
  {
    if ( DT.webVar[i] )
    {
      float a = DT.webVar[i]->val();
      float wh = DT.webVar[8 + i]->val();
      float t = DT.webVar[16 + i]->val();

      page += "\n<tr>";
      page += DT.webVar[i]->td_descr();         // descr
      page += String("<td>") + a;               // A
      page += String("<td>") + (int)(a * 233);         // W
      page += String("<td>") + wh;              // KWH
      page += String("<td>") + t;               // time
      page += "</tr>";
    }
  }
  page += "\n<tr>";
  page += String("<td>") + "Surplus";
  page += String("<td>");
  page += String("<td>") + DT.surplusWatt();
  page += String("<td>");
  page += String("<td>");
  page += "</tr>";
  client.println(page);
  //***************************************************************************************************************/

  page =  "</tbody>"
          "</table>"  ;
  client.println(page);
  //***************************************************************************************************************/
}


void S_page_valves( WiFiClient &client, String page)
{
  //***************************************************************************************************************/
  page +=  "\n<h1> Attuatori Pavimento </h1>"
           "<table>"
           "<tbody>"
           "<tr>"
           "<th>Stanze"
           "<th>Stato"
           "</tr>";
  client.println(page);
  //***************************************************************************************************************/
  page = "\n<tr>"
         "<td>Bagno</td>";

  if (DT.rPdc.val())
    page += DT.rPdc.td_bulb();
  else
    page += DT.rPompaPianoPrimo.td_bulb();
  page += "</tr>";

  for (int i = 50; i < 60; i++)
  {
    if (DT.webVar[i])
    {
      page += "\n<tr>";
      page += DT.webVar[i]->td_descr();
      page += DT.webVar[i]->td_bulb();
      page += "</tr>";
    }
  }
  page += "  </tbody>"
          "</table>";
  client.println(page);
  //***************************************************************************************************************/

  page =  "\n<h1> Attuatori Caldaia </h1>"
          "<table>"
          "<tbody>"
          "<tr>"
          "<th>Stanze"
          "<th>Stato"
          "<th>Forzato"
          "</tr>";
  client.println(page);
  //***************************************************************************************************************/
  page = "";
  for (int i = 30; i < 40; i++)
  {
    if (DT.webVar[i])
    {
      page += "\n<tr>";
      page += DT.webVar[i]->td_descr();
      page += DT.webVar[i]->td_bulb();
      page += DT.webVar[i]->td_star();
      page += "</tr>";
    }
  }
  page += "  </tbody>";
  page += "</table>";
  client.println(page);
  //***************************************************************************************************************/
  page =  "\n<h1> Attuatori Luci </h1>"
          "<table>"
          "<tbody>"
          "<tr>"
          "<th>Luci"
          "<th>Stato"
          "<th>Forzato"
          "</tr>";
  client.println(page);
  //***************************************************************************************************************/
  page = "";
  for (int i = 25; i < 30; i++)
  {
    if (DT.webVar[i])
    {
      page += "\n<tr>";
      page += DT.webVar[i]->td_descr();
      page += DT.webVar[i]->td_bulb();
      page += DT.webVar[i]->td_star();
      page += "</tr>";
    }
  }
  page += "</tbody>";
  page += "</table>";
  client.println(page);
  //***************************************************************************************************************/

}

void S_page_probes( WiFiClient &client, String page)
{
  //***************************************************************************************************************/
  page += "\n<h1> Caldaia </h1>"
          "<table>"
          "<tbody>"
          "<tr>"
          "<th>Sonda"
          "<th>Temperatura"
          "</tr>";
  client.println(page);
  //***************************************************************************************************************/
  page = "";
  for (int i = 40; i < 50; i++)
  {
    if (DT.webVar[i])
    {
      page += "\n<tr>";
      page += DT.webVar[i]->td_descr();
      page += DT.webVar[i]->td_valueF();
      page += "</tr>";
    }
  }
  page += "</tbody>"
          "</table>";

  client.println(page);
  //***************************************************************************************************************/
}

void S_page_log( WiFiClient& client, String page)
{
  page += "\n<h1> Log </h1>";

  client.println(page);
  client.println( DT.m_log.getHTML1() );
  client.println( DT.m_log.getHTML2() );

  //***************************************************************************************************************/
}

void S_page_json( WiFiClient& client, JsonObject& json, String page)
{
  page += "\n<h1> Json </h1>";

  //client.println(page);
  //json.prettyPrintTo(client);

  DT.print(page);
  client.println(page);
  //***************************************************************************************************************/

}

void S_page_all( WiFiClient &client)
{
  S_header( client );
  S_page_progs( client  , "");
  S_page_rooms( client  , "");
  S_page_amp( client  , "");
  S_page_valves( client  , "");
  S_page_probes( client  , "");
 // S_page_log( client  , "");
}
