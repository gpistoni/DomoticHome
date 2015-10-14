
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
  for (uint8_t i=0; i<webServer.args(); i++)
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
  webServer.send(200, "text/plain", labl );
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

//***************************************************************************************************
void initWebserver()
{
  webServer.on("/", handleRoot );
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

