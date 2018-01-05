extern EthernetServer server;
extern DHProtocol T[8];

String readString;

bool listenForEthernetClients()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client)
  {
    OUTLN("\nGot a client");

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
        if ( c == '\n')
        {
          OUT( readString.c_str() );
          int idx;
          //*************************************
          // comandi speciali
          idx = readString.indexOf("@debug");
          if (idx > 0)
          {
            for (int c = 1; c < 8; c++)
            {
              client.print( "T" + String(c) + ": " );
              if( c==1)  client.print( "Temperature Stanze  \t" );
              if( c==2)  client.print( "Luci Esterne   \t" );
              if( c==3)  client.print( "Rele Caldaia        \t" );
              if( c==4)  client.print( "Temperature Caldaia \t" );
              if( c==5)  client.print( "Rele Ev Pavimento   \t" );
              if( c==6)  client.print( "Amperometri   \t" );
              
              client.print( T[ c ].lastRequest % 100000);
              client.print( " / " );
              client.println( T[ c ].lastRecived % 100000);
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
            OUT("idxGET");
            OUTLN(GetParam1);
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
            OUT("idxSET");
            OUTLN(GetParam1);
            T[ SetParam0 ].relay[SetParam1] = SetParam2;
            client.print( T[ SetParam0 ].relay[SetParam1] );
            break;
          }

          OUTLN( "Get:" + String( GetParam0 ) + "," + String( GetParam1) );
          OUTLN( "Set:" + String(SetParam0) + "," + String(SetParam1) + "=" + String(SetParam2) );

          client.println("Sintax error");

          //***************************************
          break; // while
        }
      }
    }

    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    readString = "";
    client.stop();
    OUTLN("client byed");
    return true;
  }
  return false;
}


