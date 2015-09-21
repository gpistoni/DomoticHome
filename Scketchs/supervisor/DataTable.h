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
    cFloat tPufferHi;
    cFloat tPufferLow;
    cFloat tInputMixer;
    cFloat tReturnFireplace;
    cFloat tReturnFloor;
    cFloat tInletFloor;
    cFloat tExternal;
    
     // terminal 5
    cBool evCameraM1;
    cBool evCameraM2;
    cBool evSala1;
    cBool evSala2;
    cBool evCucina;
    cBool evCameraS;
    cBool evCameraD1;
    cBool evCameraD2;

    void setup()
    {
      rPdc.setup              ( T3, 0, "PDC");
      rPdcCool0_Heat1.setup   ( T3, 1, "CoolHeat");
      rPdcPompa.setup         ( T3, 2, "PdcPompa");
      rPdcNightMode.setup     ( T3, 3, "PdcNightMode");
      rPompaPianoPrimo.setup  ( T3, 4, "PompaPianoPrimo");
      rPompaPianoTerra.setup  ( T3, 5, "PompaPianoTerra");
      rBoilerSanitaria.setup  ( T3, 6, "BoilerSanitaria");

      tPufferHi.setup         ( T4, 0, "tPufferHi");
      tPufferLow.setup        ( T4, 1, "tPufferLow");
      tInputMixer.setup       ( T4, 2, "tInputMixer");
      tReturnFireplace.setup  ( T4, 3, "tReturnFireplace");
      tReturnFloor.setup      ( T4, 4, "tReturnFloor");
      tInletFloor.setup       ( T4, 5, "tInletFloor");
      tExternal.setup         ( T4, 6, "tExternal");
      
      evCameraM1.setup        ( T5, 0, "evCameraM1");
      evCameraM2.setup        ( T5, 1, "evCameraM2");
      evSala1.setup           ( T5, 2, "evSala1");
      evSala2.setup           ( T5, 3, "evSala2");
      evCucina.setup          ( T5, 4, "evCucina");
      evCameraS.setup         ( T5, 5, "evCameraS");
      evCameraD1.setup        ( T5, 6, "evCameraD1");
      evCameraD2.setup        ( T5, 7, "evCameraD2");
    };
    
    void UpdateT3( String strs )
    {
      Serial.print( "T3: " );      
      Serial.println( strs);
      
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
      Serial.print( "T4: " );      
      Serial.println( strs);
      
      tPufferHi.setS( strs );
      tPufferLow.setS( strs );
      tInputMixer.setS( strs );
      tReturnFireplace.setS( strs );
      tReturnFloor.setS( strs );
      tInletFloor.setS( strs );
      tExternal.setS( strs );
    };

    void UpdateT5( String strs)
    {
      Serial.print( "T5: " );      
      Serial.println( strs);
      
      evCameraM1.setS( strs );
      evCameraM2.setS( strs );
      evSala1.setS( strs );
      evSala2.setS( strs );
      evCucina.setS( strs );
      evCameraS.setS( strs );
      evCameraD1.setS( strs );
      evCameraD2.setS( strs );
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
