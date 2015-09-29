
extern ESP8266WebServer webServer;
extern cDataTable DT;

void handleRoot()
{
  webServer.send(200, "text/plain", "hello from esp8266! Usage: \n /log   Output logfile");
}

void handleLog()
{
  webServer.send(200, "text/plain", "logfile");
}

void handleValues()
{
  String lab, val;
  DT.enumerate( lab, val );
  webServer.send(200, "text/plain", val);
}

void handleLabels()
{
  String lab, val;
  DT.enumerate( lab, val );
  webServer.send(200, "text/plain", lab);
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += webServer.uri();
  message += "\nMethod: ";
  message += (webServer.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += webServer.args();
  message += "\n";
  
  for (uint8_t i=0; i<webServer.args(); i++)
  {
    message += " " + webServer.argName(i) + ": " + webServer.arg(i) + "\n";
  }
  webServer.send(404, "text/plain", message);
}
