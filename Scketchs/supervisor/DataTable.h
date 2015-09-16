#pragma once
#include "vars.h"

//********************************************************************************************
class cDataTable
{
  enum { T0=0, T1=1, T2=2, T3=3, T4=4, T5=5, T6=6, T7=7 };
  public:
    // terminal 3
    cBool rPdc;
    cBool rPdcCool0_Heat1;
    cBool rPdcPompa;
    cBool rPdcNightMode;
    
    cBool rPompaPianoPrimo;
    cBool rPompaPianoTerra;
    cBool rBoilerSanitaria;
    
    // terminal 4
    float tPufferHi;
    float tPufferLow;
    float tInputMixer;
    float tReturnFireplace;
    float tReturnFloor;
    float tInletFloor;
    float tExternal;
    
     // terminal 5
    bool evCameraM1;
    bool evCameraM2;
    bool evSala1;
    bool evSala2;
    bool evCucina;
    bool evCameraS;
    bool evCameraD1;
    bool evCameraD2;

    void setup()
    {
      rPdc.setup            ( T3, 0, "PDC");
      rPdcCool0_Heat1.setup ( T3, 1, "CoolHeat");
      rPdcPompa.setup       ( T3, 2, "PdcPompa");
      rPdcNightMode.setup   ( T3, 3, "PdcNightMode");
      rPompaPianoPrimo.setup( T3, 4, "PompaPianoPrimo");
      rPompaPianoTerra.setup( T3, 5, "PompaPianoTerra");
      rBoilerSanitaria.setup( T3, 6, "BoilerSanitaria");
    };
    
    void UpdateT3( String strs )
    {
      Serial.println( "T3" );
      rPdc.setS( strs );
      rPdcCool0_Heat1.setS( strs );
      rPdcPompa.setS( strs );
      rPdcNightMode.setS( strs );
      
      rPompaPianoPrimo.setS( strs );
      rPompaPianoTerra.setS( strs );
      rBoilerSanitaria.setS( strs );     
    };
    
    void UpdateT4( String strs)
    {
      Serial.println( "T4" );
      tPufferHi = strValueD(strs, ',', 0);
      tPufferLow = strValueD(strs, ',', 1);
      tInputMixer = strValueD(strs, ',', 2);
      tReturnFireplace = strValueD(strs, ',', 3);
      tReturnFloor = strValueD(strs, ',', 4);
      tInletFloor = strValueD(strs, ',', 5);
      tExternal = strValueD(strs, ',', 6);


      Serial.print( "DT.tPufferHi:" );
      Serial.println( tPufferHi );
      Serial.print( "DT.tPufferLow:" );
      Serial.println( tPufferLow );
      Serial.print( "DT.tInputMixer:" );
      Serial.println( tInputMixer );
      Serial.print( "DT.tReturnFireplace:" );
      Serial.println( tReturnFireplace );
      Serial.print( "DT.tReturnFloor:" );
      Serial.println( tReturnFloor );
      Serial.print( "DT.tInletFloor:" );
      Serial.println( tInletFloor );
      Serial.print( "DT.tExternal:" );
      Serial.println( tExternal );
    };

    void UpdateT5( String strs)
    {
      Serial.println( "T5" );
      evCameraM1 = strValueB(strs, ',', 0);
      evCameraM2 = strValueB(strs, ',', 1);
      evSala1 = strValueB(strs, ',', 2);
      evSala2 = strValueB(strs, ',', 3);
      evCucina = strValueB(strs, ',', 4);
      evCameraS = strValueB(strs, ',', 5);
      evCameraD1 = strValueB(strs, ',', 6);
      evCameraD2 = strValueB(strs, ',', 7);
    
      Serial.print( "DT.evCameraM1:" );
      Serial.println( evCameraM1 );
      Serial.print( "DT.evCameraM2:" );
      Serial.println( evCameraM2 );
      Serial.print( "DT.evSala1:" );
      Serial.println( evSala1 );
      Serial.print( "DT.evSala2:" );
      Serial.println( evSala2 );
      Serial.print( "DT.evCucina:" );
      Serial.println( evCucina );
      Serial.print( "DT.evCameraS:" );
      Serial.println( evCameraS );
      Serial.print( "DT.evCameraD1:" );
      Serial.println( evCameraD1 );
      Serial.print( "DT.evCameraD2:" );
      Serial.println( evCameraD2 );
    };
};

//********************************************************************************************
// scompatta una lista in campi
String strValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length() - 1;

  for (int i = 0; i <= maxIndex && found <= index; i++) {
    if (data.charAt(i) == separator || i == maxIndex) {
      found++;
      strIndex[0] = strIndex[1] + 1;
      strIndex[1] = (i == maxIndex) ? i + 1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}

double strValueD(String data, char separator, int index)
{
  return strValue( data, separator, index).toInt() / 10.0;
}

bool strValueB(String data, char separator, int index)
{
  return strValue( data, separator, index).toInt() > 0;
}
