
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Summer_Manager(int sec)
{
  _CHECK_TIME_;
  DT.m_log.add("-------------------- Summer_Manager ---------------");

  bool summerAC_pdc  = false;
  bool summerAC_pump = false;
  bool needPompa_pp  = false;
  bool allRoom = false;

  /**************************************************************************************************/
  if (DT.progSummerAC)
  {
    /**************************************************************************************************/
    // decido se accendere le pompe

    if ( DT.tPufferHi.val() < 23 )
    {
      needPompa_pp = true;      // economy
      allRoom = true;
    }
    else
    {
      if ( DT.tInletFloor.val()  > 20 )  // minima t Acqua raffreddata
      {
        summerAC_pdc = true;
        summerAC_pump = true;
        allRoom = DT.progAllRooms;
      }
      if ( DT.tReturnFloor.val()  > 21 )
      {
        summerAC_pump = true;
        allRoom = DT.progAllRooms;
      }
    }
    /**************************************************************************************************/
    DT.m_log.add("summerAC_pdc [" +  String(summerAC_pdc) + "] summerAC_pump [" +  String(summerAC_pump) + "] tInletFloor: " + DT.tInletFloor.sval() + " tSala: " + DT.tSala.sval() + " tReturnFloor: " +  DT.tReturnFloor.sval());
    DT.m_log.add("needPompa_pp [" +  String(needPompa_pp) + "] tPufferHi: " + DT.tPufferHi.sval() );
  }
  /**************************************************************************************************/
  // attuatori
  DT.evSala1.set(allRoom);
  DT.evSala2.set(allRoom);
  DT.evCucina.set(allRoom);

  DT.evCameraM1.set(summerAC_pump || allRoom);
  DT.evCameraM2.set(summerAC_pump || allRoom);
  DT.evCameraS.set (summerAC_pump || allRoom);
  DT.evCameraD1.set(summerAC_pump || allRoom);
  DT.evCameraD2.set(summerAC_pump || allRoom);

  DT.rPompaPianoPrimo.set( needPompa_pp );

  /**************************************************************************************************/
  // accendo PDC
  DT.rPdc.set( summerAC_pdc );
  DT.rPdcNightMode.set( summerAC_pdc );
  DT.rPdcHeat.set( false );
  DT.rPdcPompa.set( summerAC_pump );
  /**************************************************************************************************/
}

/******************************************************************************************************************************************************************/
void Winter_Manager( int sec )
{
  _CHECK_TIME_;
  DT.m_log.add("-------------------- Winter_Manager --------------------");

  bool sala = false;
  bool sala2 = false;
  bool cucina = false;
  bool cameraS = false;
  bool cameraD = false;
  bool cameraD2 = false;
  bool cameraM = false;
  bool cameraM2 = false;
  bool bagno = false;

  bool needPompa_pt = false;
  bool needPompa_pp = false;
  bool needPdc = false;
  bool needPCamino = false;

  bool allRoom = DT.progAllRooms || DT.progWinterPDC_ALLROOMS;

  if (DT.progWinterFIRE || DT.progWinterPDC || DT.progWinterPDC_ALLROOMS || DT.progWinterPDC_FOTOV)
  {
    //////////////////////////////////////////////////////////////////////////////////
    //decido se accendere le stanze
    String str = "Condizione";
    if ( DT.tSala < DT.tSala.setPoint() )
    {
      str += " tSala " + String(DT.tSala) + " < " + String(DT.tSala.setPoint());
      sala = true;
    }
    if ( DT.tSala < DT.tSala.setPoint() - 1 )
    {
      sala2 = true;
    }
    if ( DT.tCucina < DT.tCucina.setPoint() )
    {
      str += " tCucina " + String(DT.tCucina) + " < " + String(DT.tCucina.setPoint());
      cucina = true;
    }
    if ( DT.tCameraS < DT.tCameraS.setPoint() )
    {
      str += " tCameraS " + String(DT.tCameraS) + " < " + String(DT.tCameraS.setPoint());
      cameraS = true;
    }
    if ( DT.tCameraD < DT.tCameraD.setPoint() )
    {
      str += " tCameraD " + String(DT.tCameraD) + " < " + String(DT.tCameraD.setPoint());
      cameraD = true;
    }
    if ( DT.tCameraD < DT.tCameraD.setPoint() - 2 )
    {
      cameraD2 = true;
    }
    if ( DT.tCameraM < DT.tCameraM.setPoint() )
    {
      str += " tCameraM " + String(DT.tCameraM) + " < " + String(DT.tCameraM.setPoint());
      cameraM = true;
    }
    if ( DT.tCameraM < DT.tCameraM.setPoint() - 2 )
    {
      cameraM2 = true;
    }
    if ( DT.tBagno < DT.tBagno.setPoint() )
    {
      str += " tBagno " + String(DT.tBagno) + " < " + String(DT.tBagno.setPoint());
      bagno = true;
    }
    DT.m_log.add(str);

    //////////////////////////////////////////////////////////////////////////////////
    // decido se accendere/spegnere pompa piano primo
    needPompa_pp = ( sala || cucina || bagno || cameraS || cameraD || cameraM );
    if ( DT.tInputMixer < 28 && DT.tPufferHi < 28 && DT.tReturnFireplace < 28 )   // non ho temperatura
    {
      DT.m_log.add("Condizione Pompa PP insufficiente: tInletFloor: " + String(DT.tInletFloor) + " tReturnFloor: " + String(DT.tReturnFloor) );
      needPompa_pp = false;
    }
    if ( (DT.tReturnFloor > 28) )  // ritorno troppo alto - non ne ho bisogno
    {
      DT.m_log.add("Stop Pompa: ritorno troppo alto tReturnFloor: " + String(DT.tReturnFloor) );
      needPompa_pp = false;
    }
    if ( DT.tInletFloor > 35 )  // 35 è la sicurezza dopo al quale spengo la pompa
    {
      DT.m_log.add("Stop Pompa: Sicurezza temp ingreso impianto: tInletFloor: " + String(DT.tInletFloor) + " > 35" );
      needPompa_pp = false;
    }
    if ( DT.tReturnFireplace < 35 && hour() < 5 ) // fuori oario
    {
      DT.m_log.add("Stop Pompa: orario " + String( hour() ) );
      needPompa_pp = false;
    }
    if ( DT.tPufferLow > 55 )   // emergenza
    {
      DT.m_log.add("Emergenza tPufferLow > 55 ");
      needPompa_pp = true;
      needPompa_pt = true;
      allRoom = true;
    }
    DT.m_log.add( "NeedPompa_pp: [" + String(needPompa_pp) + "]" );

    //////////////////////////////////////////////////////////////////////////////////
    //decido se accendere PDC
    needPdc = DT.progWinterPDC && ( sala || cucina || bagno );
    needPdc = needPdc || ( DT.progWinterPDC_ALLROOMS );
    needPdc = needPdc || ( DT.progWinterPDC_FOTOV );

    if ( needPompa_pp )
    {
      DT.m_log.add("PDC suspended - Fire enought ");
      needPdc = false;
    }
    DT.m_log.add( "NeedPdc: [" + String(needPdc) + "]" );

    //////////////////////////////////////////////////////////////////////////////////
    // decido se accendere pompa camino
    DT.m_log.add("Condizione Pompa Camino: tReturnFireplace " + String(DT.tReturnFireplace) + " - " + "tPufferLow " + String(DT.tPufferLow) );
    if ( DT.tPufferLow < 45 && DT.tReturnFireplace > 34 && DT.tReturnFireplace > DT.tPufferLow + 5 )
    {
      needPCamino = true;
    }
    DT.m_log.add( "NeedPCamino: [" + String(needPCamino) + "]" );

    //////////////////////////////////////////////////////////////////////////////////
    // decido se accendere piano terra
    if ( DT.tPufferLow > 45 && DT.tReturnFireplace > 45 )
    {
      DT.m_log.add("Condizione DT.tPufferLow > 45 && DT.tReturnFireplace > 45");
      needPompa_pt = true;
    }
    DT.m_log.add( "NeedPompa_pt: [" + String(needPompa_pt) + "]" );

    //////////////////////////////////////////////////////////////////////////////////
    // decido se attivare le elettrovalbole primo piano
    bool NeedEv = false;
    if ( DT.tInletFloor > 25 )
    {
      NeedEv = true;
    }
    DT.m_log.add( "NeedEv: [" + String(NeedEv) + "]" );

    cameraM   = (cameraM &&  NeedEv) || allRoom;
    cameraM2  = (cameraM2 && NeedEv);
    sala      = (sala && NeedEv) || allRoom;
    sala2     = (sala2 && NeedEv) || allRoom;
    cucina    = (cucina && NeedEv) || allRoom;
    cameraS   = (cameraS && NeedEv) || allRoom;
    cameraD   = (cameraD && NeedEv) || allRoom;
    cameraD2  = (cameraD2 && NeedEv);
  }

  //**********************************************************************
  // attuatori -----------------------------------------------------------------------
  DT.evCameraM1.set(cameraM);
  DT.evCameraM2.set(cameraM2);
  DT.evSala1.set(sala);
  DT.evSala2.set(sala2);
  DT.evCucina.set(cucina);
  DT.evCameraS.set(cameraS);
  DT.evCameraD1.set(cameraD);
  DT.evCameraD2.set(cameraD2);

  // comandi semimanuali centrale -----------------------------------------------------
  // accendo pompa pp
  DT.rPompaPianoPrimo.set( needPompa_pp );
  //piano terra
  DT.rPompaPianoTerra.set( needPompa_pt );
  // accendo PDC
  DT.rPdc.set( needPdc );
  // heat
  DT.rPdcHeat.set( needPdc );
  //pompa
  DT.rPdcPompa.set( needPdc );
  //night
  DT.rPdcNightMode.set( needPdc );
  //camino
  DT.rPompaCamino.set( needPCamino );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BoilerACS_Manager(int sec)
{
  _CHECK_TIME_;
  DT.m_log.add(">> ------------------- BoilerACS_Manager --------------- >>");

  bool boilerACS = false;
  /**************************************************************************************************/
  if (DT.progBoilerACS)
  {
    //decido se accendere il boiler se ho un surplus di energia
    if ( DT.rBoilerACS && DT.surplusWatt() > 100 ||
         DT.rBoilerACS && DT.surplusWatt() > 600 )
    {
      boilerACS = true;
      DT.m_log.add("Condizione ON surplusW:" + String(DT.surplusWatt()) );
    }    
    //decido se accendere il boiler solo a mezzogiorno e solo se il camino non funziona
    if ( hour() > 12 && hour() < 16  )
    {
      boilerACS = true;
      DT.m_log.add("Condizione ON hour:" + String( hour() ) + " >12 & <16");
    }
    if ( DT.tReturnFireplace > 30 )
    {
      boilerACS = false;
      DT.m_log.add("Condizione OFF DT.ReturnFireplace:" + String( DT.tReturnFireplace ) + "> 30");
    }
  }
  /**************************************************************************************************/
  // boiler
  DT.m_log.add("BoilerACS [" + String( boilerACS ) + "]");
  DT.rBoilerACS.set( boilerACS );
  DT.m_log.add("<<< BoilerACS_Manager <<<");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ExternalLight_Manager(int sec)
{
  _CHECK_TIME_;
  DT.m_log.add(">>-------------------- ExternalLight_Manager -------------------->>");

  bool lightSide = false;
  bool lightLamp = false;

  if (DT.progExternalLight)
  {
    /**************************************************************************************************/
    DT.m_log.add("-- darkExternal: " + DT.darkExternal.sval() + " Request [" + String( 35 - 1 * DT.lightSide.val()) + "]" );
    if ( DT.darkExternal > 35 - 1 * DT.lightSide.val() ) // isteresi
    {
      lightSide = true;
      lightLamp = true;
    }

    /**************************************************************************************************/
    DT.m_log.add("-- LightLamp [" +  String(lightLamp) + "]  LightSide [" +  String(lightSide) + "]" );
  }

  // attuatori
  DT.lightCorner.set(lightSide);
  DT.lightSide.set(lightSide);
  DT.lightLamp.set(lightLamp);
  DT.lightExtra.set(lightLamp);

  DT.m_log.add("<<< ExternalLight_Manager <<<");
}
