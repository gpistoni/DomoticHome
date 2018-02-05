#include <ESP8266WiFi.h>
//#include <page1.html.h>

extern WiFiServer httpServer;
extern cDataTable DT;
extern DHFile Config;

String LastPage;

void S_header( WiFiClient &client);
void S_page_progs( WiFiClient &client);
void S_page_rooms( WiFiClient &client);
void S_page_amp( WiFiClient &client);
void S_page2( WiFiClient &client);
void S_page3( WiFiClient &client);
void S_page_log( WiFiClient &client);
void S_page_json( WiFiClient &client, JsonObject& json );

//void handlePage1() {
// String s = HTML_page1; //Read HTML contents
// server.send(200, "text/html", s); //Send web page
//}

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
  //Serial.println("new client");
  int i = 0;
  if (!client.available())
  {

    // Read the first line of the request
    String readString = client.readStringUntil('\r');
    //Serial.println(readString);
    client.flush();

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
    }

    if (readString.indexOf("/page_progs") != -1)
    {
      S_header( client );
      S_page_progs( client );
    }
    else if (readString.indexOf("/page_rooms") != -1)
    {
      S_header( client );
      S_page_rooms( client );
    }
    else if (readString.indexOf("/page_amp") != -1)
    {
      S_header( client );
      S_page_amp( client );
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
    else if (readString.indexOf("/page_log") != -1)
    {
      S_header( client );
      S_page_log( client );
    }
    else if (readString.indexOf("/page_json") != -1)
    {
      JsonObject& root = Config.root();
      S_header( client );
      S_page_json( client, root );
    }
    else
    {
      readString = "/page1";
      S_header(  client );
      S_page_rooms( client );
    }
      LastPage = readString;
      return true;
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
         "<meta http-equiv='refresh' content='4';url='http://192.168.1.201/' >"
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

String Menu()
{
  String page;
  //***************************************************************************************************************/
  page = "<h3><a href=page_progs> Programmi </a> |"
         "<a href=page_rooms> Stanze </a> |"
         "<a href=page_amp> Consumi </a> |"
         "<a href=page2> Attuatori </a> |"
         "<a href=page3> Caldaia </a> |"
         "<a href=page_log> Log </a> |"
         //    "<a href=page_json> Json </a> |"
         "</h3>";
  return page;
}


void S_page_progs( WiFiClient &client)
{
  String page = Menu();
  //***************************************************************************************************************/
  page +=  "\n<h2> Programmi </h1>"
           "<table>"
           "<tbody>"
           "<tr>"
           "<th>Stanze"
           "<th>Stato"
           "<th>Manual"
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

void S_page_rooms( WiFiClient &client)
{
  String page = Menu();
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

void S_page_amp( WiFiClient &client)
{
  String page = Menu();
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
           "<th>Euro"
           "<th>"
           "</tr>";
  client.println(page);
  //***************************************************************************************************************/

  page = "";
  for (int i = 60; i <= 65; i++)
  {
    if ( DT.webVar[i] )
    {
      float a = DT.webVar[i]->value();
      float wh = DT.webVar[8 + i]->value();
      float t = DT.webVar[16 + i]->value();

      page += "\n<tr>";
      page += DT.webVar[i]->td_descr();         // descr
      page += String("<td>") + a;               // A
      page += String("<td>") + a * 233;         // W
      page += String("<td>") + wh;              // KWH
      page += String("<td>") + t;               // time
      page += String("<td>") + wh * 0.22;
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
  String page = Menu();
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

  if (DT.rPdc == true)
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

void S_page3( WiFiClient &client)
{
  String page = Menu();
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

void S_page_log( WiFiClient& client)
{
  String page  = Menu();
  page += "\n<h1> Log </h1>";

  client.println(page);
  client.println( DT.m_log.getHTML1() );
  client.println( DT.m_log.getHTML2() );

  //***************************************************************************************************************/
}

void S_page_json( WiFiClient& client, JsonObject& json)
{
  String page  = Menu();
  page += "\n<h1> Json </h1>";

  client.println(page);
  json.prettyPrintTo(client);
  //***************************************************************************************************************/

}
