#pragma once
#include "DataVars.h"

//********************************************************************************************
class cDataTable
{
  public:
    cBool progBoilerACS;
    cBool progSummerAC;
    cBool progSummerAC_NIGHT;
    cBool progWinterFIRE;
    cBool progWinterPDC;
    cBool progWinterPDC_ALLROOMS;
    cBool progWinterPDC_FOTOV;
    cBool progAllRooms;
    cBool progExternalLight;

  public:
    // terminal 1
    cVar tCucina;
    cVar tSala;
    cVar tCameraS;
    cVar tCameraD;
    cVar tCameraM;
    cVar tBagno;
    cVar tLavanderia;

    cVar hCucina;
    cVar hSala;
    cVar hCameraS;
    cVar hCameraD;
    cVar hCameraM;
    cVar hBagno;
    cVar hLavanderia;

    cVar thCucina;
    cVar thSala;
    cVar thCameraS;
    cVar thCameraD;
    cVar thCameraM;
    cVar thBagno;
    cVar thLavanderia;

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
    cVar tPufferHi;
    cVar tPufferLow;
    cVar tInputMixer;
    cVar tReturnFireplace;
    cVar tReturnFloor;
    cVar tInletFloor;
    cVar tExternal;
    cVar darkExternal;

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
    cVar aProduced[3];
    cVar aInput[3];
    cVar aL1[3];
    cVar aL2[3];
    cVar aL3[3];

    // puntatori
    cVar* webVar[100];

    BufferString m_log;

    void setup()
    {
      memset( webVar, 0, 100 * sizeof(cVar*) );

      webVar[0] = tCucina.setup           ( "T1", "v0", "", "tCucina",  21);
      webVar[1] = tSala.setup             ( "T1", "v1", "", "tSala"  ,  23);
      webVar[2] = tCameraS.setup          ( "T1", "v2", "", "tCameraS", 18);
      webVar[3] = tCameraD.setup          ( "T1", "v3", "", "tCameraD", 18);
      webVar[4] = tCameraM.setup          ( "T1", "v4", "", "tCameraM", 16);
      webVar[5] = tBagno.setup            ( "T1", "v5", "", "tBagno",   23);
      tCucina.setAdjust(-0.5);
      tSala.setAdjust(1.5);
      tCameraS.setAdjust(1);
      tCameraD.setAdjust(0.5);
      tCameraM.setAdjust(1);
      tBagno.setAdjust(2.5);

      webVar[8 + 0] = hCucina.setup         ( "T1", "v8", "", "hCucina"   );
      webVar[8 + 1] = hSala.setup           ( "T1", "v9", "", "hSala"     );
      webVar[8 + 2] = hCameraS.setup        ( "T1", "v10", "", "hCameraS" );
      webVar[8 + 3] = hCameraD.setup        ( "T1", "v11", "", "hCameraD" );
      webVar[8 + 4] = hCameraM.setup        ( "T1", "v12", "", "hCameraM" );
      webVar[8 + 5] = hBagno.setup          ( "T1", "v13", "", "hBagno"   );

      webVar[16 + 0] = thCucina.setup       ( "T1", "v16", "", "thCucina" );
      webVar[16 + 1] = thSala.setup         ( "T1", "v17", "", "thSala"   );
      webVar[16 + 2] = thCameraS.setup      ( "T1", "v18", "", "thCameraS");
      webVar[16 + 3] = thCameraD.setup      ( "T1", "v19", "", "thCameraD");
      webVar[16 + 4] = thCameraM.setup      ( "T1", "v20", "", "thCameraM");
      webVar[16 + 5] = thBagno.setup        ( "T1", "v21", "", "thBagno"  );

      webVar[25] = lightCorner.setup        ( "T2", "", "r0", "LuciAngoli");
      webVar[26] = lightSide.setup          ( "T2", "", "r1", "LuciLati");
      webVar[27] = lightLamp.setup          ( "T2", "", "r2", "Lampione");
      webVar[28] = lightExtra.setup         ( "T2", "", "r3", "Altro");

      webVar[30] = rPdc.setup               ( "T3", "", "r0", "PDC");
      webVar[31] = rPdcHeat.setup           ( "T3", "", "r1", "PdcHeat");
      webVar[32] = rPdcPompa.setup          ( "T3", "", "r2", "PdcPompa");
      webVar[33] = rPdcNightMode.setup      ( "T3", "", "r3", "PdcNightMode");
      webVar[34] = rPompaPianoPrimo.setup   ( "T3", "", "r4", "PompaPianoPrimo");
      webVar[35] = rPompaPianoTerra.setup   ( "T3", "", "r5", "PompaPianoTerra");
      webVar[36] = rBoilerACS.setup         ( "T3", "", "r6", "BoilerACS");
      webVar[37] = rPompaCamino.setup       ( "T3", "", "r7", "PompaCamino");

      webVar[40] = tPufferHi.setup          ( "T4", "v0", "", "tPufferHi");
      webVar[41] = tPufferLow.setup         ( "T4", "v1", "", "tPufferLow");
      webVar[42] = tInputMixer.setup        ( "T4", "v2", "", "tInputMixer");
      webVar[43] = tReturnFireplace.setup   ( "T4", "v3", "", "tReturnFireplace");
      webVar[44] = tReturnFloor.setup       ( "T4", "v4", "", "tReturnFloor");
      webVar[45] = tInletFloor.setup        ( "T4", "v5", "", "tInletFloor");
      webVar[46] = tExternal.setup          ( "T4", "v6", "", "tExternal");
      webVar[47] = darkExternal.setup       ( "T4", "v8", "", "darkExternal");

      webVar[50] = evCameraM1.setup         ( "T5", "", "r0", "evCameraM1");
      webVar[51] = evCameraM2.setup         ( "T5", "", "r1", "evCameraM2");
      webVar[52] = evCucina.setup           ( "T5", "", "r2", "evCucina");
      webVar[53] = evSala1.setup            ( "T5", "", "r3", "evSala1");
      webVar[54] = evSala2.setup            ( "T5", "", "r4", "evSala2");
      webVar[55] = evCameraS.setup          ( "T5", "", "r5", "evCameraS");
      webVar[56] = evCameraD1.setup         ( "T5", "", "r6", "evCameraD1");
      webVar[57] = evCameraD2.setup         ( "T5", "", "r7", "evCameraD2");

      webVar[60] = aProduced[0].setup           ( "T6", "v0", "", "aProduced");
      webVar[61] = aInput[0].setup              ( "T6", "v1", "", "aInput");
      webVar[62] = aL1[0].setup                 ( "T6", "v2", "", "aL1");
      webVar[63] = aL2[0].setup                 ( "T6", "v3", "", "aL2");
      webVar[64] = aL3[0].setup                 ( "T6", "v4", "", "aL3");

      webVar[60 + 8] = aProduced[1].setup       ( "T6", "v8", "", "whProduced");
      webVar[61 + 8] = aInput[1].setup          ( "T6", "v9", "", "whInput");
      webVar[62 + 8] = aL1[1].setup             ( "T6", "v10", "", "whL1");
      webVar[63 + 8] = aL2[1].setup             ( "T6", "v11", "", "whL2");
      webVar[64 + 8] = aL3[1].setup             ( "T6", "v12", "", "whL3");

      webVar[60 + 16] = aProduced[2].setup      ( "T6", "v16", "", "tProduced");
      webVar[61 + 16] = aInput[2].setup         ( "T6", "v17", "", "tInput");
      webVar[62 + 16] = aL1[2].setup            ( "T6", "v18", "", "tL1");
      webVar[63 + 16] = aL1[2].setup            ( "T6", "v19", "", "tL2");
      webVar[64 + 16] = aL3[2].setup            ( "T6", "v20", "", "tL3");

      webVar[90] = progBoilerACS.setup          ( "PRG", "", "", "progBoilerACS");
      webVar[91] = progSummerAC.setup           ( "PRG", "", "", "progSummerAC");
      webVar[92] = progSummerAC_NIGHT.setup     ( "PRG", "", "", "progSummerAC_NIGHT");
      webVar[93] = progWinterFIRE.setup         ( "PRG", "", "", "progWinterFIRE");
      webVar[94] = progWinterPDC.setup          ( "PRG", "", "", "progWinterPDC");
      webVar[95] = progWinterPDC_ALLROOMS.setup ( "PRG", "", "", "progWinterPDC_ALLROOMS");
      webVar[96] = progWinterPDC_FOTOV.setup    ( "PRG", "", "", "progWinterPDC_FOTOV");
      webVar[97] = progAllRooms.setup           ( "PRG", "", "", "progAllRooms");
      webVar[98] = progExternalLight.setup      ( "PRG", "", "", "progExternalLight");
    };

    void UpdateALL( const JsonObject& values )
    {
      for ( int i = 0; i < 100; i++ )
      {
        if ( webVar[i] != 0 )
        {
          String sT = webVar[i]-> terminal();
          String sVal = webVar[i]-> idxvalue();

          //controllo se esiste il valore
          if (sVal!="")
          {
            webVar[i]->set( values[sT][sVal] );
          }

          //m_log.add( String("UpdateALL** ") + sT + " - " + sVal + ": "+ val);
        }
      }
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

    float getPars( String &label)
    {
      for ( int i = 0; i < 100; i++ )
      {
        if ( webVar[i] != 0 && webVar[i]->descrSetPoint() == label  )
        {
          return webVar[i]->val();
        }
      }
      return 0;
    }

    float getValue( String &label)
    {
      for ( int i = 0; i < 100; i++ )
      {
        if ( webVar[i] != 0) Serial.println(webVar[i]->descr());
        //Serial.println(val);

        if ( webVar[i] != 0 && webVar[i]->descr() == label  )
        {
          return webVar[i]->val();
        }
      }
      return 0;
    }

    void print( String &readable )
    {
      for ( int i = 0; i < 100; i++ )
      {
        if ( webVar[i] != 0 )
        {
          readable += "<br>[";
          readable += i;
          readable += "] ";
          readable += webVar[i]->descr();
          readable += " = ";
          readable += webVar[i]->val();
        }
      };
      readable += "<br>";
      for ( int i = 0; i < 100; i++ )
      {
        if ( webVar[i] != 0 )
        {
          readable += "<br>(";
          readable += i;
          readable += ") ";
          readable += webVar[i]->descrSetPoint();
          readable += " = ";
          readable += webVar[i]->setPoint();
        }
      };
    };

    // calcoli
    int surplusWatt()
    {
      int consumed = aL1[0].val() + aL2[0].val() + aL3[0].val();
      int produced = aProduced[0];

      return ( produced - consumed ) * 233;
    };
};
