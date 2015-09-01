extern EthernetServer server;
extern DHProtocol T[8];

String readString;

void listenForEthernetClients()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client)
  {
    OUTLN("Got a client");

    // an http request ends with a blank line
    while (client.connected())
    {
      if (client.available())
      {
        // Read the received command sent from client
        char c = client.read();
        if (readString.length() < 50 )
        {
          readString = readString + c;
        }

        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n')
        {
          OUTLN( readString.c_str() );
          int idx;
          //*************************************
          // comandi speciali
          idx = readString.indexOf("@debug");
          if (idx > 0)
          {
            for (int c = 0; c < 8; c++)
            {
              client.print( "T" + String(c) + ": " );
              client.print( T[ c ].lastRequest);
              client.print( " / " );
              client.println( T[ c ].lastRecived);
              for (int i = 0; i < 24; i++)
              {
                if (i != 0) client.print(',');
                client.print( T[ c ].sensor[i] );
              }
              client.println("");
              for (int i = 0; i < 12; i++)
              {
                if (i != 0) client.print(',');
                client.print( T[ c ].relay[i] );
              }
              client.println("");
            }
            break;
          }
          //*************************************
          int idxGET = readString.indexOf("@get(");
          int idxGET2 = readString.indexOf(",", idxGET);
          int idxGET3 = readString.indexOf(")", idxGET2);

          int GetParam0 = readString.substring(idxGET + 5, idxGET2).toInt();
          int GetParam1 = readString.substring(idxGET2 + 1, idxGET3).toInt();

          int idxSET = readString.indexOf("@set(");
          int idxSET2 = readString.indexOf(",", idxSET);
          int idxSET3 = readString.indexOf("=", idxSET2);
          int idxSET4 = readString.indexOf(")", idxSET3);

          int SetParam0 = readString.substring(idxSET + 5, idxSET2).toInt();
          int SetParam1 = readString.substring(idxSET2 + 1, idxSET3).toInt();
          int SetParam2 = readString.substring(idxSET3 + 1, idxSET4).toInt();

          if ( idxGET > 0 )
          {
            if ( GetParam1 < 99)
              client.print( T[ GetParam0 ]. sensor[ GetParam1 ] );
            else
              for (int i = 0; i < 24; i++)
              {
                if (i != 0) client.print(',');
                client.print( T[ GetParam0 ].sensor[i] );
              }
            break;
          }

          if ( idxSET > 0 )
          {
            T[ SetParam0 ].relay[SetParam1] = SetParam2;
            client.print( T[ SetParam0 ].relay[SetParam1] );
            break;
          }


          OUTLN( "Get:" + String( GetParam0 ) + "," + String( GetParam1) );
          OUTLN( "Set:" + String(SetParam0) + "," + String(SetParam1) + "=" + String(SetParam2) );

          //*************************************
          // client.println("HTTP/1.1 200 OK");
          // client.println("Content-Type: text/html");
          // client.println("Connection: close");        // the connection will be closed after completion of the response
          // client.println("Refresh: 1");               // refresh the page automatically every 5 sec

          client.println("Sintax error");

          //***************************************
          break;
        }
      }
    }

    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    readString = "";
    client.stop();
    OUTLN("client disconnected");
  }
}


