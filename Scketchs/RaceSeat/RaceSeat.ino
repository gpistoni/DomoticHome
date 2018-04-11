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

// Last state of the button
bool lastButtonState[99];

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

  for (int i = 0; i < 99; i++)
    lastButtonState[i] = false;
}

void SetButton( int index, bool state)
{
  if (state != lastButtonState[index])
  {
    lastButtonState[index] = state;
    Joystick.setButton(index, state);
    Serial.print("button");
    Serial.print(index);
    Serial.print(":");
    Serial.println(state);
  }
}


void loop()
{
  // Read PIN values
  for (int index = 0; index < 14 ; index++)
  {
    int currentButtonState = !digitalRead(index);
    SetButton(index, currentButtonState);
  }

  // bottoni ------------------------------------------
  int  A0Value = analogRead(A0);
  bool p14 = (A0Value > 100 && A0Value < 200);
  SetButton(14, p14);
  bool p15 = (A0Value > 200 && A0Value < 300);
  SetButton(15, p15);
  bool p16 = (A0Value > 300 && A0Value < 600);
  SetButton(16, p16);
  bool p17 = (A0Value > 600);
  SetButton(17, p17);

  // switch ------------------------------------------
  int  A1Value = analogRead(A1);
  bool  p18 = 0, p19 = 0, p20 = 0, p21 = 0 ;
  if (A1Value > 203 - 10 && A1Value < 203 + 10)

  { p18 = 1;
  }
  if (A1Value > 254 - 10 && A1Value < 254 + 10)
  {
    p18 = 1; p20 = 1;
  }
  if (A1Value > 407 - 10 && A1Value < 407 + 10)
  {
    p20 = 1;
  }
  if (A1Value > 611 - 10 && A1Value < 611 + 10)
  {
    p18 = 1; p21 = 1;
  }
  if (A1Value > 680 - 10 && A1Value < 680 + 10)
  {
    p19 = 1; p20 = 1;
  }
  if (A1Value > 765 - 10 && A1Value < 765 + 10)
  {
    p19 = 1; p21 = 1;
  }
  if (A1Value > 816 - 10 && A1Value < 816 + 10)
  {
    p19 = 1;
  }
  SetButton(18, p18);
  SetButton(19, p19);
  SetButton(20, p20);
  SetButton(21, p21);

  if (i++ < 1000)
  {
    Serial.print(" p18:");
    Serial.print(p18);
    Serial.print(" p19:");
    Serial.print(p19);
    Serial.print(" p20:");
    Serial.print(p20);
    Serial.print(" p21:");
    Serial.print(p21);
  }

  // switch ------------------------------------------
  int  A2Value = analogRead(A2);
  bool  p22 = 0, p23 = 0, p24 = 0, p25 = 0 ;
  if (A2Value > 203 - 10 && A2Value < 203 + 10)
  {
    p22 = 1;
  }
  if (A2Value > 254 - 10 && A2Value < 254 + 10)
  {
    p22 = 1; p24 = 1;
  }
  if (A2Value > 407 - 10 && A2Value < 407 + 10)
  {
    p24 = 1;
  }
  if (A2Value > 611 - 10 && A2Value < 611 + 10)
  {
    p22 = 1; p25 = 1;
  }
  if (A2Value > 680 - 10 && A2Value < 680 + 10)
  {
    p23 = 1; p24 = 1;
  }
  if (A2Value > 765 - 10 && A2Value < 765 + 10)
  {
    p23 = 1; p25 = 1;
  }
  if (A2Value > 816 - 10 && A2Value < 816 + 10)
  {
    p23 = 1;
  }
  SetButton(22, p22);
  SetButton(23, p23);
  SetButton(24, p24);
  SetButton(25, p25);

  if (i++ < 1000)
  {
    Serial.print(" p22:");
    Serial.print(p22);
    Serial.print(" p23:");
    Serial.print(p23);
    Serial.print(" p24:");
    Serial.print(p24);
    Serial.print(" p25:");
    Serial.print(p25);
    Serial.println("");
  }

  // Read ANALOG values
  //int  sensorValue = analogRead(sensorPin);
  //sensorValue -= 511;
  //sensorValue /= 4;
  //Joystick.setZAxis(sensorValue);

  delay(1);
}

