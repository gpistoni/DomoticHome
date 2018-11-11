#include "ArduinoJson.h"

extern EthernetServer server;
extern DHProtocol T[8];

String readString;

bool listenForEthernetClients()
{
  // listen for incoming clients
  EthernetClient client = server.available();
  if (client)
  {
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
          int idx;
          //****************************************************************************************************************************
          // comandi speciali
          //****************************************************************************************************************************
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
          //****************************************************************************************************************************
          if ( idxGET > 0 )
          {
            OUTLN( "Get:" + String( GetParam0 ) + "," + String( GetParam1) );
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
          //****************************************************************************************************************************
          else if ( idxSET > 0 )
          {
            OUTLN( "Set:" + String(SetParam0) + "," + String(SetParam1) + "=" + String(SetParam2) );
            T[ SetParam0 ].relay[SetParam1] = SetParam2;
            client.print( T[ SetParam0 ].relay[SetParam1] );
            break;
          }
          //****************************************************************************************************************************
          else
          {
            OUTLN( "DEBUG TREE"   + readString);

            StaticJsonBuffer<500> jb;
            client.println("[");
            for (int c = 1; c <= 7; c++)
            {
              jb.clear();
              JsonObject &obj = jb.createObject();
              obj["N"] = c;
              if ( c == 1)  obj["Name"] = "Temp Stanze";
              if ( c == 2)  obj["Name"] = "Luci Esterne" ;
              if ( c == 3)  obj["Name"] = "Rele Caldaia";
              if ( c == 4)  obj["Name"] = "Temp Caldaia" ;
              if ( c == 5)  obj["Name"] = "Rele Pavimento" ;
              if ( c == 6)  obj["Name"] = "Amperometri";
              if ( c == 7)  obj["Name"] = "-";

              obj["tReq"] = T[ c ].lastRequest;
              obj["tRec"] = T[ c ].lastRecived;

              for (int i = 0; i < 24; i++)
              {
                if (i < 1 || T[c].sensor[i] != 0)     obj["v" + String(i)] = T[c].sensor[i];
              }
              for (int i = 0; i < 12; i++)
              {
                if (i < 1 || T[c].relay[i] != 0)      obj["r" + String(i)] = T[c].relay[i];
              }
              obj.prettyPrintTo(client);
            }
            client.println("]");
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
    delay(2);

    // close the connection:
    readString = "";
    client.stop();
    return true;
  }
  return false;
}
/////
