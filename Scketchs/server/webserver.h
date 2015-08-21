extern EthernetServer server;
extern DHProtocol T[8];

String readString;

void listenForEthernetClients()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client)
  {
    Serial.println("Got a client");

    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected())
    {
      if (client.available())
      {
        // Read the received command sent from client
        char c = client.read();
        if (readString.length() < 50 )
        {
          readString = readString + c;
          Serial.write(c);
        }
      else
        {
          Serial.println( readString.c_str() );
          //*************************************
          // comandi speciali
          int idx = readString.indexOf("@debug");
          if (idx > 0)
          {
            client.println("ALL CLIENT");
            for ( int t = 1; t < 8; t++)
            {
              client.println("");
              client.print("Terminal");
              client.println(t);
              client.print("Relay");
              client.print( '0' + T[t].relay.bits.b1 );
              client.print( '0' + T[t].relay.bits.b2 );
              client.print( '0' + T[t].relay.bits.b3 );
              client.print( '0' + T[t].relay.bits.b4 );
              client.print( '0' + T[t].relay.bits.b5 );
              client.print( '0' + T[t].relay.bits.b6 );
              client.print( '0' + T[t].relay.bits.b7 );
              client.print( '0' + T[t].relay.bits.b8 );
              client.print("Sensors");
              for ( int s = 0; s < T[t].m_nsensors; s++)
              {
                if (s != 0)  client.print( ',');
                client.print( T[t].sensor[s] );
              }
            }
          }
        }
        //*************************************
        int idxGET = readString.indexOf("@get(");
        int idxGET2 = readString.indexOf(",", idxGET);
        int idxGET3 = readString.indexOf(")", idxGET2);

        int GetParam[2] = {0, 0};
        GetParam[0] = readString.substring(idxGET + 5, idxGET2).toInt();
        GetParam[1] = readString.substring(idxGET2 + 1, idxGET3).toInt();

        int idxSET = readString.indexOf("@set(");
        int idxSET2 = readString.indexOf(",", idxSET);
        int idxSET3 = readString.indexOf("=", idxSET2);
        int idxSET4 = readString.indexOf(")", idxSET3);

        int SetParam[3] = {0, 0, 0};
        SetParam[0] = readString.substring(idxSET + 5, idxSET2).toInt();
        SetParam[1] = readString.substring(idxSET2 + 1, idxSET3).toInt();
        SetParam[2] = readString.substring(idxSET3 + 1, idxSET4).toInt();

        Serial.println( "Get:" + String(GetParam[0]) + "," + String(GetParam[1]) );
        Serial.println( "Set:" + String(SetParam[0]) + "," + String(SetParam[1]) + "=" + String(SetParam[2]) );

        client.println("100");

        //***************************************
        break;
      }
    }

    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    readString = "";
    client.stop();
    Serial.println("client disconnected");
  }
}

