
extern ESP8266WebServer webServer;
extern cDataTable DT;


void handleRoot()
{
  webServer.send(200, "text/plain", "hello from esp8266! Usage: \n /log   Output logfile \n state \n /values \n /labels ");
}

void handleLog()
{
  webServer.send(200, "text/plain", "logfile");
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

void HtmlPage();

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

  webServer.on("/print", handlePrint );
  webServer.onNotFound(handleNotFound);
  webServer.begin();
  Serial.println("HTTP server started");
}

//***************************************************************************************************
void HtmlPage()
{
  String page = "<!DOCTYPE html><html xmlns='http://www.w3.org/1999/xhtml' dir='ltr'>"
"<head>"
"  <meta http-equiv='content-type' content='text/html; charset=iso-8859-1' />"
"  <title>Home</title>"
"</head>"
"<body>"
"<p><title> Home</span></title></p>"
"<p><span style='font-family: Arial,Helvetica,sans-serif'>Stanze"

"<table border='3' style='width: 100%'>"
"  <tbody>"
"    <tr>"
"      <td>Stanza</td>"
"      <td>Temperatura</td>"
"      <td>Umidità</td>"
"      <td>Target</td>"
"      <td></td>"
"    </tr>";

for (int i=0; i<6; i++)
{
page +="    <tr>";
page +="      <td>" + DT.webVar[10+i]->m_descr + "</td>";
page +="      <td>#t</td>";
page +="      <td>#u</td>";
page +="      <td>#p</td>";
page +="      <td>+-</td>";
page +="    </tr>";
}
"  </tbody>"
"</table>"
"</span></p>"
"</body>"
"</html>";
  webServer.send(200, "text/html", page); 
  }
