#pragma once
#include "DataVars.h"

//********************************************************************************************
class cDataTable
{
  public:
    cBool progBoilerACS;
    cBool progSummerAC;
    cBool progWinterFIRE;
    cBool progWinterPDC;
    cBool progAllRooms;
    cBool prog5;

    enum { PROG = -1, T0 = 0, T1 = 1, T2 = 2, T3 = 3, T4 = 4, T5 = 5, T6 = 6, T7 = 7 };

  public:
    // terminal 1
    cFloat tCucina;
    cFloat tSala;
    cFloat tCameraS;
    cFloat tCameraD;
    cFloat tCameraM;
    cFloat tBagno;
    cFloat tLavanderia;

    cFloat hCucina;
    cFloat hSala;
    cFloat hCameraS;
    cFloat hCameraD;
    cFloat hCameraM;
    cFloat hBagno;
    cFloat hLavanderia;

    cFloat thCucina;
    cFloat thSala;
    cFloat thCameraS;
    cFloat thCameraD;
    cFloat thCameraM;
    cFloat thBagno;
    cFloat thLavanderia;

    // terminal 2
    cBool lightCorner;
    cBool lightSide;
    cBool lightLamp;
    cBool lightExtra;

    // terminal 3
    cBool rPdc;
    cBool rPdcHeat;
    cBool rPdcPompa;
    cBool rPdcNightMode;
    cBool rPompaPianoPrimo;
    cBool rPompaPianoTerra;
    cBool rBoilerACS;
    cBool rPompaCamino;

    // terminal 4
    cFloat tPufferHi;
    cFloat tPufferLow;
    cFloat tInputMixer;
    cFloat tReturnFireplace;
    cFloat tReturnFloor;
    cFloat tInletFloor;
    cFloat tExternal;
    cFloat lightExternal;

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

      webVar[0] = tCucina.setup           ( T1, 0, "tCucina",  21);
      webVar[1] = tSala.setup             ( T1, 1, "tSala"  ,  23);
      webVar[2] = tCameraS.setup          ( T1, 2, "tCameraS", 18);
      webVar[3] = tCameraD.setup          ( T1, 3, "tCameraD", 18);
      webVar[4] = tCameraM.setup          ( T1, 4, "tCameraM", 18);
      webVar[5] = tBagno.setup            ( T1, 5, "tBagno",   22);
      tCucina.setAdjust(-0.5);
      tSala.setAdjust(1.5);
      tCameraS.setAdjust(0);
      tCameraD.setAdjust(1);
      tCameraM.setAdjust(1);
      tBagno.setAdjust(2);

      webVar[8 + 0] = hCucina.setup         ( T1, 8 + 0, "hCucina"  );
      webVar[8 + 1] = hSala.setup           ( T1, 8 + 1, "hSala"    );
      webVar[8 + 2] = hCameraS.setup        ( T1, 8 + 2, "hCameraS" );
      webVar[8 + 3] = hCameraD.setup        ( T1, 8 + 3, "hCameraD" );
      webVar[8 + 4] = hCameraM.setup        ( T1, 8 + 4, "hCameraM" );
      webVar[8 + 5] = hBagno.setup          ( T1, 8 + 5, "hBagno"   );

      webVar[16 + 0] = thCucina.setup       ( T1, 16 + 0, "thCucina",  21);
      webVar[16 + 1] = thSala.setup         ( T1, 16 + 1, "thSala",    22);
      webVar[16 + 2] = thCameraS.setup      ( T1, 16 + 2, "thCameraS", 18);
      webVar[16 + 3] = thCameraD.setup      ( T1, 16 + 3, "thCameraD", 18);
      webVar[16 + 4] = thCameraM.setup      ( T1, 16 + 4, "thCameraM", 18);
      webVar[16 + 5] = thBagno.setup        ( T1, 16 + 5, "thBagno",   22);

      webVar[20] = lightCorner.setup        ( T2, 0, "LuciAngoli");
      webVar[21] = lightSide.setup          ( T2, 1, "LuciLati");
      webVar[22] = lightLamp.setup          ( T2, 2, "Lampione");
      webVar[23] = lightExtra.setup         ( T3, 3, "Altro");

      webVar[30] = rPdc.setup               ( T3, 0, "PDC");
      webVar[31] = rPdcHeat.setup           ( T3, 1, "PdcHeat");
      webVar[32] = rPdcPompa.setup          ( T3, 2, "PdcPompa");
      webVar[33] = rPdcNightMode.setup      ( T3, 3, "PdcNightMode");

      webVar[34] = rPompaPianoPrimo.setup   ( T3, 4, "PompaPianoPrimo");
      webVar[35] = rPompaPianoTerra.setup   ( T3, 5, "PompaPianoTerra");
      webVar[36] = rBoilerACS.setup         ( T3, 6, "BoilerACS");
      webVar[37] = rPompaCamino.setup       ( T3, 7, "PompaCamino");

      webVar[40] = tPufferHi.setup          ( T4, 0, "tPufferHi");
      webVar[41] = tPufferLow.setup         ( T4, 1, "tPufferLow");
      webVar[42] = tInputMixer.setup        ( T4, 2, "tInputMixer");
      webVar[43] = tReturnFireplace.setup   ( T4, 3, "tReturnFireplace");
      webVar[44] = tReturnFloor.setup       ( T4, 4, "tReturnFloor");
      webVar[45] = tInletFloor.setup        ( T4, 5, "tInletFloor");
      webVar[46] = tExternal.setup          ( T4, 6, "tExternal");
      webVar[47] = lightExternal.setup      ( T4, 8, "lightExternal");

      webVar[50] = evCameraM1.setup         ( T5, 0, "evCameraM1");
      webVar[51] = evCameraM2.setup         ( T5, 1, "evCameraM2");
      webVar[52] = evCucina.setup           ( T5, 2, "evCucina");
      webVar[53] = evSala1.setup            ( T5, 3, "evSala1");
      webVar[54] = evSala2.setup            ( T5, 4, "evSala2");
      webVar[55] = evCameraS.setup          ( T5, 5, "evCameraS");
      webVar[56] = evCameraD1.setup         ( T5, 6, "evCameraD1");
      webVar[57] = evCameraD2.setup         ( T5, 7, "evCameraD2");

      webVar[90] = progBoilerACS.setup      ( PROG, 0, "progBoilerACS");
      webVar[91] = progSummerAC.setup       ( PROG, 0, "progSummerAC");
      webVar[92] = progWinterFIRE.setup     ( PROG, 0, "progWinterFIRE");
      webVar[93] = progWinterPDC.setup      ( PROG, 0, "progWinterPDC");
      webVar[94] = progAllRooms.setup       ( PROG, 0, "progAllRooms");
      webVar[95] = prog5.setup              ( PROG, 0, "prog5");

    };

    void UpdateT1( String strs )
    {
      m_log.add("**T1** ");
      m_log.add(strs);

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

      thCucina.update( strs );
      thSala.update( strs );
      thCameraS.update( strs );
      thCameraD.update( strs );
      thCameraM.update( strs );
      thBagno.update( strs );
    };

    void UpdateT2( String strs )
    {
      m_log.add("**T2** ");
      m_log.add(strs);
    };

    void UpdateT3( String strs )
    {
      m_log.add("**T3** ");
      m_log.add(strs);

      rPdc.update( strs );
      rPdcHeat.update( strs );
      rPdcPompa.update( strs );
      rPdcNightMode.update( strs );

      rPompaPianoPrimo.update( strs );
      rPompaPianoTerra.update( strs );
      rBoilerACS.update( strs );
      rPompaCamino.update( strs );
    };

    void UpdateT4( String strs)
    {
      m_log.add("**T4** ");
      m_log.add(strs);

      tPufferHi.update( strs );
      tPufferLow.update( strs );
      tInputMixer.update( strs );
      tReturnFireplace.update( strs );
      tReturnFloor.update( strs );
      tInletFloor.update( strs );
      tExternal.update( strs );
      lightExternal.update( strs );
    };

    void UpdateT5( String strs)
    {
      m_log.add("**T5** ");
      m_log.add(strs);

      evCameraM1.update( strs );
      evCameraM2.update( strs );
      evCucina.update( strs );
      evSala1.update( strs );
      evSala2.update( strs );
      evCameraS.update( strs );
      evCameraD1.update( strs );
      evCameraD2.update( strs );
    };

    void UpdateT6( String strs )
    {
      m_log.add("**T6** ");
      m_log.add(strs);
    };

    void UpdateT7( String strs )
    {
      m_log.add("**T7** ");
      m_log.add(strs);
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
