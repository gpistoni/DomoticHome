#pragma once
#include "DataVars.h"

//********************************************************************************************
class cDataTable
{
    enum { T0 = 0, T1 = 1, T2 = 2, T3 = 3, T4 = 4, T5 = 5, T6 = 6, T7 = 7 };
  public:
    // terminal 1
    cFloat hCucina;
    cFloat hSala;
    cFloat hCameraS;
    cFloat hCameraD;
    cFloat hCameraM;
    cFloat hBagno;
    cFloat hLavanderia;

    cFloat tCucina;
    cFloat tSala;
    cFloat tCameraS;
    cFloat tCameraD;
    cFloat tCameraM;
    cFloat tBagno;
    cFloat tLavanderia;

    // terminal 3
    cBool rPdc;
    cBool rPdcHeat;
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

    // puntatori
    cVar* webVar[100];

    BufferString m_log;

    void setup()
    {
      memset( webVar, 0, 100 * sizeof(cVar*) );

      webVar[0] = hCucina.setup            ( T1, 0, "hCucina",  50);
      webVar[1] = hSala.setup              ( T1, 1, "hSala",    50);
      webVar[2] = hCameraS.setup           ( T1, 2, "hCameraS", 50);
      webVar[3] = hCameraD.setup           ( T1, 3, "hCameraD", 50);
      webVar[4] = hCameraM.setup           ( T1, 4, "hCameraM", 50);
      webVar[5] = hBagno.setup             ( T1, 5, "hBagno",   50);

      webVar[10] = tCucina.setup           ( T1, 10, "tCucina",  20);
      webVar[11] = tSala.setup             ( T1, 11, "tSala"  ,  22);
      webVar[12] = tCameraS.setup          ( T1, 12, "tCameraS", 18);
      webVar[13] = tCameraD.setup          ( T1, 13, "tCameraD", 18);
      webVar[14] = tCameraM.setup          ( T1, 14, "tCameraM", 18);
      webVar[15] = tBagno.setup            ( T1, 15, "tBagno",   21);

      webVar[30] = rPdc.setup              ( T3, 0, "PDC");
      webVar[31] = rPdcHeat.setup          ( T3, 1, "PdcHeat");
      webVar[32] = rPdcPompa.setup         ( T3, 2, "PdcPompa");
      webVar[33] = rPdcNightMode.setup     ( T3, 3, "PdcNightMode");

      webVar[34] = rPompaPianoPrimo.setup  ( T3, 4, "PompaPianoPrimo");
      webVar[35] = rPompaPianoTerra.setup  ( T3, 5, "PompaPianoTerra");
      webVar[36] = rBoilerSanitaria.setup  ( T3, 6, "BoilerSanitaria");

      webVar[40] = tPufferHi.setup         ( T4, 0, "tPufferHi");
      webVar[41] = tPufferLow.setup        ( T4, 1, "tPufferLow");
      webVar[42] = tInputMixer.setup       ( T4, 2, "tInputMixer");
      webVar[43] = tReturnFireplace.setup  ( T4, 3, "tReturnFireplace");
      webVar[44] = tReturnFloor.setup      ( T4, 4, "tReturnFloor");
      webVar[45] = tInletFloor.setup       ( T4, 5, "tInletFloor");
      webVar[46] = tExternal.setup         ( T4, 6, "tExternal");

      webVar[50] = evCameraM1.setup        ( T5, 0, "evCameraM1");
      webVar[51] = evCameraM2.setup        ( T5, 1, "evCameraM2");
      webVar[52] = evCucina.setup          ( T5, 2, "evCucina");
      webVar[53] = evSala1.setup           ( T5, 3, "evSala1");
      webVar[54] = evSala2.setup           ( T5, 4, "evSala2");
      webVar[55] = evCameraS.setup         ( T5, 5, "evCameraS");
      webVar[56] = evCameraD1.setup        ( T5, 6, "evCameraD1");
      webVar[57] = evCameraD2.setup        ( T5, 7, "evCameraD2");

    };

    void UpdateT1( String strs )
    {
      Serial.print( "T1: " );
      Serial.println( strs);

      tCucina.update( strs );
      tSala.update( strs );
      tCameraS.update( strs );
      tCameraD.update( strs );
      tCameraM.update( strs );
      tBagno.update( strs );

      hCucina.update( strs );
      hSala.update( strs );
      hCameraS.update( strs );
      hCameraD.update( strs );
      hCameraM.update( strs );
      hBagno.update( strs );

    };

    void UpdateT3( String strs )
    {
      Serial.print( "T3: " );
      Serial.println( strs);

      rPdc.update( strs );
      rPdcHeat.update( strs );
      rPdcPompa.update( strs );
      rPdcNightMode.update( strs );

      rPompaPianoPrimo.update( strs );
      rPompaPianoTerra.update( strs );
      rBoilerSanitaria.update( strs );
    };

    void UpdateT4( String strs)
    {
      Serial.print( "T4: " );
      Serial.println( strs);

      tPufferHi.update( strs );
      tPufferLow.update( strs );
      tInputMixer.update( strs );
      tReturnFireplace.update( strs );
      tReturnFloor.update( strs );
      tInletFloor.update( strs );
      tExternal.update( strs );
    };

    void UpdateT5( String strs)
    {
      Serial.print( "T5: " );
      Serial.println( strs);

      evCameraM1.update( strs );
      evCameraM2.update( strs );
      evCucina.update( strs );
      evSala1.update( strs );
      evSala2.update( strs );
      evCameraS.update( strs );
      evCameraD1.update( strs );
      evCameraD2.update( strs );
    };

    void setPars( String &label, String &value)
    {
      for ( int i = 0; i < 100; i++ )
      {
        if ( webVar[i] != 0 && webVar[i]->descrSetPoint() == label  )
        {
          webVar[i]->setSetPoint( value.toFloat() );
        }
      }
    }

    void enumerateVals( String &labels, String &values)
    {
      for ( int i = 0; i < 100; i++ )
      {
        if ( webVar[i] != 0 )
        {
          labels += webVar[i]->descr();
          labels += ",";
          values += webVar[i]->value();
          values += ",";
        }
        else
        {
          labels += "?,";
          values += "0,";
        }
      };
    };

    void enumeratePars( String &labels, String &values)
    {
      for ( int i = 0; i < 100; i++ )
      {
        if ( webVar[i] != 0 )
        {
          labels += webVar[i]->descrSetPoint();
          labels += ",";
          values += webVar[i]->setPoint();
          values += ",";
        }
        else
        {
          labels += "?,";
          values += "0,";
        }
      };
    };

    void print( String &readable )
    {
      for ( int i = 0; i < 100; i++ )
      {
        if ( webVar[i] != 0 )
        {
          readable += "\n[";
          readable += i;
          readable += "] ";
          readable += webVar[i]->descr();
          readable += " = ";
          readable += webVar[i]->value();
        }
      };
      readable += "\n";
      for ( int i = 0; i < 100; i++ )
      {
        if ( webVar[i] != 0 )
        {
          readable += "\n(";
          readable += i;
          readable += ") ";
          readable += webVar[i]->descrSetPoint();
          readable += " = ";
          readable += webVar[i]->setPoint();
        }
      };
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
