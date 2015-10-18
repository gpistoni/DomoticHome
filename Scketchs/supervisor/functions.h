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

void logToFile ()
{
  // make a string that start with a timestamp for assembling the data to log:
  String dataString;
  dataString = short_time();
  dataString += " = ";
 /* 
  // read three sensors and append to the string:
  for (int analogPin = 0; analogPin < 3; analogPin++) 
  {
    int sensor = analogRead(analogPin);
    dataString += String(sensor);
    if (analogPin < 2) 
    {
      dataString += ",";  // separate the values with a comma
    }
  }
  */
  
//
//  // open the file. note that only one file can be open at a time,
//  // so you have to close this one before opening another.
//  // The FileSystem card is mounted at the following "/mnt/FileSystema1"
//  File dataFile = FileSystem.open("/mnt/sd/datalog.txt", FILE_APPEND);
//
//  // if the file is available, write to it:
//  if (dataFile) {
//    dataFile.println(dataString);
//    dataFile.close();
//    // print to the serial port too:
//    Serial.println(dataString);
//  }
//  // if the file isn't open, pop up an error:
//  else {
//    Serial.println("error opening datalog.txt");
//  }
}


#endif
