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


void setup()
{
  Serial.begin(9600);

  dht.setup(10, DHT21);
   
  // put your setup code here, to run once:
  disp.setup();

  t_h.setup(20, 20, 60, 40, "00", YELLOW);
  t_m.setup(90, 20, 60, 40, "00", YELLOW);
  t_s.setup(160, 20, 60, 40, "00", YELLOW);

  ltemp.setup(20, 70, 120, 90, "\n00.0", CYAN);

  bt_piu.setup(150, 70, 70, 40, " +", RED);
  bt_meno.setup(150, 120, 70, 40, " -", BLUE);
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
  
  float t = dht.readTemperature();  
  Serial.println(t);
  ltemp.label( t );
 
  Serial.println("UpdateTemp timer");
}

float tTarget = 20;

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
  if ( bt_piu.pressed(p) )
  {
    tTarget += 0.5;
    ltemp.bkgCol( MAGENTA );
    ltemp.label( tTarget );
    blocked = millis() + 6000;
     Serial.println("piu");
  }
  if ( bt_meno.pressed(p) )
  {
    tTarget -= 0.5;
    ltemp.bkgCol( MAGENTA );
    ltemp.label( tTarget );
    blocked = millis() + 6000;
      Serial.println("meno");
  }

  SecondT();  
  UpdateTemp(blocked);

}
