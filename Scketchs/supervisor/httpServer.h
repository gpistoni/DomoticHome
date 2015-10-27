extern WiFiServer httpServer;
extern cDataTable DT;

void initHttpServer()
{
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
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();

  // Match the request
  int value = 0;
  if (req.indexOf("/set") != -1)
  {
    int idxSET = readString.indexOf("/set?");
    int idxSET2 = readString.indexOf("=", idxSET2);

    String name = readString.substring(idxSET + 5, idxSET2).toInt();
    float val = readString.substring(idxSET2 + 1, 999).toInt();

    Serial.println(name);
    Serial.println(val);
    DT.setPars( name, val );    
  }
  if (req.indexOf(" / LED = OFF") != -1)
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
  message += "Click <a href=\"/LED=ON\">here</a> turn the LED on pin 2 ON<br>";
  message += "Click <a href=\"/LED=OFF\">here</a> turn the LED on pin 2 OFF<br>";
  message += "</html>";

  client.println(message);

  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");

}
