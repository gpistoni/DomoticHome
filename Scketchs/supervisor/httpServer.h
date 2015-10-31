extern WiFiServer httpServer;
extern cDataTable DT;

void initHttpServer()
{
  httpServer.begin();
  Serial.println("HTTP server started");
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
}

void handleHttpServer()
{
  // Check if a client has connected
  WiFiClient client = httpServer.available();
  if (!client)
  {
    return;
  }

  // Wait until the client sends some data
  Serial.println("new client");
  while (!client.available())
  {
    delay(1);
  }

  // Read the first line of the request
  String readString = client.readStringUntil('\r');
  Serial.println(readString);
  client.flush();

  // Match the request
  int value = 0;
  if (readString.indexOf("/set") != -1)
  {
    int idxSET = readString.indexOf("/set?");
    int idxSET2 = readString.indexOf("=", idxSET);

    String name = readString.substring(idxSET + 5, idxSET2);
    String val = readString.substring(idxSET2 + 1, 999);

    Serial.println(name);
    Serial.println(val);
    DT.setPars( name, val );    
  }
  if (readString.indexOf(" / LED = OFF") != -1)
  {
    value = 2;
  }

  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");

  ///********************************************************************************************
  // message
  String message;
  message = "Led pin is now: ";

  if (value == HIGH)
  {
    message += "On";
  }
  else
  {
    message += "Off";
  }
  message += "<br><br>";
  message += "Click <a href=\"/set?ptCucina=20\">here</a> turn the LED on pin 2 ON<br>";
  message += "Click <a href=\"/set?ptCucina=22\">here</a> turn the LED on pin 2 OFF<br>";
  message += "</html>";

  client.println(message);

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
