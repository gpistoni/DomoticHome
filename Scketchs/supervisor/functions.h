#ifndef functions_h
#define functions_h

void printDigits(int digits)
{
    // utility function for digital clock display: prints preceding colon and leading 0
    if(digits < 10)
        Serial.print('0');
    Serial.print(digits);
}

void digitalClockDisplay()
{
  // digital clock display of the time
  Serial.print(hour());
  Serial.print(":");
  printDigits(minute());
  Serial.print(":");
  printDigits(second());
  Serial.print(" ");
  printDigits(day());
  Serial.print("/");
  printDigits(month());
  Serial.print("/");
  Serial.print(year());
  Serial.print(" ");
}

String short_time()
{
  String dataString;
  if(hour() < 10)
        dataString += "0";
  dataString += hour();
  dataString += ":";
  if(minute() < 10)
        dataString += "0";
  dataString += minute();
  dataString += ":";
    if(second() < 10)
        dataString += "0";
  dataString += second();
  dataString += " ";
 
  return dataString;
}

#endif
