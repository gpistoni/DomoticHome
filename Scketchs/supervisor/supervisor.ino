#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Time.h>

#include "dhwifi.h"
#include "dhconfig.h"
#include "DataTable.h"
#include "functions.h"
#include "httpServer2.h"
#include "Managers.h"

DHwifi dhWifi;

cDataTable DT;
DHFile     Config;

WiFiServer httpServer(80);

const int ACT = 2;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup()
{
  Serial.begin(115200);
  Serial.println("SETUP");

  pinMode(ACT, OUTPUT);

  IPAddress ip(192, 168, 1, 201);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 255, 0);

  String ssid   = "PistoniHome";          // your network SSID (name)
  String pass   = "giaco1iren1dario";     // your network password
  String remote = "192.168.1.200";        // remote server (arduino ethernet home)

  dhWifi.setup( ip, gateway, subnet, ssid, pass, remote );

  DT.setup();

  UpdateTime(0);      // update system time

  initHttpServer();

  UpdateTerminals( 0 );

  DT.progBoilerACS.set(1);
  DT.progSummerAC.set(0);
  DT.progWinterPDC.set(0);
  DT.progWinterPDC_ALLROOMS.set(0);
  DT.progWinterPDC_FOTOV.set(0);
  DT.progAllRooms.set(0);
  DT.progExternalLight.set(1);

  UpdateTime(0);  // update system time
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop()
{
  if ( handleHttpServer() )
  {
    return;
  }
  UpdateTime( 300 );

  digitalWrite(ACT, 1);

  // manual Check Programmi
  DT.progBoilerACS.manualCheck();
  DT.progSummerAC.manualCheck();
  DT.progSummerAC_NIGHT.manualCheck();
  DT.progWinterFIRE.manualCheck();
  DT.progWinterPDC.manualCheck();
  DT.progWinterPDC_ALLROOMS.manualCheck();
  DT.progWinterPDC_FOTOV.manualCheck();
  DT.progAllRooms.manualCheck();
  DT.progExternalLight.manualCheck();

  if ( hour() > 7 && hour() < 19 ) DT.progSummerAC_NIGHT.set(0);
  if ( month() >= 10 || month() <= 4) DT.progWinterFIRE.set(1);

  if (DT.progSummerAC_NIGHT)      DT.progSummerAC.set(1);
  
  if (DT.progWinterFIRE)          DT.progSummerAC.set(0);
  if (DT.progWinterPDC)           DT.progSummerAC.set(0);
  if (DT.progWinterPDC_ALLROOMS)  DT.progSummerAC.set(0);
  if (DT.progWinterPDC_FOTOV)     DT.progSummerAC.set(0);

  { // Run Managers

    if ( DT.progSummerAC )            // solo estate
    {
      Summer_Manager( 30 );
    }
    else                               // solo inverno
    {
      Winter_Manager( 31 );
    }
    
    BoilerACS_Manager( 32 );
    
    ExternalLight_Manager( 60 );
  }

  //----------------------------------------------------------------------------
  RollingSendValues( 5 );
  //----------------------------------------------------------------------------

  if ( handleHttpServer() )
  {
    return;
  }

  digitalWrite(ACT, 0);
  //----------------------------------------------------------------------------
  
  UpdateTerminals( 5 );
  //----------------------------------------------------------------------------
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateTime( int sec )
{
  _CHECK_TIME_;
 DT.m_log.add( "--- UpdateTime" );

  time_t epoch = dhWifi.GetSystemTime();

  if (epoch > 0)
  {
    setTime( epoch );
    if (month() >= 4 && month() <= 10) adjustTime(3600);
    DT.m_log.add( date_time() );
  }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateTerminals( int sec )
{
  _CHECK_TIME_;
  DT.m_log.add( "--- UpdateTerminals" );

  String data = dhWifi.HttpRequest("/");

  DynamicJsonBuffer jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(data);

  if (!root.success()) 
  {
    DT.m_log.add("parseObject() failed");
    return;
  }

  DT.UpdateALL( root );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RollingSendValues( int sec )
{
  _CHECK_TIME_;
  //DT.m_log.add( "--- RollingSendValues" );
  
  static unsigned int i = 0;

  // manual Check Rele'
  DT.rPdc.manualCheck();
  DT.rPdcHeat.manualCheck();
  DT.rPdcPompa.manualCheck();
  DT.rPdcNightMode.manualCheck();

  DT.rPompaPianoPrimo.manualCheck();
  DT.rPompaPianoTerra.manualCheck();
  DT.rBoilerACS.manualCheck();
  DT.rPompaCamino.manualCheck();

  DT.lightCorner.manualCheck();
  DT.lightSide.manualCheck();
  DT.lightLamp.manualCheck();
  DT.lightExtra.manualCheck();

  // le nnn sono a basso intervento 200 sec
  unsigned int i_hi =  i % 20;
  unsigned int i_low =  i % 200;

  if ( i_low == 10 )  DT.rPdc.sendRequest(&dhWifi, DT.m_log );
  if ( i_low == 12 )  DT.rPdcHeat.sendRequest(&dhWifi, DT.m_log );
  if ( i_low == 14 )  DT.rPdcPompa.sendRequest(&dhWifi, DT.m_log );
  if ( i_low == 16 )  DT.rPdcNightMode.sendRequest(&dhWifi, DT.m_log );

  if ( i_hi == 1 )    DT.rPompaPianoPrimo.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 2 )    DT.rPompaPianoTerra.sendRequest(&dhWifi, DT.m_log );
  if ( i_low == 20 )  DT.rBoilerACS.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 3 )    DT.rPompaCamino.sendRequest(&dhWifi, DT.m_log );

  if ( i_hi == 5 )    DT.evCameraM1.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 6 )    DT.evCameraM2.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 7 )    DT.evSala1.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 8 )    DT.evSala2.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 9 )    DT.evCucina.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 10 )   DT.evCameraS.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 11 )   DT.evCameraD1.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 12 )   DT.evCameraD2.sendRequest(&dhWifi, DT.m_log );

  if ( i_hi == 13 )   DT.lightCorner.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 14 )   DT.lightSide.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 15 )   DT.lightLamp.sendRequest(&dhWifi, DT.m_log );
  if ( i_hi == 16 )   DT.lightExtra.sendRequest(&dhWifi, DT.m_log );

  i++;
}
