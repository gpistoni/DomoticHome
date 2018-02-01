#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_TFTLCD.h> // Hardware-specific library
#include <TouchScreen.h>
#include <Time.h>
#include <DHT.h>

#include "screen.h"

DHT dht;

CScreen disp;

ButtonLabel t_h, t_m, t_s;
ButtonLabel ltemp;
ButtonLabel bt_piu, bt_meno;

ButtonLabel bt_manAuto;
bool ManAuto = 0;

ButtonLabel bt_caldaia;


float tCorrente = 20;
float tTarget = 25;

bool Caldaia = false;

void setup()
{
  Serial.begin(9600);

  dht.setup(10, DHT21);

  pinMode(11, OUTPUT);

  // put your setup code here, to run once:
  disp.setup();

  t_h.setup(20, 20, 60, 40, "00", YELLOW);
  t_m.setup(90, 20, 60, 40, "00", YELLOW);
  t_s.setup(160, 20, 60, 40, "00", YELLOW);

  ltemp.setup(20, 70, 120, 90, "0.0", CYAN);

  bt_piu.setup(150, 70, 70, 40, " +", RED);
  bt_meno.setup(150, 120, 70, 40, " -", BLUE);

  bt_manAuto.setup(20, 170, 200, 40, "MANUALE", MAGENTA);

  bt_caldaia.setup(20, 240, 70, 40, "off", GRAY );
}

/**************************************************************************************************/
void SecondT()
{
  static unsigned long last = 0;
  if ( millis() - last < 1000 ) return;
  last = millis();

  t_s.label( second() );
  if ( second() == 0 ) t_m.label( minute() );
  if ( second() == 0  && minute() == 0 )  t_h.label( hour() );
  Serial.println("SecondT timer");
}

/**************************************************************************************************/
void UpdateTemp( unsigned long &blocked )
{
  static unsigned long last = 0;
  if ( millis() - last < 3000 || millis() < blocked ) return;
  last = millis();
  blocked = 0;

  // leggere templ
  ltemp.bkgCol( CYAN );

  tCorrente = dht.readTemperature();
  Serial.println(tCorrente);
  ltemp.label( tCorrente  );

  Serial.println("UpdateTemp timer");
}

void Attuatori()
{
  static unsigned long last = 0;
  if ( millis() - last < 3000 ) return;
  last = millis();

  if ( ManAuto == false)
  {
    if ( Caldaia )
    { if ( tCorrente > tTarget + 0.2  )
        Caldaia = false;
    }
    else
    { if ( tCorrente < tTarget - 0.2  )
        Caldaia = true;
    }
    Serial.println("caldaia");
    Serial.println(Caldaia);
    Serial.println(tCorrente);
    Serial.println(tTarget);
  }
  else
  {
    float tT = 10;
    if ( hour() > 6 && hour() < 20  )
      tT = 20;
    if ( (hour() < 6 || hour() > 20))
      tT = 15;

    if ( Caldaia )
      if ( tCorrente > tT + 0.2  )
        Caldaia = false;
      else if ( tCorrente < tT - 0.2  )
        Caldaia = true;
  }

  if ( Caldaia )
    bt_caldaia.label( "on", GREEN );
  else
    bt_caldaia.label( "off", GRAY );

  digitalWrite(11, Caldaia);
}



/**************************************************************************************************/
void loop()
{
  static unsigned long blocked;

  TSPoint p = disp.getTouchPoint();

  if ( t_h.pressed(p) )
  {
    adjustTime( 60 * 60 );
    t_h.label( hour() );
  }
  if ( t_m.pressed(p) )
  {
    adjustTime( 60 );
    t_m.label( minute() );
  }
  if ( bt_piu.pressed(p) && ManAuto == false)
  {
    tTarget += 0.5;
    ltemp.bkgCol( MAGENTA );
    ltemp.label( tTarget );
    blocked = millis() + 6000;
    Serial.println("piu");
  }
  if ( bt_meno.pressed(p) && ManAuto == false)
  {
    tTarget -= 0.5;
    ltemp.bkgCol( MAGENTA );
    ltemp.label( tTarget );
    blocked = millis() + 6000;
    Serial.println("meno");
  }
  if ( bt_manAuto.pressed(p) )
  {
    ManAuto = !ManAuto;
    if (ManAuto)
    {
      bt_manAuto.label( "Automat", GREEN );
      bt_piu.hide();
      bt_meno.hide();
    }
    else
    {
      bt_manAuto.label( "Manuale", MAGENTA );
      bt_piu.draw(true);
      bt_meno.draw(true);
    }
  }

  if ( p.z > 20 )
    delay(50);

  SecondT();
  UpdateTemp(blocked);

  Attuatori();
}
