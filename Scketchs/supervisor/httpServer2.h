#include <ESP8266WiFi.h>

extern WiFiServer httpServer;
extern cDataTable DT;
extern DHFile Config;

String LastPage;

void S_header( WiFiClient &client);
void S_page0( WiFiClient &client);
void S_page1( WiFiClient &client);
void S_page2( WiFiClient &client);
void S_page3( WiFiClient &client);
void S_page4( WiFiClient &client);
void S_page5( WiFiClient &client, JsonObject& json );

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
  if (!client)
  {
    return false;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  int i = 0;
  while (!client.available())
  {
    delay(1);
    i++;
    if (i > 1000) return false;
  }

  // Read the first line of the request
  String readString = client.readStringUntil('\r');
  Serial.println(readString);
  client.flush();

  // Match the request
  int value = 0;
  if (readString.indexOf("/set?") != -1)
  {
    int idxSET = readString.indexOf("/set?");
    int idxSET2 = readString.indexOf("=", idxSET);

    String name = readString.substring(idxSET + 5, idxSET2);
    String val = readString.substring(idxSET2 + 1, 999);

    Serial.println(name);
    Serial.println(val);
    DT.setPars( name, val );

    readString = LastPage;
  }

  if (readString.indexOf("/page0") != -1)
  {
    S_header( client );
    S_page0( client );
  }
  else if (readString.indexOf("/page1") != -1)
  {
    S_header( client );
    S_page1( client );
  }
  else if (readString.indexOf("/page2") != -1)
  {
    S_header( client );
    S_page2( client );
  }
  else if (readString.indexOf("/page3") != -1)
  {
    S_header( client );
    S_page3( client );
  }
  else if (readString.indexOf("/page4") != -1)
  {
    S_header( client );
    S_page4( client );
  }
  else if (readString.indexOf("/page5") != -1)
  {
    JsonObject& root = Config.root();
    S_header( client );
    S_page5( client, root );
  }
  else
  {
    readString = "/page1";
    S_header(  client );
    S_page1( client );
  }

  LastPage = readString;
  return true;
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
         "<meta http-equiv='refresh' content='10';url='http://192.168.0.201/' >"
         "<title>Home</title>"
         "\n<script>"
         "function myButton( str )"
         "{"
         "window.location='http://192.168.0.201/set?' + str;"
         "}"
         "</script>"
         // <!-- define on/off styles -->
         "\n<style type='text/css'>"
         ".on  { background:yellow; }"
         ".off { background:gray; }"
         ".fon { background:blue; }"
         ".foff { background:red; }"
         ".fdis { background:gray; }"
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
         "font-size:160%;}"
         "p  {"
         "color:red;"
         "font-family:verdana;"
         "font-size:160%;}"
         "a  {"
         "font-family:verdana;"
         "font-size:120%;}"
         "table, th, td {"
         "border: 1px solid black;"
         "border-collapse: collapse;}"
         "th, td {"
         "padding: 5px;"
         "text-align: cnter;}"
         "</style>";
  client.println(page);
  //***************************************************************************************************************/

  page =  "\n<body>"
          "<p><title> Home</span></title></p>";
  client.println(page);
  //***************************************************************************************************************/
}

void S_page0( WiFiClient &client)
{
  String page;
  //***************************************************************************************************************/
  page =  "<h2><a href=page1> Stanze </a></h2>"
          "\n<h1> Programmi </h1>"
          "<table>"
          "<tbody>"
          "<tr>"
          "<th>Stanze"
          "<th>Stato"
          "<th>Forzato"
          "</tr>";
  client.println(page);
  //***************************************************************************************************************/

  page = "\n<tr>";
  page += DT.progBoilerSanitaria.td_descr();
  page += DT.progBoilerSanitaria.td_bulb();
  page += DT.progBoilerSanitaria.td_star();
  page += "</tr>";
  client.println(page);
  //***************************************************************************************************************/

  page =  "</tbody>"
          "</table>"  ;
  client.println(page);
  //***************************************************************************************************************/
}

void S_page1( WiFiClient &client)
{
  String page;
  //***************************************************************************************************************/
  page =  "<h2><a href=page0> Programmi </a> | <a href=page2> Attuatori </a></h2>"
          "\n<h1> Stanze </h1>"
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
      page += "<td><button onclick='myButton(\"" + req_p + "\")'> UP </button></td>";

      page += DT.webVar[i]->td_setpointF();

      String req_m = DT.webVar[ i]->descrSetPoint() + "=" + String(DT.webVar[ i]->setPoint() - 0.5 );
      page += "<td><button onclick='myButton(\"" + req_m + "\")'> DW </td>";

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


void S_page2( WiFiClient &client)
{
  String page;
  //***************************************************************************************************************/
  page =  "<h2><a href=page1> Stanze </a> | <a href=page3> Caldaia </a></h2>"
          "\n<h1> Attuatori Pavimento </h1>"
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
  if (DT.rPdc == true)
    page += DT.rPdc.td_bulb();
  else
    page += DT.rPompaPianoPrimo.td_bulb();
  page += "</tr>";
  for (int i = 0; i < 10; i++)
  {
    if (DT.webVar[50 + i])
    {
      page += "\n<tr>";
      page += DT.webVar[50 + i]->td_descr();
      page += DT.webVar[50 + i]->td_bulb();
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
  for (int i = 0; i < 10; i++)
  {
    if (DT.webVar[30 + i])
    {
      page += "\n<tr>";
      page += DT.webVar[30 + i]->td_descr();
      page += DT.webVar[30 + i]->td_bulb();
      if ( DT.webVar[30 + i] )
        page += DT.webVar[30 + i]->td_star();
      page += "</tr>";
    }
  }
  page += "  </tbody>";
  page += "</table>";
  client.println(page);
  //***************************************************************************************************************/
}

void S_page3( WiFiClient &client)
{
  String page;
  //***************************************************************************************************************/
  page += "<h2><a href=page2> Attuatori </a> | <a href=page4> Log </a></h2>"
          "\n<h1> Caldaia </h1>"
          "<table>"
          "<tbody>"
          "<tr>"
          "<th>Sonda"
          "<th>Temperatura"
          "</tr>";
  client.println(page);
  //***************************************************************************************************************/
  page = "";
  for (int i = 0; i < 10; i++)
  {
    if (DT.webVar[40 + i])
    {
      page += "\n<tr>";
      page += DT.webVar[40 + i]->td_descr();
      page += DT.webVar[40 + i]->td_valueF();
      page += "</tr>";
    }
  }
  page += "</tbody>"
          "</table>";
  //***************************************************************************************************************/
  client.println(page);
}

void S_page4( WiFiClient& client)
{
  String page;
  page = "<h2><a href=page3><<--</a>|<a href=page5>Json</a></h2>"
         "\n<h1> Log </h1>";
  client.println(page);
  //***************************************************************************************************************/
  for (int i = 0; i < 60; i++)
    client.println( DT.m_log.get(i) + "<br>" );

  //json.prettyPrintTo(client);
}

void S_page5( WiFiClient& client, JsonObject& json)
{
  String page;
  page = "<h2><a href=page4> Log </a>|</h2>"
         "\n<h1> Json </h1>";
  client.println(page);
  //***************************************************************************************************************/

  json.prettyPrintTo(client);
}
