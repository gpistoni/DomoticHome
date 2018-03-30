// Simple example application that shows how to read four Arduino
// digital pins and map them to the USB Joystick library.
//
// NOTE: This sketch file is for use with Arduino Leonardo and
//       Arduino Micro only.
//
// by Matthew Heironimus
// 2015-11-20
//--------------------------------------------------------------------

#include <Joystick.h>

void setup()
{
  // Initialize Button Pins
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
  Serial.begin(115200);
}

// Last state of the button
int lastButtonState[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void loop()
{
  // Read PIN values
  for (int index = 0; index < 14 ; index++)
  {
    int currentButtonState = !digitalRead(index);
    if (currentButtonState != lastButtonState[index])
    {
      Joystick.setButton(index, currentButtonState);
      lastButtonState[index] = currentButtonState;
      Serial.print("button");
      Serial.println(index);
    }
  }

  // bottoni
  int  A0Value = analogRead(A0);
  bool p14 = (A0Value > 100 && A0Value < 200);
  Joystick.setButton(14, p14);
  bool p15 = (A0Value > 200 && A0Value < 300);
  Joystick.setButton(15, p15);
  bool p16 = (A0Value > 300 && A0Value < 600);
  Joystick.setButton(16, p16);
  bool p17 = (A0Value > 600);
  Joystick.setButton(17, p17);
  /*
    Serial.print(" p14:");
    Serial.print(p14);
    Serial.print(" p15:");
    Serial.print(p15);
    Serial.print(" p16:");
    Serial.print(p16);
    Serial.print(" p17:");
    Serial.print(p17);
    Serial.print("A0Value");
    Serial.println(A0Value);
  */

  // switch
  int  A1Value = analogRead(A1);
  bool  p18 = 0, p19 = 0, p20 = 0, p21 = 0 ;
  if (A1Value > 203 - 10 && A1Value < 203 + 10)  
  {
    p18 = 1;
  }
  if (A1Value > 254 - 10 && A1Value < 254 + 10)  
  {
    p18 = 1;p20 = 1;
  }
  if (A1Value > 407 - 10 && A1Value < 407 + 10)  
  {
    p20 = 1;
  }
   if (A1Value > 611 - 10 && A1Value < 611 + 10)  
  {
    p18 = 1;p21 = 1;
  }
   if (A1Value > 680 - 10 && A1Value < 680 + 10)  
  {
    p19 = 1;p20 = 1;
  }
    if (A1Value > 765 - 10 && A1Value < 765 + 10)  
  {
    p19 = 1;p21 = 1;
  }
  if (A1Value > 816 - 10 && A1Value < 816 + 10)  
  {
    p19 = 1;
  }
  Joystick.setButton(18, p18);
  Joystick.setButton(19, p19);
  Joystick.setButton(20, p20);
  Joystick.setButton(21, p21);
  /*
  Serial.print(" p18:");
  Serial.print(p18);
  Serial.print(" p19:");
  Serial.print(p19);
  Serial.print(" p20:");
  Serial.print(p20);
  Serial.print(" p21:");
  Serial.print(p21);
  Serial.print("A1Value");
  Serial.println(A1Value);*/

  // switch
  int  A2Value = analogRead(A2);
  bool  p22 = 0, p23 = 0, p24 = 0, p25 = 0 ;
  if (A2Value > 203 - 10 && A2Value < 203 + 10)  
  {
    p22 = 1;
  }
  if (A2Value > 254 - 10 && A2Value < 254 + 10)  
  {
    p22 = 1;p24 = 1;
  }
  if (A2Value > 407 - 10 && A2Value < 407 + 10)  
  {
    p24 = 1;
  }
   if (A2Value > 611 - 10 && A2Value < 611 + 10)  
  {
    p22 = 1;p25 = 1;
  }
   if (A2Value > 680 - 10 && A2Value < 680 + 10)  
  {
    p23 = 1;p24 = 1;
  }
    if (A2Value > 765 - 10 && A2Value < 765 + 10)  
  {
    p23 = 1;p25 = 1;
  }
  if (A2Value > 816 - 10 && A2Value < 816 + 10)  
  {
    p23 = 1;
  }
  Joystick.setButton(22, p18);
  Joystick.setButton(23, p19);
  Joystick.setButton(24, p20);
  Joystick.setButton(25, p21);
  /*
  Serial.print(" p22:");
  Serial.print(p22);
  Serial.print(" p23:");
  Serial.print(p23);
  Serial.print(" p24:");
  Serial.print(p24);
  Serial.print(" p25:");
  Serial.print(p25);
  Serial.print("A2Value");
  Serial.println(A2Value);
*/
  
  // Read ANALOG values
  //int  sensorValue = analogRead(sensorPin);
  //sensorValue -= 511;
  //sensorValue /= 4;
  //Joystick.setZAxis(sensorValue);

  delay(1);
}

