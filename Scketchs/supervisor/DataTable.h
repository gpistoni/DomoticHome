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
    cBool progWinterPDC_ECO;
    cBool progAllRooms;
    cBool progExternalLight;

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

    // terminal 6
    cFloat aTotal[3];
    cFloat aL1[3];
    cFloat aL2[3];
    cFloat aL3[3];
    cFloat aM[3];
    cFloat aN[3];

    // puntatori
    cVar* webVar[100];

    BufferString m_log;

    void setup()
    {
      memset( webVar, 0, 100 * sizeof(cVar*) );

      webVar[0] = tCucina.setup           ( T1, 0, "tCucina",  21);
      webVar[1] = tSala.setup             ( T1, 1, "tSala"  ,  23);
      webVar[2] = tCameraS.setup          ( T1, 2, "tCameraS", 17.5);
      webVar[3] = tCameraD.setup          ( T1, 3, "tCameraD", 17.5);
      webVar[4] = tCameraM.setup          ( T1, 4, "tCameraM", 17);
      webVar[5] = tBagno.setup            ( T1, 5, "tBagno",   23);
      tCucina.setAdjust(-0.5);
      tSala.setAdjust(1.5);
      tCameraS.setAdjust(1);
      tCameraD.setAdjust(0.5);
      tCameraM.setAdjust(1);
      tBagno.setAdjust(2);

      webVar[8 + 0] = hCucina.setup         ( T1, 8 + 0, "hCucina"  );
      webVar[8 + 1] = hSala.setup           ( T1, 8 + 1, "hSala"    );
      webVar[8 + 2] = hCameraS.setup        ( T1, 8 + 2, "hCameraS" );
      webVar[8 + 3] = hCameraD.setup        ( T1, 8 + 3, "hCameraD" );
      webVar[8 + 4] = hCameraM.setup        ( T1, 8 + 4, "hCameraM" );
      webVar[8 + 5] = hBagno.setup          ( T1, 8 + 5, "hBagno"   );

      webVar[16 + 0] = thCucina.setup       ( T1, 16 + 0, "thCucina");
      webVar[16 + 1] = thSala.setup         ( T1, 16 + 1, "thSala");
      webVar[16 + 2] = thCameraS.setup      ( T1, 16 + 2, "thCameraS");
      webVar[16 + 3] = thCameraD.setup      ( T1, 16 + 3, "thCameraD");
      webVar[16 + 4] = thCameraM.setup      ( T1, 16 + 4, "thCameraM");
      webVar[16 + 5] = thBagno.setup        ( T1, 16 + 5, "thBagno");

      webVar[25] = lightCorner.setup        ( T2, 0, "LuciAngoli");
      webVar[26] = lightSide.setup          ( T2, 1, "LuciLati");
      webVar[27] = lightLamp.setup          ( T2, 2, "Lampione");
      webVar[28] = lightExtra.setup         ( T2, 3, "Altro");

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

      webVar[60] = aTotal[0].setup             ( T6, 0, "Total");
      webVar[61] = aL1[0].setup                ( T6, 1, "L1");
      webVar[62] = aL2[0].setup                ( T6, 2, "L2");
      webVar[63] = aL3[0].setup                ( T6, 3, "L3");
      webVar[64] = aM[0].setup                 ( T6, 4, "M");
      webVar[65] = aN[0].setup                 ( T6, 5, "N");

      webVar[60+8] = aTotal[1].setup             ( T6, 8 + 0, "wTotal");
      webVar[61+8] = aL1[1].setup                ( T6, 8 + 1, "wL1");
      webVar[62+8] = aL2[1].setup                ( T6, 8 + 2, "wL2");
      webVar[63+8] = aL3[1].setup                ( T6, 8 + 3, "wL3");
      webVar[64+8] = aM[1].setup                 ( T6, 8 + 4, "wM");
      webVar[65+8] = aN[1].setup                 ( T6, 8 + 5, "wN");

      webVar[60+16] = aTotal[2].setup             ( T6, 16 + 0, "whTotal");
      webVar[61+16] = aL1[2].setup                ( T6, 16 + 1, "whL1");
      webVar[62+16] = aL2[2].setup                ( T6, 16 + 2, "whL2");
      webVar[63+16] = aL3[2].setup                ( T6, 16 + 3, "whL3");
      webVar[64+16] = aM[2].setup                 ( T6, 16 + 4, "whM");
      webVar[65+16] = aN[2].setup                 ( T6, 16 + 5, "whN");

      webVar[90] = progBoilerACS.setup      ( PROG, 0, "progBoilerACS");
      webVar[91] = progSummerAC.setup       ( PROG, 0, "progSummerAC");
      webVar[92] = progWinterFIRE.setup     ( PROG, 0, "progWinterFIRE");
      webVar[93] = progWinterPDC.setup      ( PROG, 0, "progWinterPDC");
      webVar[94] = progWinterPDC_ECO.setup  ( PROG, 0, "progWinterPDC_ECO");
      webVar[95] = progAllRooms.setup       ( PROG, 0, "progAllRooms");
      webVar[96] = progExternalLight.setup  ( PROG, 0, "progExternalLight");

    };

    void UpdateT1( String strs )
    {
      m_log.add("**T1-GET-tStanze** ");
      m_log.add(strs);

      tCucina.updateNz( strs );
      tSala.updateNz( strs );
      tCameraS.updateNz( strs );
      tCameraD.updateNz( strs );
      tCameraM.updateNz( strs );
      tBagno.updateNz( strs );

      hCucina.updateNz( strs );
      hSala.updateNz( strs );
      hCameraS.updateNz( strs );
      hCameraD.updateNz( strs );
      hCameraM.updateNz( strs );
      hBagno.updateNz( strs );

      thCucina.updateNz( strs );
      thSala.updateNz( strs );
      thCameraS.updateNz( strs );
      thCameraD.updateNz( strs );
      thCameraM.updateNz( strs );
      thBagno.updateNz( strs );
    };

    void UpdateT2( String strs )
    {
      m_log.add("**T2-SET-Luci** ");
      m_log.add(strs);
    };

    void UpdateT3( String strs )
    {
      m_log.add("**T3-SET-Caldaia** ");
      m_log.add(strs);
    };

    void UpdateT4( String strs)
    {
      m_log.add("**T4-GET-tCaldaia** ");
      m_log.add(strs);

      tPufferHi.updateNz( strs );
      tPufferLow.updateNz( strs );
      tInputMixer.updateNz( strs );
      tReturnFireplace.updateNz( strs );
      tReturnFloor.updateNz( strs );
      tInletFloor.updateNz( strs );
      tExternal.updateNz( strs );
      lightExternal.updateNz( strs );
    };

    void UpdateT5( String strs)
    {
      m_log.add("**T5-SET-EvStanze** ");
      m_log.add(strs);
    };

    void UpdateT6( String strs )
    {
      m_log.add("**T6-GET-Amperometri** ");
      m_log.add(strs);

      for (int i = 0; i < 3; i++)
      {
        aTotal[i].updateNz( strs );
        aL1[i].updateNz( strs );
        aL2[i].updateNz( strs );
        aL3[i].updateNz( strs );
        aM[i].updateNz( strs );
        aN[i].updateNz( strs );
      }
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
