//#include "ArduinoJson.h"

extern EthernetServer server;
extern DHProtocol T[8];

//StaticJsonBuffer<500> jb;

// caratteri
void jPrint( EthernetClient &client, char* ch)
{
  client.println(ch);
}

// gruppo
void jPrint_T( EthernetClient &client, int n)
{
  client.println(String("\"T") + String(n) + "\" : " );
}

// elementi
void jPrint_S( EthernetClient &client, const String &name, const String &value)
{
  client.println(String("\"") + name + "\":\"" +  value +  "\"," );
}

void jPrint_F( EthernetClient &client, const String &name, float value)
{
  client.println(String("\"") + name + "\":\"" +  String(value) +  "\"," );
}

void jPrint_I( EthernetClient &client, const String &name, int value)
{
  client.println(String("\"") + name + "\":\"" +  String(value) +  "\"," );
}

// elemento terminale senza la virgola
void jPrint_check( EthernetClient &client)
{
  client.println(String("\"") + String("check") + "\":" +  String(0) );
}


bool listenForEthernetClients()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client)
  {
    String readString;

    // an http request ends with a blank line
    unsigned long timeout = millis() + 2000;
    while (client.connected() && millis() < timeout )
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
          int idx;
          //****************************************************************************************************************************
          // comandi speciali
          //****************************************************************************************************************************
          int idxGET = readString.indexOf("get?");

          int idxGET1 = readString.indexOf("?", idxGET);
          int idxGET2 = readString.indexOf("-", idxGET1);
          int idxGET3 = readString.indexOf(" ", idxGET2);

          String GetParam0 = readString.substring(idxGET1 + 1, idxGET2);
          String GetParam1 = readString.substring(idxGET2 + 1, idxGET3);

          int idxSET  = readString.indexOf("set?");
          int idxSET1 = readString.indexOf("?", idxSET);
          int idxSET2 = readString.indexOf("-", idxSET1);
          int idxSET3 = readString.indexOf("=", idxSET2);
          int idxSET4 = readString.indexOf(" ", idxSET3);

          String SetParam0 = readString.substring(idxSET1 + 1, idxSET2);
          String SetParam1 = readString.substring(idxSET2 + 1, idxSET3);
          String SetParam2  = readString.substring(idxSET3 + 1, idxSET4);

          //****************************************************************************************************************************
          if ( idxGET > 0 )
          {
            OUTLN( "Get:" + String( GetParam0 ) + "," + String( GetParam1) );

            int t = GetParam0.substring(1).toInt();
            int v = GetParam1.substring(1).toInt();

            if (t > 0 && t < 8 && v >= 0 && v < 24)
              client.print( T[ t ].sensor[v] );
            break;
          }
          //****************************************************************************************************************************
          else if ( idxSET > 0 )
          {
            OUTLN( "Set:" + String(SetParam0) + "," + String(SetParam1) + "=" + String(SetParam2) );

            int t = SetParam0.substring(1).toInt();
            int r = SetParam1.substring(1).toInt();
            float value = SetParam2.toFloat();

            if (t > 0 && t < 8 && r >= 0 && r < 12)
            {
              T[t].relay[r] = value;
              client.print( T[t].relay[r] );
            }            
            break;
          }
          //****************************************************************************************************************************
          else
          {
            String str;
            jPrint(client, "{");

            for (int c = 1; c <= 7; c++)
            {
              jPrint_T(client, c);

              jPrint(client, "{");

              if ( c == 1)  jPrint_S(client, "Name", "Temp Stanze");
              if ( c == 2)  jPrint_S(client, "Name", "Luci Esterne");
              if ( c == 3)  jPrint_S(client, "Name", "Rele Caldaia");
              if ( c == 4)  jPrint_S(client, "Name", "Temp Caldaia");
              if ( c == 5)  jPrint_S(client, "Name", "Rele Pavimento");
              if ( c == 6)  jPrint_S(client, "Name", "Amperometri");
              if ( c == 7)  jPrint_S(client, "Name", "-");

              jPrint_I(client, "tReq", T[c].lastRequest );
              jPrint_I(client, "tRec", T[c].lastRecived );


              for (int i = 0; i < 24; i++)
              {
                if (i < 1 || T[c].sensor[i] != 0)
                  jPrint_F(client, String("v") + String(i), T[c].sensor[i] / 10.0  );
              }
              for (int i = 0; i < 12; i++)
              {
                if (i < 1 || T[c].relay[i] != 0)
                  jPrint_I(client, String("r") + String(i), T[c].relay[i] );
              }

              jPrint_check(client);
              jPrint(client, "}");
              if (c != 7) jPrint(client, ",");
            }

            jPrint(client, "}\n\r");
            break;
          }
          //*************************************
          client.println("Sintax error");
          //***************************************
          break; // while
        }
      }
    }

    // give the web browser time to receive the data
    delay(50);

    // close the connection:
    readString = "";
    client.stop();
    return true;
  }
  return false;
}
/////
