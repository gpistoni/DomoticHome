//#include <ESP8266WiFi.h>
//
//extern WiFiServer httpServer;
//extern cDataTable DT;
//
//void page1( WiFiClient &client);
//  
//void initHttpServer()
//{
//  httpServer.begin();
//  Serial.println("HTTP server started");
//  Serial.print("Use this URL to connect: ");
//  Serial.print("http://");
//  Serial.print(WiFi.localIP());
//  Serial.println("/");
//}
//
//void handleHttpServer()
//{
//  // Check if a client has connected
//  WiFiClient client = httpServer.available();
//  if (!client)
//  {
//    return;
//  }
//
//  // Wait until the client sends some data
//  Serial.println("new client");
//  while (!client.available())
//  {
//    delay(1);
//  }
//
//  // Read the first line of the request
//  String readString = client.readStringUntil('\r');
//  Serial.println(readString);
//  client.flush();
//
//  // Match the request
//  int value = 0;
//  if (readString.indexOf("/set") != -1)
//  {
//    int idxSET = readString.indexOf("/set?");
//    int idxSET2 = readString.indexOf("=", idxSET);
//
//    String name = readString.substring(idxSET + 5, idxSET2);
//    String val = readString.substring(idxSET2 + 1, 999);
//
//    Serial.println(name);
//    Serial.println(val);
//    DT.setPars( name, val );
//  }
//  if (readString.indexOf(" / LED = OFF") != -1)
//  {
//    value = 2;
//  }
//
//  // Return the response
//
//  //client.println("<html>");
//
//  page1( client );
//  return;
//
//  ///********************************************************************************************
//  // message
//  String message;
//  message = "Led pin is now: ";
//
//  if (value == HIGH)
//  {
//    message += "On";
//  }
//  else
//  {
//    message += "Off";
//  }
//  message += "<br><br>";
//  message += "Click <a href=\"/set?ptCucina=20\">here</a> turn the LED on pin 2 ON<br>";
//  message += "Click <a href=\"/set?ptCucina=22\">here</a> turn the LED on pin 2 OFF<br>";
//  message += "</html>";
//
//  client.println(message);
//
//  delay(1);
//  Serial.println("Client disonnected");
//  Serial.println("");
//
//}
//
//void page1( WiFiClient &client)
//{
//  client.println("HTTP/1.1 200 OK");
//  client.println("Content-Type: text/html");
//  client.println(""); //  do not forget this one
//  client.println("<!DOCTYPE HTML>");
//  
//  String message = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>"
//
//                   "<svg id=\"svg2\" xmlns:rdf=\"http://www.w3.org/1999/02/22-rdf-syntax-ns#\" xmlns=\"http://www.w3.org/2000/svg\"  xmlns:osb=\"http://www.openswatchbook.org/uri/2009/osb\"  height=\"700\" width=\"600\" version=\"1.1\" xmlns:cc=\"http://creativecommons.org/ns#\" xmlns:xlink=\"http://www.w3.org/1999/xlink\" xmlns:dc=\"http://purl.org/dc/elements/1.1/\">"
//                   "<defs id=\"defs4\">""</defs>"
//                   "<metadata id=\"metadata7\">"
//                   "<rdf:RDF>"
//                   "<cc:Work rdf:about=\"\">"
//                   "<dc:format>image/svg+xml</dc:format>"
//                   "<dc:type rdf:resource=\"http://purl.org/dc/dcmitype/StillImage\"/>"
//                   "<dc:title/>"
//                   "</cc:Work>"
//                   "</rdf:RDF>"
//                   "</metadata>";
//  client.println(message);
//
//  message = "<script type=\"text/javascript\">"
//            "<![CDATA["
//            "var redVal=0;"
//            "var greenVal=0;"
//            "var blueVal=0;"
//            "function changeCol(evt)"
//            "{"
//            "   redVal = Math.round(Math.random()*255);"
//            "   greenVal = Math.round(Math.random()*255);"
//            "   blueVal = Math.round(Math.random()*255);"
//            "   evt.setAttribute(\"fill\", \"rgb(\" + redVal + \",\" + greenVal + \",\" + blueVal + \")\");"
//            "}"
//            "// ]]>"
//            "</script>";
//  client.println(message);
//
//  message = "<g id=\"layer1\" stroke-linejoin=\"round\" stroke=\"#000\" stroke-dasharray=\"none\" stroke-miterlimit=\"4\" stroke-width=\"1\" >"
//            "<rect id=\"rect1\" height=\"290\" width=\"250\"  y=\"0\"   x=\"0\"     fill=\"£1\" onclick=\"changeCol(this)\"/>"
//            "<rect id=\"rect2\" height=\"160\" width=\"250\"  y=\"0\"   x=\"260\"   fill=\"£2\" onclick=\"changeCol(this)\"/>"
//            "<rect id=\"rect3\" height=\"140\" width=\"250\"  y=\"300\" x=\"0\"     fill=\"£3\" onclick=\"changeCol(this)\"/>"
//            "<rect id=\"rect4\" height=\"200\" width=\"250\"  y=\"450\" x=\"0\"     fill=\"£4\" onclick=\"changeCol(this)\"/>"
//            "<rect id=\"rect5\" height=\"200\" width=\"250\"  y=\"450\" x=\"260\"   fill=\"£5\" onclick=\"changeCol(this)\"/>"
//            "<rect id=\"rect7\" height=\"140\" width=\"250\"  y=\"220\" x=\"310\"   fill=\"£6\" onclick=\"changeCol(this)\"/>"
//            "<rect id=\"rect6\" height=\"140\" width=\"250\"  y=\"300\" x=\"260\"   fill=\"£6\" onclick=\"changeCol(this)\"/>"
//            "</g>"
//
//            "<g id=\"layer2\" font-size=\"45px\" font-family=\"Verdana\" >"
//            "<text id=\"text1\" y=\"50\" x=\"20\" fill=\"#000000\"> $1 </text>"
//            "<text id=\"text2\" y=\"50\" x=\"280\" fill=\"#000000\"> $2 </text>"
//            "<text id=\"text3\" y=\"350\" x=\"20\" fill=\"#000000\"> $3 </text>"
//            "<text id=\"text4\" y=\"500\" x=\"20\" fill=\"#000000\"> $4 </text>"
//            "<text id=\"text5\" y=\"500\" x=\"280\" fill=\"#000000\"> $5 </text>"
//            "<text id=\"text7\" y=\"270\" x=\"330\" fill=\"#000000\"> $7 </text>"
//            "<text id=\"text6\" y=\"350\" x=\"280\" fill=\"#000000\"> $6 </text>"
//
//            "<a xlink:href=\"http://example.com/link/\">"
//            "<text x=\"10\" y=\"700\" >An example link.</text>"
//            "</a>"
//            "</g>"
//
//            "</svg>";
//
//
//            message.replace("$1", String(DT.tSala) );
//            message.replace("$2", String(DT.tCucina) );
//            message.replace("$3", String(DT.tCameraS) );
//            message.replace("$4", String(DT.tCameraD) );
//            message.replace("$5", String(DT.tCameraM) );
//            message.replace("$6", String(DT.tBagno) );
//            message.replace("$7", String(DT.tLavanderia) );
//
//            message.replace("£1", DT.tSala.webColor() );
//            message.replace("£2", String("rgb(") + String((int)(DT.tCucina*10)) + String(",120,200)") );
//            message.replace("£3", String("rgb(") + String((int)(DT.tCameraS*10)) + String(",120,200)") );
//            message.replace("£4", String("rgb(") + String((int)(DT.tCameraD*10)) + String(",120,200)") );
//            message.replace("£5", String("rgb(") + String((int)(DT.tCameraM*10)) + String(",120,200)") );
//            message.replace("£6", String("rgb(") + String((int)(DT.tBagno*10)) + String(",120,200)") );
//            message.replace("£7", String("rgb(") + String((int)(DT.tLavanderia*10)) + String(",120,200)") );
//            
//            client.println(message);
//
//}
