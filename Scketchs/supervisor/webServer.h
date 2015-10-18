
extern ESP8266WebServer webServer;
extern cDataTable DT;

void HtmlPage();
void handleRoot()
{
  webServer.send(200, "text/plain", "hello from esp8266! Usage: \n /log   Output logfile \n state \n /values \n /labels ");
}

void handleLog()
{
  webServer.send(200, "text/plain",    DT.m_log.get() );
}

void handleValues()
{
  String lab, val;
  DT.enumerateVals( lab, val );
  webServer.send(200, "text/plain", val);
}

void handleLabels()
{
  String lab, val;
  DT.enumerateVals( lab, val );
  webServer.send(200, "text/plain", lab);
}

void handlePars()
{
  String lab, val;
  DT.enumeratePars( lab, val );
  webServer.send(200, "text/plain", val);
}

void handleLabelsPars()
{
  String lab, val;
  DT.enumeratePars( lab, val );
  webServer.send(200, "text/plain", lab);
}

void handleSetPars()
{
  String message;
  for (uint8_t i = 0; i < webServer.args(); i++)
  {
    String name = webServer.argName(i);
    String val = webServer.arg(i);
    DT.setPars( name, val );
    message += " " + webServer.argName(i) + ": " + webServer.arg(i) + "\n";
  }
  webServer.send(200, "text/plain", message);
}

void handleSet()
{
  String message;
  for (uint8_t i = 0; i < webServer.args(); i++)
  {
    String name = webServer.argName(i);
    String val = webServer.arg(i);
    DT.setPars( name, val );
  }
  HtmlPage();
}

void handlePrint()
{
  String labl;
  DT.print( labl );
  labl = labl + "\n\n------------------------------------ \n" + DT.m_log.get();
  webServer.send(200, "text/plain", labl );
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += webServer.uri();
  message += "\nMethod: ";
  message += (webServer.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += webServer.args();
  message += "\n";

  for (uint8_t i = 0; i < webServer.args(); i++)
  {
    message += " " + webServer.argName(i) + ": " + webServer.arg(i) + "\n";
  }
  webServer.send(404, "text/plain", message);
}

//***************************************************************************************************
void initWebserver()
{
  webServer.on("/", HtmlPage );
  webServer.on("/log", handleLog );
  webServer.on("/values", handleValues );
  webServer.on("/labels", handleLabels );

  webServer.on("/pars", handlePars );
  webServer.on("/labpars", handleLabelsPars );
  webServer.on("/setpars", handleSetPars );
  webServer.on("/set", handleSet );

  webServer.on("/print", handlePrint );
  webServer.onNotFound(handleNotFound);
  webServer.begin();
  Serial.println("HTTP server started");
}



//***************************************************************************************************
void HtmlPage()
{
  Serial.println("HtmlPage");
  String page;
  page += "<!DOCTYPE html><html xmlns='http://www.w3.org/1999/xhtml' dir='ltr'>"
          "<head>"
          "<meta http-equiv='refresh' content='30'>"
          "  <title>Home</title>"
          "</head>";
  page += "<style>"
          "body {"
          "    font-family:verdana;"
          "    font-size:120%;"
          "}"
          "h1 {"
          "    color:blue;"
          "    font-family:verdana;"
          "    font-size:160%;"
          "}"
          "p  {"
          "    color:red;"
          "    font-family:verdana;"
          "    font-size:160%;"
          "}"
          "a  {"
          "    font-family:verdana;"
          "    font-size:120%;"
          "}"
          "table, th, td {"
          "border: 1px solid black;"
          "border-collapse: collapse;"
          "}"
          "th, td {"
          "    padding: 5px;"
          "    text-align: cnter;"
          "}"
          "</style>";
  //***************************************************************************************************************/
  page +=  "<body>"
           "<p><title> Home</span></title></p>";
  //***************************************************************************************************************/
  Serial.println("Stanze");
  page +=  "\n<h1> Stanze </h1>"
           "<table>"
           "  <tbody>"
           "    <tr>"
           "      <th>Stanza</th>"
           "      <th>Temperatura</th>"
           "      <th>Umidita</th>"
           "      <th></th>"
           "      <th>Target</th>"
           "      <th></th>"
           "    </tr>";
  for (int i = 0; i < 6; i++)
  {
    if ( DT.webVar[10 + i] && DT.webVar[i] && DT.webParam[10 + i] )
    {
      page += "    \n<tr>";
      page += DT.webVar[10 + i]->td_descr();
      page += DT.webVar[10 + i]->td_valueF();
      page += DT.webVar[i]->td_valueF();

      String href_p = "'http://192.168.0.201/set?" + DT.webParam[10 + i]->m_descr + "=" + String(DT.webParam[10 + i]->m_value + 0.5 ) + "'";
      String href_m = "'http://192.168.0.201/set?" + DT.webParam[10 + i]->m_descr + "=" + String(DT.webParam[10 + i]->m_value - 0.5 ) + "'";
      page += "      <td><a href=" + href_p + "> <img " + srcIcon("arrow_up") + " alt='+' >  </a> </td>";
      page += DT.webParam[10 + i]->td_valueF();
      page += "      <td><a href=" + href_m + "> <img " + srcIcon("arrow_down") + " alt='-' >  </a> </td>";

      page += "    </tr>";
    }
  }
  page +=  "  </tbody>"
           "</table>";
  //***************************************************************************************************************/
  Serial.println("Caldaia");
  page +=  "\n<h1> Caldaia </h1>"
           "<table>"
           "  <tbody>"
           "    <tr>"
           "      <th>Sonda</th>"
           "      <th>Temperatura</th>"
           "    </tr>";
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
  page += "  </tbody>"
          "</table>";
  //***************************************************************************************************************/
  Serial.println("Pavimento");
  page +=  "\n<h1> Attuatori Pavimento </h1>"
           "<table>"
           "  <tbody>"
           "    <tr>"
           "      <th>Stanze</th>"
           "      <th>Stato</th>"
           "    </tr>";
  page += "\n<tr>"
          "<td>Bagno</td>";
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
  //***************************************************************************************************************/
  Serial.println("Attuatori");
  page +=  "\n<h1> Attuatori Caldaia </h1>"
           "<table>"
           "  <tbody>"
           "    <tr>"
           "      <th>Stanze</th>"
           "      <th>Stato</th>"
           "      <th>Forzato</th>"
           "    </tr>";
  for (int i = 0; i < 10; i++)
  {
    if (DT.webVar[30 + i])
    {
      page += "\n<tr>";
      page += DT.webVar[30 + i]->td_descr();
      page += DT.webVar[30 + i]->td_bulb();
     // if ( DT.webParam[30 + i] )
     //   page += DT.webParam[30 + i]->td_star();
      page += "</tr>";
    }
  }
  page += "  </tbody>";
  page += "</table>";
  //***************************************************************************************************************/
  page += "</body>";
  page += "</html>";
  Serial.println("send Page");
  webServer.send(200, "text/html", page);
}
/*

void HtmlPage() {
  String out = "";
  char temp[100];
  out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"400\" height=\"150\">\n";
  out += "<rect width=\"400\" height=\"150\" fill=\"rgb(250, 230, 210)\" stroke-width=\"1\" stroke=\"rgb(0, 0, 0)\" />\n";
  out += "<g stroke=\"black\">\n";
  int y = rand() % 130;
  for (int x = 10; x < 390; x += 10) {
    int y2 = rand() % 130;
    sprintf(temp, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke-width=\"1\" />\n", x, 140 - y, x + 10, 140 - y2);
    out += temp;
    y = y2;
  }
  out += "</g>\n</svg>\n";

  webServer.send ( 200, "image/svg+xml", out);
}
*/
