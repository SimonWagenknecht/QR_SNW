/* ------------ Parameterliste  Parli -------------------------- */

/* Aufbau eines Parameters in einer Parametergruppe:
   - num        Parameternummer    ( 4 Byte ASCII),
   - bez        Bezeichnung        (16 Byte ASCII),
   - dim        Dimension          ( 7 Byte ASCII),
   - *label     Zeiger auf Variable,
   - konv       Konvertierungsname
   - attr       Attribut (Kommastelle etc.)
   - *vis				Sichtbarkeit
   - ktab				Komtab-Eintrag
   - alclass		Alarm-Klasse
   - alfunc			Alarm-Funktion
*/   

// Konvertierungsnamen: siehe konvform.h

/* Auflistung aller Parametergruppen    */

/*------------------------------ Anlage --------------------------------------------------*/
const Pgrup anl[] = {
	#if VARIPROJ == 0
	{"***:"," RIEDEL  R66E   ","       ", P&Kategorie_Typ,				ASCII_FORM, 0, P&vis,		V1, 0, 0},
	#else
	{"***:"," RIEDEL  R66E   ","       ", P&KatVar_Typ,						ASCII_FORM, 0, P&vis,		V1, 0, 0},// Variable Kategorie
	#endif

	{" 01:"," UHRZEIT        ","       ",				0,									UHR_FORM, 0, P&vis,		V1, 0, 0},
	{" 02:"," DATUM          ","       ",				0,								DATUM_FORM, 0, P&vis,		V1, 0, 0},
	{"*03:"," BETRIEBSSTUNDEN"," h     ", P&bst,											US_INT, 0, P&vis,		V1, 0, 0},

	{"*09."," ANZEIGE-TAFEL  ","       ", P&Leer15,							ASCII_FORM, 0, P&hid4,		V0, 0, 0},
	{"*->."," KOLLEKTOR   TS1"," C    ", P&TS1_[0],						 ANA_FORMP, 1, P&hid4,		V1, 0, 0},
	{"*->."," PUFFER o TSPo-P"," C    ", P&TS6_[0],						 ANA_FORMP, 1, P&hid4,		V1, 0, 0},
  {"*->."," LEISTUNG    P2 "," kW    ", P&wmengCtr[2].wmLeistg,		US_INT,	0, P&hid4,		V1, 0, 0},
  {"*->."," Q2 - KOLLEKTOR "," kWh   ", P&wmengCtr[2].wmeng,		US_LONG,	0, P&hid4,		V1, 0, 0},
  {"*->."," CO2-EINSPARUNG "," kg    ", P&CO2_Einspar,					US_LONG,	0, P&hid4,		V1, 0, 0},
  {"*->."," ANZEIGE RESERVE","       ", P&anz_dummy,						US_CHAR,	0, P&hid4,		V1, 0, 0},

	#include "parli_Copy.h"
	
	#if TVP_ANL == 1
	{"*10:"," VORLAUF   PRIM."," C    ", P&TVP[ANL],						 	ANA_FORMP, 1, P&vis,		V1, 0, 0},
	{"*10:"," VORLAUF   PRIM."," C    ", P&TVP[ANL],					 ANA_FORMP, 0x81, P&kom,		E1, FUEHLER, 0},
	#endif

	#if TRP_ANL == 1
	{"*11:"," RUECKLAUF PRIM."," C    ", P&TRP[ANL],							 ANA_FORMP, 1, P&vis,		V1, 0, 0},      
	{"*11:"," RUECKLAUF PRIM."," C    ", P&TRP[ANL],						ANA_FORMP, 0x81, P&kom,		E1, FUEHLER, 0},
	#endif

	#if TAE_ANZ == 1
	{"*->;"," Ta 0..10V-Eing."," Volt  ", P&TAE[0],								 ANA_FORMP, 2, P&hid2,	V0, 0, 0},
	{"*->;"," Ta 0..10V-Temp."," C    ", P&ta_ae,									ANA_FORM, 1, P&hid2,	V0, 0, 0},
	{" ->;"," eingabe Ta 0 V "," C    ", P&TaeSkalMin,								 S_INT, 1, P&hid2,	V0, 0, 0},
	{" ->;"," eingabe Ta 10 V"," C    ", P&TaeSkalMax,								 S_INT, 1, P&hid2,	V0, 0, 0},
	#endif

	#if TA_ANL == 1
{" 12;"," AUSSENLUFTTEMP."," C    ", P&TA[0],								 ANA_FORMP, 1, P&hid2,	V0, 0, 0},		// f�r erweiterte In-/Out Anzeige in ANL: 
	{" 12:"," AUSSENLUFTTEMP."," C    ", P&ta1m,										ANA_FORM, 1, P&vis,		V1, 0, 0},      
	{" 12:"," AUSSENLUFTTEMP."," C    ", P&ta1m,							 	 ANA_FORM, 0x81, P&kom,		E1, FUEHLER, 0},
	{" 13:"," DAEMPFUNGSZEIT "," min   ", P&Ta1mzk,									 US_CHAR, 0, P&vis,		V1, 0, 0},

	{" ->;"," TA-ERSATZ JAN  "," C    ", P&TaErsatz[0],							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," TA-ERSATZ FEB  "," C    ", P&TaErsatz[1],							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," TA-ERSATZ MRZ  "," C    ", P&TaErsatz[2],							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," TA-ERSATZ APR  "," C    ", P&TaErsatz[3],							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," TA-ERSATZ MAI  "," C    ", P&TaErsatz[4],							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," TA-ERSATZ JUN  "," C    ", P&TaErsatz[5],							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," TA-ERSATZ JUL  "," C    ", P&TaErsatz[6],							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," TA-ERSATZ AUG  "," C    ", P&TaErsatz[7],							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," TA-ERSATZ SEP  "," C    ", P&TaErsatz[8],							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," TA-ERSATZ OKT  "," C    ", P&TaErsatz[9],							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," TA-ERSATZ NOV  "," C    ", P&TaErsatz[10],							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," TA-ERSATZ DEZ  "," C    ", P&TaErsatz[11],							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," TA-ERSATZ VERZ."," h     ", P&TaErsatzVerz,						 US_CHAR, 0, P&hid1,	V0, 0, 0},
	{" ->;"," ta-ersatz ctr  "," min/2 ", P&TaErsatzCtr,						  US_INT, 0, P&hid2,	V0, 0, 0},

	#if TAA_ANZ > 0
	{"*->;"," ausgabe ta     "," Volt  ", P&TAA[0],								AOUT_FORMP, 2, P&hid2,	V0, 0, 0},
	{" ->;"," ausgabe Ta 0 V "," C    ", P&TaaSkalMin,								 S_INT, 1, P&hid2,	V0, 0, 0},
	{" ->;"," ausgabe Ta 10 V"," C    ", P&TaaSkalMax,								 S_INT, 1, P&hid2,	V0, 0, 0},
	#endif

	{"*14:"," AUSSENT. MITTEL"," C    ", P&ta1mh,									ANA_FORM, 1, P&vis,		V1, 0, 0},
	{"*14:"," AUSSENT. MITTEL"," C    ", P&ta1mh,							 ANA_FORM, 0x81, P&kom,		V1, 0, 0},
	{" ->."," Mittlungs-Init."," C    ", P&ta1mh_temp,								 S_INT, 1, P&hid2,	V0, 0, 0},
	{" 15;"," MITTLUNGS-ZEIT "," h     ", P&Ta1mhzk,								 US_CHAR, 0, P&hid1,		V1, 0, 0},
	{" 16;"," Ta-WINTER [EIN]"," C    ", P&Tae,											US_INT, 1, P&hid1,		V1, 0, 0},
	{" 17;"," Ta-SOMMER [AUS]"," C    ", P&Taa,											US_INT, 1, P&hid1,		V1, 0, 0},
	{" 18;"," SOMMER-BEGINN  "," TT.MM ", P&SomBegin,		 					 ZEIT_FORM, 1, P&hid1,		V1, 0, 0},
	{" 19;"," SOMMER-ENDE    "," TT.MM ", P&SomEnd, 			 				 ZEIT_FORM, 1, P&hid1,		V1, 0, 0}, 
// ***AnFre 06.06.2012 entfernt
//	{" 20;"," KLIMASCHUTZ    "," EIN=1 ", P&Klima,					 				 US_CHAR, 0, P&hid1,		V0, 0, 0},
//	{" ->."," Absenkung Klima"," K     ", P&DTKlima,									US_INT, 1, P&hid2,		V0, 0, 0},
  #endif // TA_ANL




	
	{"*30;"," ANFORDER. UST  "," C    ", P&anaInp[U2].mwSkal,			 ANA_FORM, 1, P&hid1,	V0, 0 , 0},
	{" ->.","  0V: Sollwert 1"," C    ", P&AnaInpPara[U2].Skal0,		 		S_INT, 1, P&hid2,	V0, 0 , 0},	
	{" ->."," 10V: Sollwert 1"," C    ", P&AnaInpPara[U2].Skal10,			S_INT, 1, P&hid2,	V0, 0 , 0},	
	{" ->."," Filterzeit 1   "," s     ", P&AnaInpPara[U2].ZkFilt,		 US_INT, 0, P&hid2,	V0, 0 , 0},

	//*************************************************************************************************
	// Datenmanager  	Ger�t im DM_Modus (Data Master)
	//*************************************************************************************************
	#if DM_MODE == 1
		#if DM_SLAVES > 0					// Slave 1: HKV ***AnFre 06.06.2012
	{"*40;"," DATENMANAGER   ","       ", P&DMmod1,								 ASCII_FORM, 0, P&hid1,	V0, 0, 0},	// ***AnFre 19.04.2012
	{" ->;"," SLAVE 1 ADRESSE","       ", P&Slave[0],								  US_CHAR, 0, P&hid1,	V0, 0, 0},
	{" ->."," Slave.1  rxtout"," min   ", P&DM[0].RxTout,				 			US_CHAR, 0, P&hid2,	V0, 0, 0},
// empfangen von HKV
	{"*41;"," SSM 1  HKV     ","       ", P&DM_SSM_Ext1,						 ANA_FORM, 0, P&hid1,	V0, 0, 0},	// von HKV
	{"*42;"," ANFORDER.1 HKV "," C    ", P&DM_ANF_Ext1,						 ANA_FORM, 1, P&hid1,	V0, 0, 0},	// von HKV
	{"*43;"," ANFORDER.2 HKV "," C    ", P&DM_ANF_Ext2,						 ANA_FORM, 1, P&hid1,	V0, 0, 0},	// von HKV

	{"*45;"," EXT.WW-VORRANG ","       ", P&hkd[HK2].ww_Vorrang,  JANEIN_FORM, 0, P&hid1,	V0, 0, 0},	// nach HKV
	{"*46;"," BEDARFSLADUNG  ","       ", P&hkd[HK1].bedLadung,  	JANEIN_FORM, 0, P&hid1,	V0, 0, 0},	// nach HKV
		#endif

		#if DM_SLAVES > 1 				// Slave 2: WPU ***AnFre 06.06.2012
	{"*50;"," DATENMANAGER   ","       ", P&DMmod2,								 ASCII_FORM, 0, P&hid1,	V0, 0, 0},	// ***AnFre 19.04.2012
	{" ->;"," SLAVE 2 ADRESSE","       ", P&Slave[1],								  US_CHAR, 0, P&hid1,	V0, 0, 0},
	{" ->."," Slave.2  rxtout"," min   ", P&DM[1].RxTout,				 			US_CHAR, 0, P&hid2,	V0, 0, 0},
// empfangen von WPU
	{"*51;"," SSM 2  WPU     ","       ", P&DM_SSM_Ext2,						 ANA_FORM, 0, P&hid1,	V0, 0, 0},	// von WP
	{"*52;"," WPU-FREIGABE   ","       ", P&DM_WPU_Frei,					   ANA_FORM, 0, P&hid1,	V0, 0, 0},	// von WP
	{"*53;"," WPU VENTILSTELL"," %     ", P&DM_WPU_Ventil,  				 ANA_FORM, 1, P&hid1,	V0, 0, 0},	// von WP

// senden an WPU
	{"*55;"," SOLLWERT WPU   "," C    ", P&hkd[HK1].tvsb,					 	 US_INT, 1, P&hid1,	V0, 0, 0},	// nach WP
	{"*56;"," VENTILSTELL.HKL"," %     ", P&RVENT[HK1],						 AOUT_FORMP, 1, P&hid1,	V0, 0, 0},	// nach WP
		#endif

		#if DM_SLAVES > 2 				// Slave 3: KES ***AnFre 06.06.2012
	{"*60;"," DATENMANAGER   ","       ", P&DMmod3,								 ASCII_FORM, 0, P&hid1,	V0, 0, 0},	// ***AnFre 02.10.2012
	{" ->;"," SLAVE 3 ADRESSE","       ", P&Slave[2],								  US_CHAR, 0, P&hid1,	V0, 0, 0},
	{" ->."," Slave.3  rxtout"," min   ", P&DM[2].RxTout,				 			US_CHAR, 0, P&hid2,	V0, 0, 0},
// empfangen von KES
	{"*61;"," SSM 3  KESSEL  ","       ", P&DM_SSM_Ext3,						 ANA_FORM, 0, P&hid1,	V0, 0, 0},	// von KES
// senden an KES
	{"*65;"," SOLLWERT KESSEL"," C    ", P&ked[KE1].tvsb,					 	 US_INT, 1, P&hid1,	V0, 0, 0},	// nach KES
	{"*66:"," KESSEL FREIGABE","       ", P&PUKEEA[KE1],		 	  JANEIN_FORMOP, 0, P&hid1,	V0,	0, 0},	// nach KES
		#endif
	#endif // DM_MODE
	
	//*************************************************************************************************
	// Datenmanager  	Ger�t im DS_Modus (Data Slave)
	//*************************************************************************************************
	#if DS_MODE == 1
	#endif
	
	//*************************************************************************************************

	{"*70:"," SOMMER ?       ","       ", P&sowi,			 					 			 JANEIN_FORM, 0, P&vis,		V1, 0, 0},
	{"*71:"," EXT.WW-VORRANG?","       ", P&hkd[HK2].ww_Vorrang, JANEIN_FORM, 0, P&vis,		V1, 0, 0},
	{" ->;"," dT EXT.WW-VORRA"," K     ", P&hks[HK2].DTVorEin,				 S_INT, 1, P&hid1,	V1, 0, 0},
	{" ->;"," VORRANGZEIT MAX"," min   ", P&hks[HK2].VorZeitMax,		 	US_INT, 0, P&hid2,	V0,	0, 0},
	{" ->."," Vorrang Max Cnt"," *30 s ", P&hkd[HK2].zVorZeitMax,		 	US_INT, 0, P&hid2,	V0,	0, 0},

	{"*80:"," SCHALTER HAND ?","       ", P&HardHand,							 		 JANEIN_FORM, 0, P&vis,		V1, 0, 0},
	{"*81;"," R66 SCHALTER1-6","       ", P&sw_stat_info,						DYN_ASCII_FORM, 6, P&hid1,	V1, 0, 0},

	#if R37_MODULE > 0
	{"*82;"," R37_1 SCHALT1-3","       ", P&mod37[0].sw_stat_info,	DYN_ASCII_FORM, 3, P&hid1,	V1, 0, 0},
	#endif

	#if R37_MODULE > 1
	{"*83;"," R37_2 SCHALT1-3","       ", P&mod37[1].sw_stat_info,	DYN_ASCII_FORM, 3, P&hid1,	V1, 0, 0},
	#endif

	{"*90:"," SMGRUP STANDARD","       ", P&sstm[STANDARD],			 	US_CHAR, 0, P&vis,		A1, GRUP|STANDARD, 0},
	{"*91:"," SMGRUP FUEHLER ","       ", P&sstm[FUEHLER],			 	US_CHAR, 0, P&vis,		A1, GRUP|FUEHLER,  0},
	{"*92:"," SMGRUP MODULE  ","       ", P&sstm[MODULE],			 		US_CHAR, 0, P&vis,		A1, GRUP|MODULE,   0},
{"*->:"," SSTM ALARME    ","       ", P&sstm_alarme,		 	JANEIN_FORM, 0, P&vis,		V1, 0, 0},
	{"*->:"," SSTM AL+FUEHLER","       ", P&sstm_all,		 			JANEIN_FORM, 0, P&vis,		V1, 0, 0},

#if SSTM_PU == 1
	{"*93:"," SSTM  PUMPEN ? ","       ", P&PUSAMAL[ANL],			JANEIN_FORMIP, 0, P&vis,		A1, EINZEL, 0},
	#endif

#if SSTM_ANL == 1
	{"*93:"," SSTM  ANLAGE ? ","       ", P&SAMAL[ANL],			 	JANEIN_FORMIP, 0, P&vis,		A1, EINZEL, 0},
	#endif

// WILOAF
	#if ( WILO_MODBUS == 1 || GENI == 1 )
	{"*93:"," SSTM PUMPENBUS?","       ", P&ssmBusPu,			  		JANEIN_FORM, 0, P&vis,		A1, EINZEL, 0},
	#endif
// AnFre 17.11.2011 02.10.2012 ge�ndert !!!
	{"*94:"," SSM EXT.1 HKV ?","       ", P&ext1SammelSM,				 JANEIN_FORM, 0, P&vis,		A1, EINZEL, 0},
	{"*->:"," SSM EXT.2 WPU ?","       ", P&ext2SammelSM,				 JANEIN_FORM, 0, P&vis,		A1, EINZEL, 0},
	{"*->:"," SSM EXT.3 KES ?","       ", P&ext3SammelSM,				 JANEIN_FORM, 0, P&vis,		A1, EINZEL, 0},
	{"*->:"," EXTERNE SSM ?  ","       ", P&SAMAL[ANL], 		 JANEIN_FORMIP, 0, P&vis,		A1, EINZEL,   0},
 	{"_->."," SSM-Bezeichnung","       ", (char*)(EXTALARMTEXT_ADR),	EEP_ASCII_FORM, 15, P&hid2,	V0, 0, 0},

#if ANFORD > 0
	{"*95:"," ANFORDERUNG MAX"," C    ", P&maxAnford,				 				 S_INT, 1, P&vis, 	V1, 0, 0},
	{" ->;"," TEMP.ANFORD.MIN"," C    ", P&TmanfSkalMin,							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," SPG.ANFORD.MIN "," Volt  ", P&TmanfSkalMinSpg,					 S_INT, 2, P&hid1,	V0, 0, 0},
	{" ->;"," TEMP.ANFORD.MAX"," C    ", P&TmanfSkalMax,							 S_INT, 1, P&hid1,	V0, 0, 0},
	{" ->;"," SPG.ANFORD.MAX "," Volt  ", P&TmanfSkalMaxSpg,					 S_INT, 2, P&hid1,	V0, 0, 0},
	{"*->;"," ausgabe tmanf  "," Volt  ", P&TMANF[0],							AOUT_FORMP, 2, P&hid2,	V0, 0, 0},
	#else
	{"*95;"," anforderung max"," C    ", P&maxAnford,				 				 S_INT, 1, P&hid2,	V0, 0, 0},
	#endif
	

#if QUIT_TASTE == 0	// wenn keine QSM-Gruppe existiert, kann hiermit eine Soft-Quittierung (Funktion: quit_proc(void) ) in Alarme.c ausgef�hrt werden
	{" 96:"," QUITTIER-TASTE "," EIN=1 ", P&quit_taste,			 				US_CHAR,  0, P&hid1,	V1, 0, 0},
	#endif

{"*97."," BELEGUNG DER   ","       ", P&Ein_Ausg,						ASCII_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," EINGANG  IN1   ","       ", P&nlist[0],					EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," EINGANG  IN2   ","       ", P&nlist[1],					EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," EINGANG  IN3   ","       ", P&nlist[2],					EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," EINGANG  IN4   ","       ", P&nlist[3],					EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," EINGANG  IN5   ","       ", P&nlist[4],					EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," EINGANG  IN6   ","       ", P&nlist[5],					EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," EINGANG  IN7   ","       ", P&nlist[6],					EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," EINGANG  IN8   ","       ", P&nlist[7],					EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," EINGANG  IN9   ","       ", P&nlist[8],					EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," EINGANG  IN10  ","       ", P&nlist[9],					EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," AUSGANG  AA1   ","       ", P&nlist[10],				EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," AUSGANG  AA2   ","       ", P&nlist[11],				EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," AUSGANG  DA1   ","       ", P&nlist[12],				EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," AUSGANG  DA2   ","       ", P&nlist[13],				EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," AUSGANG  DA3   ","       ", P&nlist[14],				EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," AUSGANG  DA4   ","       ", P&nlist[15],				EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," AUSGANG  DA5   ","       ", P&nlist[16],				EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},
	{"+->."," AUSGANG  DA6   ","       ", P&nlist[17],				EA_NAME_FORM, 0, P&hid2,		V0, 0, 0},

	#if R37_MODULE > 0
	{"+->."," R37_1 EING IN1 ","       ", P&n37list[0][0],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_1 EING IN2 ","       ", P&n37list[0][1],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_1 EING IN3 ","       ", P&n37list[0][2],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_1 EING IN4 ","       ", P&n37list[0][3],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_1 EING IN5 ","       ", P&n37list[0][4],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_1 EING IN6 ","       ", P&n37list[0][5],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_1 AUSG AA1 ","       ", P&n37list[0][6],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_1 AUSG AA2 ","       ", P&n37list[0][7],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_1 AUSG AA3 ","       ", P&n37list[0][8],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_1 AUSG AA4 ","       ", P&n37list[0][9],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_1 AUSG DA1 ","       ", P&n37list[0][10],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_1 AUSG DA2 ","       ", P&n37list[0][11],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_1 AUSG DA3 ","       ", P&n37list[0][12],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	#endif

	#if R37_MODULE > 1
	{"+->."," R37_2 EING IN1 ","       ", P&n37list[1][0],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_2 EING IN2 ","       ", P&n37list[1][1],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_2 EING IN3 ","       ", P&n37list[1][2],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_2 EING IN4 ","       ", P&n37list[1][3],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_2 EING IN5 ","       ", P&n37list[1][4],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_2 EING IN6 ","       ", P&n37list[1][5],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_2 AUSG AA1 ","       ", P&n37list[1][6],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_2 AUSG AA2 ","       ", P&n37list[1][7],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_2 AUSG AA3 ","       ", P&n37list[1][8],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_2 AUSG AA4 ","       ", P&n37list[1][9],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_2 AUSG DA1 ","       ", P&n37list[1][10],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_2 AUSG DA2 ","       ", P&n37list[1][11],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R37_2 AUSG DA3 ","       ", P&n37list[1][12],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	#endif

	#if R38_MODULE > 0
	{"+->."," R38_1 EING IN1 ","       ", P&n38list[0][0],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_1 EING IN2 ","       ", P&n38list[0][1],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_1 EING IN3 ","       ", P&n38list[0][2],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_1 EING IN4 ","       ", P&n38list[0][3],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_1 EING IN5 ","       ", P&n38list[0][4],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_1 EING IN6 ","       ", P&n38list[0][5],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_1 EING IN7 ","       ", P&n38list[0][6],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_1 EING IN8 ","       ", P&n38list[0][7],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_1 EING IN9 ","       ", P&n38list[0][8],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_1 EING IN10","       ", P&n38list[0][9],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_1 EING IN11","       ", P&n38list[0][10],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_1 EING IN12","       ", P&n38list[0][11],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_1 EING IN13","       ", P&n38list[0][12],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_1 EING IN14","       ", P&n38list[0][13],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	#endif

	#if R38_MODULE > 1
	{"+->."," R38_2 EING IN1 ","       ", P&n38list[1][0],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_2 EING IN2 ","       ", P&n38list[1][1],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_2 EING IN3 ","       ", P&n38list[1][2],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_2 EING IN4 ","       ", P&n38list[1][3],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_2 EING IN5 ","       ", P&n38list[1][4],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_2 EING IN6 ","       ", P&n38list[1][5],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_2 EING IN7 ","       ", P&n38list[1][6],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_2 EING IN8 ","       ", P&n38list[1][7],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_2 EING IN9 ","       ", P&n38list[1][8],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_2 EING IN10","       ", P&n38list[1][9],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_2 EING IN11","       ", P&n38list[1][10],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_2 EING IN12","       ", P&n38list[1][11],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_2 EING IN13","       ", P&n38list[1][12],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	{"+->."," R38_2 EING IN14","       ", P&n38list[1][13],				EA_NAME_FORM, 0, P&hid2, V0, 0, 0},
	#endif

{"*->;"," SSTM RELAIS    ","       ", P&SSTM[ANL],				 JANEIN_FORMOP, 0, P&hid4,	V0, 0, 0},	// f�r erweiterte In-/Out Anzeige in ANL: 
	{" 98;"," R3X-Simulator  "," EIN=1 ", P&ea_simul,				 				 US_CHAR, 0, P&hid2,	V0, 0, 0},
	{" 99;"," serv_count     ","       ", P&serv_cnt,									US_INT, 0, P&hid2,	V0, 0, 0},


	
	
	{".99:"," SERVICE-CODE   ","       ", P&service_code,						 US_CHAR, 0, P&vis,		V0, 0, 0},
};  

/*------------------------------ Kesselsteuerung -------------------------------------------*/
#if KEANZ > 0
const Pgrup ke1[] = {
	{"***:"," KESSELSTEUERUNG","       ", P&Kesmod,							ASCII_FORM, 0, P&vis,		V0, 0, 0},
	{"*01:"," VL-KESSEL  TVK1"," C    ", P&TVKE[KE1],					 ANA_FORMP, 1, P&vis,		V1, 0, 0},
	{"*01:"," VL-KESSEL  TVK1"," C    ", P&TVKE[KE1],				ANA_FORMP, 0x81, P&kom,		E1, FUEHLER, 0},
//	{"*02:"," RL-KESSEL TRKES"," C    ", P&TRKE[KE1],					 ANA_FORMP, 1, P&vis,		V1, 0, 0},
//	{"*02:"," RL-KESSEL TRKES"," C    ", P&TRKE[KE1],				ANA_FORMP, 0x81, P&kom,		E1, FUEHLER, 0},
	
	{" 10;"," VORLAUF   MAX  "," C    ", P&kes[KE1].Tvma,					US_INT, 1, P&hid1,		V1, 0, 0},
	{" 11;"," VORLAUF   MIN  "," C    ", P&kes[KE1].Tvmi,					US_INT, 1, P&hid1,		V1, 0, 0},
	{" 12;"," ANHEBUNG  [HKL]"," K     ", P&kes[KE1].Tvpa,					S_INT, 	1, P&hid1,		V1, 0, 0},
// ***AnFre 06.06.2012	{" 13;"," ANHEBUNG  [TWE]"," K     ", P&kes[KE1].TvPaWw,				S_INT, 	1, P&hid1,		V1, 0, 0},

	{"*14:"," ANFORDER.EXT 1 "," C    ", P&ked[KE1].ExtAnf1Ke,				ANA_FORM, 1, P&vis,	V1, 0, 0},
	{"*14:"," ANFORDER.EXT 1 "," C    ", P&ked[KE1].ExtAnf1Ke,	 		 	ANA_FORM, 0x81, P&kom,	E1, FUEHLER, 0},
	{" ->."," ANFORD.GUELTIG "," 1=JA  ", P&kes[KE1].ExtAnf1_Ja,		 US_CHAR, 0, P&hid2,	V0, 0, 0},
	{"*15:"," ANFORDER.EXT 2 "," C    ", P&ked[KE1].ExtAnf2Ke,				ANA_FORM, 1, P&vis,	V1, 0, 0},
	{"*15:"," ANFORDER.EXT 2 "," C    ", P&ked[KE1].ExtAnf2Ke,	 		 	ANA_FORM, 0x81, P&kom,	E1, FUEHLER, 0},
	{" ->."," ANFORD.GUELTIG "," 1=JA  ", P&kes[KE1].ExtAnf2_Ja,		 US_CHAR, 0, P&hid2,	V0, 0, 0},
	{" 16;"," ANHEB. EXT.ANF."," K     ", P&kes[KE1].TvAnhExt,				US_INT, 1, P&hid1,	V0, 0, 0},	//V0 Munzert 21.01.2015

//	{" 17:"," RUECKLAUF MAX  "," C    ", P&kes[KE1].Trma,					US_INT, 1, P&vis,		V1, 0, 0},
//	{" 18:"," Xp-RUECKL.BEGR.","       ", P&kes[KE1].Kpr,						US_INT, 2, P&vis,		V1, 0, 0},
	{" 19;"," dT KALTSTART   "," K     ", P&kes[KE1].Ttaup,					S_INT, 1, P&hid1,		V0, 0, 0},

	{"*20:"," VORLAUF-SOLLWER"," C    ", P&ked[KE1].tvsb_kes,				US_INT, 1, P&vis,		V1, 0, 0},

	{" 50;"," KESSEL VERZOEG."," min   ", P&kes[KE1].Kepuverz,			US_CHAR, 0, P&hid1,		V0,	0, 0},
	{" 51;"," KESSEL NACHLAUF"," min   ", P&kes[KE1].Kepuna,				US_CHAR, 0, P&hid1,		V0,	0, 0},
// 24.10.2012 Kessel-Freigabe entsprechend der Ventilstellung der W�rmepumpe: DM_WPU_Ventil
	{" 55;"," WP-VENT. K-EIN "," %     ", P&kes[KE1].WpVentEin,	 		 	US_INT, 1, P&hid1,	V0, 0, 0},
	{" 56;"," WP-VENT. K-AUS "," %     ", P&kes[KE1].WpVentAus,	 		 	US_INT, 1, P&hid1,	V0, 0, 0},

	{"*70:"," KESSEL EIN ?   ","       ", P&PUKEEA[KE1],		 	 JANEIN_FORMOP, 0, P&vis,		V1,	0, 0},
	{" ->."," Kessel Verz.Cnt"," *30 s ", P&ked[KE1].puein_cnt,		 		US_INT, 0, P&hid2,	V0,	0, 0},
	{" ->."," Kess. Nachl.Cnt"," *30 s ", P&ked[KE1].puna_cnt,		 		US_INT, 0, P&hid2,	V0,	0, 0},
	{" ->."," Kessel-Starts  ","       ", P&ked[KE1].kestarts, 				US_INT, 0, P&hid2,	V1, 0, 0},
	{" ->."," Kessel-Laufzeit"," h     ", P&ked[KE1].kesh,						US_INT, 0, P&hid2,	V1, 0, 0},

	{"*72:"," HEIZ-BEDARF ?  ","       ", P&hkdSoL[HK1].heizBed, JANEIN_FORM, 0, P&vis,		V1, 0, 0},
	{" ->."," RV-HKL ZU      "," min   ", P&hksSoL[HK1].RVzu,			 	 US_CHAR, 0, P&hid2,	V0, 0, 0},
	{" ->."," RV-HKL Zu   Cnt"," s     ", P&hkdSoL[HK1].zRVzu,			 	US_INT, 0, P&hid2,	V0, 0, 0},
	{" ->."," RV-HKL AUF     "," min   ", P&hksSoL[HK1].RVauf,			 US_CHAR, 0, P&hid2,	V0, 0, 0},
	{" ->."," RV-HKL Auf  Cnt"," s     ", P&hkdSoL[HK1].zRVauf,			 	US_INT, 0, P&hid2,	V0, 0, 0},

	{"*80:"," SSM KESSEL ?   ","       ", P&ked[KE1].keAl_sAl,	JANEIN_FORM, 0, P&vis,	A1, EINZEL, 0},	// Verz�gerter Alarm
	{" ->."," SSM Verzoegern "," min   ", P&kes[KE1].KeAl_verz,			US_CHAR, 0, P&hid2,	V0,	0, 0},
	{" ->."," SSM Verzoeg.Cnt"," *30 s ", P&ked[KE1].keAl_cnt, 			 US_INT, 0, P&hid2,	V0,	0, 0},
	#if PUBM_KE1 == 1
	{"*88:"," SM KES-PUMPE ? ","       ", P&ked[KE1].pukeBm,	 	JANEIN_FORM, 0, P&vis,	E1, STANDARD,	0},
	#endif

	#if PU_BUS_KE1 > 0
	{"*88:"," SM BUS PUMPE ? ","       ", P&ked[KE1].busPuSm,	 JANEIN_FORM, 0, P&vis,		A1, EINZEL, 0},
	#endif
	
	{"*89:"," HANDBETRIEB ?  ","       ", P&kes[KE1].Haut,		 JANEIN_FORM, 0, P&vis,		E1, EREIGNIS, 0},

	{" 90;"," IST > SOLL  MAX"," K     ", P&kes[KE1].SchaltDiff,		US_INT, 1, P&hid1,	V0, 0, 0},
	{" 95;"," VL-TEMP.  0Volt"," C    ", P&kes[KE1].Tvsol0,				 S_INT, 1, P&hid1,	V0, 0, 0},
	{" 96;"," VL-TEMP. 10Volt"," C    ", P&kes[KE1].Tvsol10,				 S_INT, 1, P&hid1,	V0, 0, 0},
	{"*97;"," SOLLWERT       "," C    ", P&ked[KE1].tvsb,					US_INT, 1, P&hid1,	V1, 0, 0},
	{" ->."," Sollw.Steigerng"," K/30s ", P&kes[KE1].TvsbSteig,			US_INT, 1, P&hid2,	V0, 0, 0},
	{" ->."," Sollw.Minderung"," K/30s ", P&kes[KE1].TvsbMinde,			US_INT, 1, P&hid2,	V0, 0, 0},

	{"*98;"," ANFORDERUNG    "," Volt  ", P&ked[KE1].y_rel,					US_INT, 2, P&hid1,	V0, 0, 0},

	{" 99;"," HAND/AUTOMATIK "," HAND=1", P&kes[KE1].Haut,				 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" ->;"," KESSEL  EIN/AUS"," EIN=1 ", P&kes[KE1].Kespuea,			 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" ->;"," KESSEL  STELLEN"," Volt  ", P&kes[KE1].Kestell,			  US_INT, 2, P&hid1,	V1, 0, 0},

};
#endif

/*------------------------------ Heizkreis 2 Nahw�rmenetz -------------------------------------------*/
#if HKANZ > 1
	#include "parli_Hk2_Netz.h"
#endif

/*------------------------------ Heizkreis 1 -------------------------------------------*/
#if HKANZ > 0
	#include "parli_Hk1_HKL.h"
#endif

/*------------------------ Heizkreis 1 Solare Einspeisung ***AnFre ---------------*/
#if HKSoLANZ > 0
	#include "parli_HkSol.h"
#endif
/*------------------------------ Heizkreis 3 -------------------------------------------*/
/*------------------------------ Heizkreis 4 -------------------------------------------*/

/*------------------------------ Warmwasser -------------------------------------------*/

/*------------------------------ Solar-Steuerung SOL: und Solar-Sensor SOS: ----------------------------------------*/
#if SOANZ > 0
	#include "parli_Solar.h"
#endif
/*------------------------------ Quellenregeneration ----------------------------------------*/
	#include "parli_quellenregeneration.h"


// ***AnFre	Ende
//*------------------------------ Genibus ----------------------------------------*/
#if GENI == 1
	#include "parli_genibus.h"
#endif



/*------------------------------ Ferienprogramm ----------------------------------------*/
//#if FER == 1
//const Pgrup fer[] = {
//	{"***:"," FERIENPROGRAMM ","       ", P&Leer15,							ASCII_FORM, 0, P&vis,		V1, 0, 0},
//	{" 10:"," FERIENBEGINN 1 ","       ", P&ferien[0].ferienBeg, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 11:"," FERIENENDE 1   ","       ", P&ferien[0].ferienEnd, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 12:"," FERIENBEGINN 2 ","       ", P&ferien[1].ferienBeg, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 13:"," FERIENENDE 2   ","       ", P&ferien[1].ferienEnd, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 14:"," FERIENBEGINN 3 ","       ", P&ferien[2].ferienBeg, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 15:"," FERIENENDE 3   ","       ", P&ferien[2].ferienEnd, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 16:"," FERIENBEGINN 4 ","       ", P&ferien[3].ferienBeg, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 17:"," FERIENENDE 4   ","       ", P&ferien[3].ferienEnd, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 18:"," FERIENBEGINN 5 ","       ", P&ferien[4].ferienBeg, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 19:"," FERIENENDE 5   ","       ", P&ferien[4].ferienEnd, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 20:"," FERIENBEGINN 6 ","       ", P&ferien[5].ferienBeg, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 21:"," FERIENENDE 6   ","       ", P&ferien[5].ferienEnd, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 22:"," FERIENBEGINN 7 ","       ", P&ferien[6].ferienBeg, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 23:"," FERIENENDE 7   ","       ", P&ferien[6].ferienEnd, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 24:"," FERIENBEGINN 8 ","       ", P&ferien[7].ferienBeg, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 25:"," FERIENENDE 8   ","       ", P&ferien[7].ferienEnd, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 26:"," FERIENBEGINN 9 ","       ", P&ferien[8].ferienBeg, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 27:"," FERIENENDE 9   ","       ", P&ferien[8].ferienEnd, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 28:"," FERIENBEGINN 10","       ", P&ferien[9].ferienBeg, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{" 29:"," FERIENENDE 10  ","       ", P&ferien[9].ferienEnd, DATE_FORM, 1, P&vis,		V1, 0, 0},
//	{"*80:"," FERIEN ?       ","       ", P&ferienStat,		 		 JANEIN_FORM, 0, P&vis,		V1, 0, 0},
//};
//#endif

/*----------------------- Quittierbare Gespeicherte St�rmeldungen ---------------------------*/

#if QUIT_TASTE == 1
	#include "qsm.h"
#endif

/*------------------------------ Interne Z�hler ----------------------------------------*/
#if ZE3==1
	#include "zin03.h"
#endif
#if ZE4==1
	#include "zin04.h"
#endif
#if ZE5==1
	#include "zin05.h"
#endif
#if ZE6==1
	#include "zin06.h"
#endif
//#if ZE7==1	Kaltwasser-Z�hler nicht vorhanden
//	#include "zin07.h"
//#endif
#if ZE8==1
	#include "zin08.h"
#endif
#if ZE9==1
	#include "zin09.h"
#endif
#if ZE10==1
	#include "zin10.h"
#endif
/*------------------------------ Externe Z�hler R37_1 ----------------------------------*/
#if ZE11==1
	#include "x1zin1.h"
#endif
#if ZE12==1
	#include "x1zin2.h"
#endif
#if ZE13==1
	#include "x1zin3.h"
#endif
#if ZE14==1
	#include "x1zin4.h"
#endif
#if ZE15==1
	#include "x1zin5.h"
#endif
#if ZE16==1
	#include "x1zin6.h"
#endif
/*------------------------------ Externe Z�hler R37_2 ----------------------------------*/
#if ZE21==1
	#include "x2zin1.h"
#endif
#if ZE22==1
	#include "x2zin2.h"
#endif
#if ZE23==1
	#include "x2zin3.h"
#endif
#if ZE24==1
	#include "x2zin4.h"
#endif
#if ZE25==1
	#include "x2zin5.h"
#endif
#if ZE26==1
	#include "x2zin6.h"
#endif

/*------------------------------ MBUS-Z�hler -------------------------------------------*/
#if MBUSANZ > 0
	#include "parli_mbus.h"
#endif
/*------------------------------ Synchronisierung Z�hler -------------------------------*/
//const Pgrup syc[] = {
// {"***:"," ZAEHLER        ","       ", P&Zsync,					ASCII_FORM, 0, P&hid3,	V0, 0, 0},
// {" 01:"," ZAEHL-SYNC IN3 ","       ", P&ZE[0],						ZE_FORMP, 6, P&hid3,	V0, 0, 0},
// {" 02:"," ZAEHL-SYNC IN4 ","       ", P&ZE[1],						ZE_FORMP, 6, P&hid3,	V0, 0, 0},
// {" 03:"," ZAEHL-SYNC IN5 ","       ", P&ZE[2],						ZE_FORMP, 6, P&hid3,	V0, 0, 0},
// {" 04:"," ZAEHL-SYNC IN6 ","       ", P&ZE[3],						ZE_FORMP, 6, P&hid3,	V0, 0, 0},
// {" 05:"," ZAEHL-SYNC IN7 ","       ", P&ZE[4],						ZE_FORMP, 6, P&hid3,	V0, 0, 0},
// {" 06:"," ZAEHL-SYNC IN8 ","       ", P&ZE[5],						ZE_FORMP, 6, P&hid3,	V0, 0, 0},
// {" 07:"," ZAEHL-SYNC IN9 ","       ", P&ZE[6],						ZE_FORMP, 6, P&hid3,	V0, 0, 0},
// {" 08:"," ZAEHL-SYNC IN10","       ", P&ZE[7],						ZE_FORMP, 6, P&hid3,	V0, 0, 0},
// {" 11:"," VERBR-SYNC IN3 ","       ", P&ZE[0],						ZE_FORMP, 7, P&hid3,	V0, 0, 0},
// {" 12:"," VERBR-SYNC IN4 ","       ", P&ZE[1],						ZE_FORMP, 7, P&hid3,	V0, 0, 0},
// {" 13:"," VERBR-SYNC IN5 ","       ", P&ZE[2],						ZE_FORMP, 7, P&hid3,	V0, 0, 0},
// {" 14:"," VERBR-SYNC IN6 ","       ", P&ZE[3],						ZE_FORMP, 7, P&hid3,	V0, 0, 0},
// {" 15:"," VERBR-SYNC IN7 ","       ", P&ZE[4],						ZE_FORMP, 7, P&hid3,	V0, 0, 0},
// {" 16:"," VERBR-SYNC IN8 ","       ", P&ZE[5],						ZE_FORMP, 7, P&hid3,	V0, 0, 0},
// {" 17:"," VERBR-SYNC IN9 ","       ", P&ZE[6],						ZE_FORMP, 7, P&hid3,	V0, 0, 0},
// {" 18:"," VERBR-SYNC IN10","       ", P&ZE[7],						ZE_FORMP, 7, P&hid3,	V0, 0, 0},
//
//}; 

/*------------------------------ Diagnose --------------------------------------------------*/
#if DIAG == 1
	#include "parli_Dia_WZ1_WZ3_TN2_TH2.h"
#endif

/*----------------------- Quittierbare Gespeicherte St�rmeldungen ---------------------------*/


/*------------------------------ Alarmkontrolle ----------------------------------------*/
const Pgrup alk[] = {
 {"***;"," ALARMKONTROLLE ","       ", P&Leer15,										ASCII_FORM, 0, P&hid3,	V0, 0, 0},
 {" 00:"," PARAM. SICHERN "," 1=JA  ", P&altest_speich,								 US_CHAR, 0, P&hid3,	V0, 0, 0},
 {" 01:"," ALARM-NUMMER   "," # 0-  ", P&alarm_test,						ALARMTEST_FORM, 0, P&hid3,	V0, 0, 0},
 {" 01:"," AlarmKontrolle ","       ", P&alarm_test,						ALARMTEST_FORM, 1, P&hid3,	V0, 0, 0},
 {" 02:"," AKTIVIERUNG    "," s     ", P&alarmtab[0].Waitlimit,	ALARMTEST_FORM, 2, P&hid3,	V0, 0, 0},
 {" 03:"," MASKE          ","       ", P&alarmtab[0].Maske,			ALARMTEST_FORM, 3, P&hid3,	V0, 0, 0},
 {" 04:"," LED-FUNKTION   ","       ", P&alarmtab[0].Ledfunc,		ALARMTEST_FORM, 4, P&hid3,	V0, 0, 0},
 {" 05:"," LCD-ANZEIGE    "," s     ", P&alarmtab[0].Visloader,	ALARMTEST_FORM, 5, P&hid3,	V0, 0, 0},

};

/*------------------------------ Heizgradtage ---------------------------------------------*/
#if HEIZGRD == 1
const Pgrup hgt[] = {
 {"***:"," HEIZGRADTAGE   ","       ", P&HzGrdTg,							 			ASCII_FORM, 0, P&vis,	V0, 0, 0},
 {" 01:"," MONATSAUSWAHL  "," # 1-12", P&monHzGrdAnz,					 				 EXP_HGT, 0, P&vis,	V0, 0, 0},	
 {"*10:"," HEIZGRADTAGE   ","       ", P&sMonHzGrdAnz.hzGrdTage,	 EXP_HGT_INT, 1, P&vis,	V0, 0, 0},
 {"*11:"," HEIZTAGE       ","       ", P&sMonHzGrdAnz.hzTage,	 		EXP_HGT_CHAR, 0, P&vis,	V0, 0, 0},  
 {"*12:"," BEWERTETE TAGE ","       ", P&sMonHzGrdAnz.hzTageBew,	EXP_HGT_CHAR, 0, P&vis,	V0, 0, 0},
 {"*20:"," HEIZGRADTAGE VJ","       ", P&sMonHzGrdAnz.hzGrdTageVj, EXP_HGT_INT, 1, P&vis,	V0, 0, 0},
 {"*21:"," HEIZTAGE VJ    ","       ", P&sMonHzGrdAnz.hzTageVj,	 	EXP_HGT_CHAR, 0, P&vis,	V0, 0, 0},  
 {"*22:"," BEWERT.TAGE VJ ","       ", P&sMonHzGrdAnz.hzTageBewVj,EXP_HGT_CHAR, 0, P&vis,	V0, 0, 0},   
};
#endif

/*------------------------------ Leistungs-Begrenzung ---------------------------------------------*/
#if LEIST_BEGR == 1
const Pgrup lbg[] = {
 {"***:"," BEGRENZUNG     ","       ", P&Leistung,							 		ASCII_FORM, 0, P&vis,	 V0, 0, 0},

 {" 01:"," GRENZ-LEISTUNG "," kW    ", P&GrenzLeistung.GrenzLeistg,			US_INT,	0, P&vis,  V1, 0, 0}, 
 {" 02:"," HYSTERESE      "," kW    ", P&GrenzLeistung.LeistgHyst,			US_INT,	0, P&vis,  V1, 0, 0}, 

 {" 10:"," MITTL/AKT/MBUS "," 1/2/3 ", P&GrenzLeistung.BegrAkt,				 US_CHAR,	0, P&vis,  V1, 0, 0},  
 {" 11;"," DAEMPFUNG      ","       ", P&GrenzLeistung.Daempfung,				US_INT,	0, P&hid1, V1, 0, 0}, 
 {"*12:"," LEISTUNG BEGR. "," kW    ", P&grenzLeistung.leistBegr,				US_INT,	0, P&vis,  V1, 0, 0}, 
 {"*13:"," BEGRENZUNG EIN?","       ", P&grenzLeistung.begrenzung, JANEIN_FORM, 0, P&vis,	 V1, 0, 0},
 {"*->;"," begrenzgs-stufe","       ", P&grenzLeistung.begrenzung,	 	 US_CHAR, 0, P&hid2, V0, 0, 0},
 {"*14:"," ANZAHL BEGRENZ.","       ", P&AnzahlBegrenzung,	 			 	 	  US_INT, 0, P&vis,	 V1, 0, 0},  		
 {"*15:"," DAUER BEGRENZ. "," min   ", P&DauerBegrenzung,	 			 	 	 		US_INT, 0, P&vis,	 V1, 0, 0},

};
#endif


/*------------------------------ Benutzersteuerung mit UNI-Elementen -------------------*/
#if STEUER_UNI == 1
	#include "parli_uni.h"
#endif	

/*------------------------------ Test-RS485 --------------------------------------------*/
#if ( (IMPLEMENT_S1 & GBUS1_IMPL) == GBUS1_IMPL )
const Pgrup us1[] = {
 {"***;"," TEST-RS485 S1  ","       ", P&Leer15,									ASCII_FORM, 0, P&hid1,	V0, 0, 0},
 {" 06;"," MASTER         "," JA=1  ", P&serial[S1].Mode,						 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 07;"," BAUDRATE       "," Baud  ", P&serial[S1].Baudrate,			 BAUD_FORM, 0, P&hid1,	V0, 0, 0},
 {" ->;"," BAUD QUALI     "," %     ", P&serial[S1].BaudQuali,				 S_INT, 0, P&hid2,	V0, 0, 0},
 {" 72;"," RX_TEST        ","       ", P&serial[S1].rxtest,					 US_CHAR, 0, P&hid2,	V1, 0, 0},
 {" 76;"," STATUS         ","       ", P&serial[S1].status,					 US_CHAR, 0, P&hid2,	V0, 0, 0},
};
#endif
#if ( (IMPLEMENT_S2 & GBUS1_IMPL) == GBUS1_IMPL )
const Pgrup us2[] = {
 {"***;"," TEST-RS485 S2  ","       ", P&Leer15,									ASCII_FORM, 0, P&hid1,	V0, 0, 0},
 {" 06;"," MASTER         "," JA=1  ", P&serial[S2].Mode,						 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 07;"," BAUDRATE       "," Baud  ", P&serial[S2].Baudrate,			 BAUD_FORM, 0, P&hid1,	V0, 0, 0},
 {" ->;"," BAUD QUALI     "," %     ", P&serial[S2].BaudQuali,				 S_INT, 0, P&hid2,	V0, 0, 0},
 {" 72;"," RX_TEST        ","       ", P&serial[S2].rxtest,					 US_CHAR, 0, P&hid2,	V1, 0, 0},
 {" 76;"," STATUS         ","       ", P&serial[S2].status,					 US_CHAR, 0, P&hid2,	V0, 0, 0},
};
#endif
#if ( (IMPLEMENT_S3 & GBUS1_IMPL) == GBUS1_IMPL )
const Pgrup us3[] = {
 {"***;"," TEST-RS485 S3  ","       ", P&Leer15,									ASCII_FORM, 0, P&hid1,	V0, 0, 0},
 {" 06;"," MASTER         "," JA=1  ", P&serial[S3].Mode,						 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 07;"," BAUDRATE       "," Baud  ", P&serial[S3].Baudrate,			 BAUD_FORM, 0, P&hid1,	V0, 0, 0},
 {" ->;"," BAUD QUALI     "," %     ", P&serial[S3].BaudQuali,				 S_INT, 0, P&hid2,	V0, 0, 0},
 {" 72;"," RX_TEST        ","       ", P&serial[S3].rxtest,					 US_CHAR, 0, P&hid2,	V1, 0, 0},
 {" 76;"," STATUS         ","       ", P&serial[S3].status,					 US_CHAR, 0, P&hid2,	V0, 0, 0},
};
#endif

/*------------------------------ Funkempfang ------------------------------------------------------------------------------------------------*/
#if ( ((IMPLEMENT_S1 & FUNK1_IMPL) == FUNK1_IMPL ) || ((IMPLEMENT_S2 & FUNK1_IMPL) == FUNK1_IMPL ) || ((IMPLEMENT_S3 & FUNK1_IMPL) == FUNK1_IMPL) )
const Pgrup rf[] = {
	{"***;", " FUNKSENSOREN   ", "       ", P&Leer15,											 ASCII_FORM, 0, P&hid1,	V0, 0, 0},
	{" 01;", " RF-SENSORKANAL?", " # 1-12", P&bedien_rf_nummer,						EXPAND_CHAR, 0, P&hid1, V0, 0, EXP_RFS},
	{" 11;", " RF-STATUS      ", " 7..0  ", P&rf_feld[0].ucRf_status,				DIGR_FORM, 8, P&hid1, V0, 0, EXP_RFS},
	{" 12;", " RF-PRAESENS    ", "       ", P&rf_feld[0].ucRf_praesens,				US_CHAR, 0, P&hid1, V0, 0, EXP_RFS},
	{" 13;", " RF-TEMPERATUR  ", " C    ", P&rf_feld[0].siRf_temp,						 US_INT, 1, P&hid1, V0, 0, EXP_RFS},
	{" 14;", " RF-TEMP-VERSCH.", " K     ", P&rf_feld[0].scRf_temp_shift,			 S_CHAR, 1, P&hid1, V0, 0, EXP_RFS},
	{" 15;", " RF-LIVE-CHECK  ", " min   ", P&rf_feld[0].ucLive_check_timer,	US_CHAR, 0, P&hid1, V0, 0, EXP_RFS},
	{" 16;", " RF-TEACH-ENABLE", "       ", P&rf_feld[0].ucRf_teach_enable,		US_CHAR, 0, P&hid1, V0, 0, EXP_RFS},
	{"[17;", " RF-SENSOR-ID   ", "       ", P&rf_feld[0].ulRf_modul_id,		HEXBUF_FORM, 4, P&hid1, V0, 0, EXP_RFS},
	{" 18;", " RF-SETUP       ", " 7..0  ", P&rf_feld[0].ucSetup,						DIGR_FORM, 8, P&hid1, V0, 0, EXP_RFS},
	{"[90;", " ucfRxBuf_RF    ", "       ", P&ucfRxBuf_RF[0],							HEXBUF_FORM, 8, P&hid2, V0, 0, 0},
	{" 91;", " ucTeach_idx    ", "       ", P&ucTeach_idx,										US_CHAR, 0, P&hid2, V0, 0, 0},
	{" 92;", " ucRxFlag_RF    ", "       ", P&ucRxFlag_RF,										US_CHAR, 0, P&hid2, V0, 0, 0},
	{" 93;", " ucCond_RF      ", "       ", P&ucCond_RF,											US_CHAR, 0, P&hid2, V0, 0, 0},
	{" 94;", " Typ = SRC-EVC ?", " JA=1  ", P&ucReceiverTyp_RF,								US_CHAR, 0, P&hid2, V0, 0, 0},

};		
#endif

/*------------------------------ Anybus ------------------------------------------------------------------------------------------------*/
#if ANYBUS_MODUL == 1
#include "anybus/anybusparli.h"
#endif

//*------------------------------ Modbus Allgemein ----------------------------------------*/
#if MODBUS_UNI > 0
  #include "Modbus/modbusparli.h"
#endif

//*------------------------------ Modbus WILO-Pumpen----------------------------------------*/

#if WILO_MODBUS > 0
	#include "parli_Wilo.h"
#endif


/*------------------------------------ ZLT ---------------------------------------------------*/
const Pgrup zlt[] = {
 {"***;"," LEITTECHNIK    ","       ", P&Leitstr,										ASCII_FORM, 0, P&hid1,	V0, 0, 0},
 {" 01;"," MODULADRESSE   ","       ", P&ModulAdr,										 US_CHAR, 0, P&hid1,	V0, 0, 0},

 {" 02;"," MASTER-S1      "," JA=1  ", P&Mode_S1,											 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 03;"," BAUDRATE-S1    "," Baud  ", P&Baudrate_S1,								 BAUD_FORM, 0, P&hid1,	V0, 0, 0},
 {" ->;"," BAUD-S1 QUALI  "," %     ", P&BaudQuali_S1,								   S_INT, 0, P&hid2,	V0, 0, 0},
 {" ->;"," FUNKTION-S1    ","       ", P&Funktion_S1,						  FU_NAME_FORM, 0, P&hid1,	V0, 0, 0},
 {" ->;"," PARITY-S1      ","       ", P&Parity_S1,									   US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" ->;"," STOPBITS-S1    ","       ", P&Stopbits_S1,								   US_CHAR, 0, P&hid1,	V0, 0, 0},

 {" 04;"," MASTER-S2-opto "," JA=1  ", P&Mode_S2,											 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 05;"," BAUDRATE-S2    "," Baud  ", P&Baudrate_S2,								 BAUD_FORM, 0, P&hid1,	V0, 0, 0},
 {" ->;"," BAUD-S2 QUALI  "," %     ", P&BaudQuali_S2,								   S_INT, 0, P&hid2,	V0, 0, 0},
 {" ->;"," FUNKTION-S2    ","       ", P&Funktion_S2,							FU_NAME_FORM, 0, P&hid1,	V0, 0, 0},
 {" ->;"," PARITY-S2      ","       ", P&Parity_S2,									   US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" ->;"," STOPBITS-S2    ","       ", P&Stopbits_S2,								   US_CHAR, 0, P&hid1,	V0, 0, 0},

 #if ( ( (IMPLEMENT_S3 & GBUS_IMPL) == GBUS_IMPL ) || ( (IMPLEMENT_S3 & MBUS1_IMPL) == MBUS1_IMPL ) || ( (IMPLEMENT_S3 & GENI1_IMPL) == GENI1_IMPL ) || ( (IMPLEMENT_S3 & MODBUS1_IMPL) == MODBUS1_IMPL ) )
 {" 06;"," MASTER-S3      "," JA=1  ", P&Mode_S3,											 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 07;"," BAUDRATE-S3    "," Baud  ", P&Baudrate_S3,								 BAUD_FORM, 0, P&hid1,	V0, 0, 0},
 {" ->;"," BAUD-S3 QUALI  "," %     ", P&BaudQuali_S3,								   S_INT, 0, P&hid2,	V0, 0, 0},
 {" ->;"," FUNKTION-S3    ","       ", P&Funktion_S3,							FU_NAME_FORM, 0, P&hid1,	V0, 0, 0},
 {" ->;"," PARITY-S3      ","       ", P&Parity_S3,									   US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" ->;"," STOPBITS-S3    ","       ", P&Stopbits_S3,								   US_CHAR, 0, P&hid1,	V0, 0, 0},
 {"*->;"," MODULTYP-S3    ","       ", P&spl_kennung,									SPL_FORM, 0, P&hid1,	V0, 0, 0},
 {" ->;"," KENNUNG-S3 SIMU","       ", P&Spl_kennung_simu,						SPL_FORM, 1, P&hid2,	V0, 0, 0},
 #endif
 
 {" 08;"," IrDA-S4        "," JA=1  ", P&IrDA_S4,											 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 09;"," MASTER-S4      "," JA=1  ", P&Mode_S4,											 US_CHAR, 0, P&hid1,	V0, 0, 0},

 {" 10;"," FERNBED  1=GBUS"," 0=XBUS", P&fb_bus,											 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 11;"," FERNBED-ADRESSE","       ", P&fb_adresse,									 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 12;"," FERNBEDIENUNG  "," JA=1  ", P&fernbedien,									 US_CHAR, 0, P&hid1,	V0, 0, 0},

 {"_13;"," OBJ-BEZEICHNUNG","       ", (char*)(OBJBEZ_ADR),		 EEP_ASCII_FORM, 15, P&hid1,	V0, 0, 0},
 {"_14;"," OBJ-NUMMER     ","       ", (char*)(OBJNUM_ADR),		 EEP_ASCII_FORM,  9, P&hid1,	V0, 0, 0},
 {"_15;"," STRASSE        ","       ", (char*)(STRASSE_ADR),	 EEP_ASCII_FORM, 15, P&hid1,	V0, 0, 0},
 {"_16;"," HAUSNUMMER     ","       ", (char*)(NUMMER_ADR),		 EEP_ASCII_FORM,  9, P&hid1,	V0, 0, 0},
 {"_17;"," ORT            ","       ", (char*)(ORT_ADR),		 	 EEP_ASCII_FORM, 15, P&hid1,	V0, 0, 0},
 {"_18;"," PLZ            ","       ", (char*)(PLZAHL_ADR),		 EEP_ASCII_FORM,  9, P&hid1,	V0, 0, 0},
 {"*19;"," OBJ-ORT FEHLT ?","       ", P&ort_idf,									 JANEIN_FORM, 0, P&hid1,	E1, ANZEIGE, 0},

 {"*20;"," STATION-ADRESSE","       ", P&StationsAdr,								 	 US_CHAR, 0, P&hid1,	V1, 0, 0},
 {" ->;"," STATION-INITADR","       ", P&StatInitAdr,									 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {"021;"," MASTER -IDF    ","       ", P&Master_Idf,								 TELE_FORM, 0, P&hid1,	V1, 0, 0},
 {"022;"," STATION-IDF    ","       ", P&Station_Idf,								 TELE_FORM, 0, P&hid1,	V1, 0, 0},
 {"023;"," ALARM-IDF 1    ","       ", P&Alarm_Idf[0],							 TELE_FORM, 0, P&hid1,	V1, 0, 0},
 {"024;"," ALARM-IDF 2    ","       ", P&Alarm_Idf[1],							 TELE_FORM, 0, P&hid1,	V1, 0, 0},
 {"025;"," ALARM-IDF 3    ","       ", P&Alarm_Idf[2],							 TELE_FORM, 0, P&hid1,	V1, 0, 0},
 {"026;"," SERVICE-IDF    ","       ", P&Service_Idf,								 TELE_FORM, 0, P&hid1,	V1, 0, 0},
 {" 27;"," AMTSHOLUNG     "," JA=1  ", P&Amt_hol,									 		 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 28;"," ANRUF-MODUS    ","       ", P&Anrufmodus,							 		 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 29;"," ANRUF-MEDIUM   "," SMS=1 ", P&Anrufmedium,							 		 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 30;"," ANRUF-ANMELDUNG"," JA=1  ", P&anruf_action,						 		 US_CHAR, 0, P&hid1,	V0, 0, 0},

 {" 31;"," MSN-INIT       "," JA=1  ", P&msnInit,									 		 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {"032;"," PIN-CODE       ","       ", P&PinCode,								 		  PIN_FORM, 4, P&hid1,	V0, 0, 0},
 {"*33;"," PIN FEHLT ?    ","       ", P&pin_fehlt,								 JANEIN_FORM, 0, P&hid1,	E1, ANZEIGE, 0},
 {" 34;"," FELDSTAERKETEST"," JA=1  ", P&csqRequest,									 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {"*35;"," FELDSTAERKEWERT"," >15 OK", P&csqBuf,	 								 		 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {"*36;"," GSM-EINBUCHUNG ","       ", 0,				 								GSM_STATE_FORM, 0, P&hid1,	V0, 0, 0},
 {"*37;"," NETZBETREIBER  ","       ", P&net_name,	 								ASCII_FORM, 0, P&hid1,	V0, 0, 0},
 {" 38;"," MODEM-INIT     "," JA=1  ", P&modem_init,									 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 39;"," MODEM-NEUSTART "," JA=1  ", P&modem_neustart,							 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {"*40;"," M-STATUS/ACTION","       ", 0,				 									M_STATE_FORM, 0, P&hid1,	V0, 0, 0},
 
 {" 41;"," MODEM-STATUS   ","       ", P&modem_status,								 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" 42;"," MSTAT-ACTION   ","       ", P&mstat_action,								 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {"*43;"," ALARM-STATUS   ","       ", P&alarm_state,								 DIGR_FORM, 8, P&hid2,	V0, 0, 0},
 {"[44;"," ALARST-EXPAND  ","       ", P&alarm_state_exp[0],			 HEXBUF_FORM, 0, P&hid2,	V0, 0, 0},
 {"*45;"," ANRUF-STATUS   ","       ", P&anruf_state,								 DIGR_FORM, 8, P&hid2,	V0, 0, 0},
 {"*46;"," ANRUF-VERBINDNG","       ", P&dial_state,								 DIGR_FORM, 8, P&hid2,	V0, 0, 0},
 {" 47;"," ANRUF-PAUSE-CNT"," min   ", P&anrufpause,						 			  US_INT, 0, P&hid2,	V0, 0, 0},
 {" 48;"," STANDARD-PAUSE "," min   ", P&Standpause,						 			  US_INT, 0, P&hid2,	V0, 0, 0},
 {" 49;"," ANRUF-EXTRA    "," JA=1  ", P&anruf_extra,				  		 		 US_CHAR, 0, P&hid2,	V0, 0, 0},

 {" 50;"," ZLT-DIREKT     "," JA=1  ", P&Zlt_direkt,									 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" 51;"," DLB-FUNKTION   "," JA=1  ", P&DlbFunktion,									 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" 52;"," DC1-Protokoll  "," JA=1  ", P&dc1_prot,										 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" 53;"," DC1-Enable     "," JA=1  ", P&dc1_enable,									 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {"[60;"," TXBUF_LP       ","       ", P&TxBuf_LP[0],							 HEXBUF_FORM, 8, P&hid2,	V0, 0, 0},
 {"[61;"," RXBUF_LP       ","       ", P&RxBuf_LP[0],							 HEXBUF_FORM, 8, P&hid2,	V0, 0, 0},
 {"[62;"," TXBUF_IFU      ","       ", P&TxBuf_IFU[0],						 HEXBUF_FORM, 8, P&hid2,	V0, 0, 0},
 {"[63;"," RXBUF_IFU      ","       ", P&RxBuf_IFU[0],						 HEXBUF_FORM, 8, P&hid2,	V0, 0, 0},
 {"[64;"," TXBUF_S1       ","       ", P&TxBuf_S1[0],							 HEXBUF_FORM, 8, P&hid2,	V0, 0, 0},
 {"[65;"," RXBUF_S1       ","       ", P&RxBuf_S1[0],							 HEXBUF_FORM, 8, P&hid2,	V0, 0, 0},
 {"[66;"," TXBUF_S2       ","       ", P&TxBuf_S2[0],							 HEXBUF_FORM, 8, P&hid2,	V0, 0, 0},
 {"[67;"," RXBUF_S2       ","       ", P&RxBuf_S2[0],							 HEXBUF_FORM, 8, P&hid2,	V0, 0, 0},
 {"[68;"," TXBUF_S3       ","       ", P&TxBuf_S3[0],							 HEXBUF_FORM, 8, P&hid2,	V0, 0, 0},
 {"[69;"," RXBUF_S3       ","       ", P&RxBuf_S3[0],							 HEXBUF_FORM, 8, P&hid2,	V0, 0, 0},
 {"[68;"," TXBUF_S4       ","       ", P&TxBuf_IR[0],							 HEXBUF_FORM, 8, P&hid2,	V0, 0, 0},
 {"[69;"," RXBUF_S4       ","       ", P&RxBuf_IR[0],							 HEXBUF_FORM, 8, P&hid2,	V0, 0, 0},
 {" 70;"," RX_TEST-S1     ","       ", P&rxtest_S1,										 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" 71;"," RX_TEST-S2     ","       ", P&rxtest_S2,										 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" 72;"," RX_TEST-S3     ","       ", P&rxtest_S3,										 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" 72;"," RX_TEST-S4     ","       ", P&rxtest_S4,										 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" 73;"," RX_TEST-LP     ","       ", P&rxtest_LP,										 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" 74;"," STATUS-S1      ","       ", P&status_S1,										 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" 75;"," STATUS-S2      ","       ", P&status_S2,										 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" 76;"," STATUS-S3      ","       ", P&status_S3,										 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" 76;"," STATUS-S4      ","       ", P&status_S4,										 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" 77;"," INAKTIV-CNT    ","       ", P&inactiv_cnt,										US_INT, 0, P&hid2,	V0, 0, 0},
 {" 78;"," RX-TIMER       ","       ", P&rxtimer,												US_INT, 0, P&hid2,	V0, 0, 0},
 {" 79;"," M-TIMER        ","       ", P&mtimer,												US_INT, 0, P&hid2,	V0, 0, 0},
 {" 80;"," DIAL-TIMER     "," sek   ", P&dial_timer,									 US_LONG, 1, P&hid2,	V0, 0, 0},
 {"[81;"," DIAL-ERROR-CNT ","       ", P&dial_errcount,						 HEXBUF_FORM, 3, P&hid2,	V0, 0, 0},
 {"[82;"," DIAL-TRY       ","       ", P&dial_try,								 HEXBUF_FORM, 3, P&hid2,	V0, 0, 0},
 {" 83;"," COMMAND-TIO-CNT","       ", P&command_tio_cnt,								US_INT, 0, P&hid2,	V0, 0, 0},

// �nderung f�r R66 GPRS
 {"*90:"," GPRS-STATUS    ","       ", P&gprs_connection.ucf_status_ascii[0],		 		ASCII_FORM,  15, 	P&hid1,		V0, 0, 0}, 
 {" 91:"," USE GPRS       "," JA=1  ", P&uc_use_gprs,																US_CHAR, 			0, 	P&hid1,		V0, 0, 0},
 {" 92:"," RECONNECT GPRS "," ***   ", P&uc_gprs_reconnect,													US_CHAR, 			0, 	P&hid1,		V0, 0, 0},
 {"_93:"," APN 1          ","       ", P&gprs_connection.ucf_apn[0],		 						ASCII_FORM,  15, 	P&hid1,		V0, 0, 0},       
 {"_94:"," APN 2          ","       ", P&gprs_connection.ucf_apn[15],		 						ASCII_FORM,  15, 	P&hid1,		V0, 0, 0},
 {"_95:"," MAIN ADDRESS 1 ","       ", P&gprs_connection.ucf_main_address[0],		 		ASCII_FORM,  15, 	P&hid1,		V0, 0, 0},
 {"_96:"," MAIN ADDRESS 2 ","       ", P&gprs_connection.ucf_main_address[15],		 	ASCII_FORM,  15, 	P&hid1,		V0, 0, 0},
 {"_97:"," MAIN ADDRESS 3 ","       ", P&gprs_connection.ucf_main_address[30],		 	ASCII_FORM,  15, 	P&hid1,		V0, 0, 0},
 {"*->;"," curr address 1 ","       ", P&gprs_connection.ucf_current_address[0],		ASCII_FORM,  15, 	P&hid2,		V0, 0, 0},
 {"*->;"," curr address 2 ","       ", P&gprs_connection.ucf_current_address[15],		ASCII_FORM,  15, 	P&hid2,		V0, 0, 0},
 {"*->;"," curr address 3 ","       ", P&gprs_connection.ucf_current_address[30],		ASCII_FORM,  15, 	P&hid2,		V0, 0, 0},

}; 



/*------------------------------ Testgruppe ------------------------------------------*/
const Pgrup tes[] = {
 {"***:"," TEST-ANZEIGEN  ","       ", P&Leer15,						ASCII_FORM, 0, P&hid4,	V0, 0, 0},
 {" 00:"," KomtabKontrolle","       ", P&dae_test,				KOMTEST_FORM, 0, P&hid4,	V0, 0, 0},

 {" ->:"," unbekannt.Alarm"," idx   ", P&unbek_Alarm,			 US_CHAR, 0, P&hid4,	V0, 0, 0},

 {"*01:"," PT_ANIN1       "," Digit ", P&pt_anin[0],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*02:"," PT_ANIN2       "," Digit ", P&pt_anin[1],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*03:"," PT_ANIN3       "," Digit ", P&pt_anin[2],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*04:"," PT_ANIN4       "," Digit ", P&pt_anin[3],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*05:"," PT_ANIN5       "," Digit ", P&pt_anin[4],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*06:"," PT_ANIN6       "," Digit ", P&pt_anin[5],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*07:"," PT_ANIN7       "," Digit ", P&pt_anin[6],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*08:"," PT_ANIN8       "," Digit ", P&pt_anin[7],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*09:"," PT_ANIN_REF1   "," Digit ", P&pt_anin[8],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*10:"," PT_ANIN_REF2   "," Digit ", P&pt_anin[9],				US_INT, 0, P&hid4,	V0, 0, 0},
 
 {"*11:"," ANA_ANIN3      "," Digit ", P&ana_anin[0],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*12:"," ANA_ANIN4      "," Digit ", P&ana_anin[1],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*13:"," ANA_ANIN5      "," Digit ", P&ana_anin[2],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*14:"," ANA_ANIN6      "," Digit ", P&ana_anin[3],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*15:"," ANA_ANIN7      "," Digit ", P&ana_anin[4],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*16:"," ANA_ANIN8      "," Digit ", P&ana_anin[5],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*17:"," ANA_ANIN9      "," Digit ", P&ana_anin[6],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*18:"," ANA_ANIN10     "," Digit ", P&ana_anin[7],				US_INT, 0, P&hid4,	V0, 0, 0},

 {"*21:"," DIG_ANIN3      "," Digit ", P&dig_anin[0],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*22:"," DIG_ANIN4      "," Digit ", P&dig_anin[1],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*23:"," DIG_ANIN5      "," Digit ", P&dig_anin[2],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*24:"," DIG_ANIN6      "," Digit ", P&dig_anin[3],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*25:"," DIG_ANIN7      "," Digit ", P&dig_anin[4],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*26:"," DIG_ANIN8      "," Digit ", P&dig_anin[5],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*27:"," DIG_ANIN9      "," Digit ", P&dig_anin[6],				US_INT, 0, P&hid4,	V0, 0, 0},
 {"*28:"," DIG_ANIN10     "," Digit ", P&dig_anin[7],				US_INT, 0, P&hid4,	V0, 0, 0},

 {" 30:"," DE-SIMULATION  "," 1=JA  ", P&de_simul,					US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 31:"," DIG_IN3        ","       ", P&di_mewe[0].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 32:"," DIG_IN4        ","       ", P&di_mewe[1].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 33:"," DIG_IN5        ","       ", P&di_mewe[2].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 34:"," DIG_IN6        ","       ", P&di_mewe[3].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 35:"," DIG_IN7        ","       ", P&di_mewe[4].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 36:"," DIG_IN8        ","       ", P&di_mewe[5].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 37:"," DIG_IN9        ","       ", P&di_mewe[6].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 38:"," DIG_IN10       ","       ", P&di_mewe[7].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 
 {" 39:"," R37_1 DIG_IN1  ","       ", P&mod37[0].di_mewe[0].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R37_1 DIG_IN2  ","       ", P&mod37[0].di_mewe[1].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R37_1 DIG_IN3  ","       ", P&mod37[0].di_mewe[2].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R37_1 DIG_IN4  ","       ", P&mod37[0].di_mewe[3].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R37_1 DIG_IN5  ","       ", P&mod37[0].di_mewe[4].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R37_1 DIG_IN6  ","       ", P&mod37[0].di_mewe[5].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},

 {" 40:"," R39_1 DIG_IN1  ","       ", P&mod39[0].di_mewe[0].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R39_1 DIG_IN2  ","       ", P&mod39[0].di_mewe[1].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R39_1 DIG_IN3  ","       ", P&mod39[0].di_mewe[2].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R39_1 DIG_IN4  ","       ", P&mod39[0].di_mewe[3].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R39_1 DIG_IN5  ","       ", P&mod39[0].di_mewe[4].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R39_1 DIG_IN6  ","       ", P&mod39[0].di_mewe[5].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R39_1 DIG_IN7  ","       ", P&mod39[0].di_mewe[6].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R39_1 DIG_IN8  ","       ", P&mod39[0].di_mewe[7].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R39_1 DIG_IN9  ","       ", P&mod39[0].di_mewe[8].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R39_1 DIG_IN10 ","       ", P&mod39[0].di_mewe[9].bwert,	US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R39_1 DIG_IN11 ","       ", P&mod39[0].di_mewe[10].bwert,US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" ->:"," R39_1 DIG_IN12 ","       ", P&mod39[0].di_mewe[11].bwert,US_CHAR, 0, P&hid4,	V0, 0, 0},

 {"*41:"," DIG_OUT1       ","       ", P&Dout[0].wert,		 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {"*42:"," DIG_OUT2       ","       ", P&Dout[1].wert,		 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {"*43:"," DIG_OUT3       ","       ", P&Dout[2].wert,		 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {"*44:"," DIG_OUT4       ","       ", P&Dout[3].wert,		 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {"*45:"," DIG_OUT5       ","       ", P&Dout[4].wert,		 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {"*46:"," DIG_OUT6       ","       ", P&Dout[5].wert,		 US_CHAR, 0, P&hid4,	V0, 0, 0},

 {"*51:"," ANALOG-AUSGANG1"," Digit ", P&anout[0],				 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {"*52:"," ANALOG-AUSGANG2"," Digit ", P&anout[1],				 US_CHAR, 0, P&hid4,	V0, 0, 0},

 {"*61:"," PT-CONTROL     ","       ", P&ptcontrol,			 DIGR_FORM, 8, P&hid4,	V0, 0, 0},
 {"*62:"," AE-CONTROL     ","       ", P&aecontrol,			 DIGR_FORM, 8, P&hid4,	V0, 0, 0},
 {"*63:"," ASW-CONTROL    ","       ", P&aswcontrol,		 DIGR_FORM, 8, P&hid4,	V0, 0, 0},
 {"*64:"," CNT-CONTROL    ","       ", P&cntcontrol,		 DIGR_FORM, 8, P&hid4,	V0, 0, 0},
 {" 65:"," AE-ZERO-CONTROL","       ", P&ae_zero_control,DIGR_FORM, 8, P&hid4,	V0, 0, 0},

 {"[68:"," AKT. LONGZEIT  ","       ", P&LongZeit,		 HEXBUF_FORM, 4, P&hid4,	V0},
 {"[69:"," WRITE TIMESTAMP","       ", P&ulWriteStamp, HEXBUF_FORM, 4, P&hid4,	V0},

 {" 70:"," SOM_BEGIN_MONAT","       ", P&Som_Begin,				 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 71:"," SOM_WOEND      ","       ", P&Som_Woend,				 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 72:"," WIN_BEGIN_MONAT","       ", P&Win_Begin,				 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 73:"," WIN_WOEND      ","       ", P&Win_Woend,				 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 74:"," SWZEIT_MERKER  ","       ", P&swzeit,					 US_CHAR, 0, P&hid4,	V0, 0, 0},
 
 {"*75:"," LCD-Mode       ","       ", P&pub_LCD_Mode,		 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {"*76:"," FRONT-Status   ","       ", P&front_stat,			 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 77:"," bicmove_flag   ","       ", P&bicmove_flag,		 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 78:"," bicmove_count  ","       ", P&bicmove_count,		 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 79;"," rtc_err_cnt    ","       ", P&rtc_err_cnt,			 US_CHAR, 0, P&hid4,	V0, 0, 0},

 {" 80;"," noi_sekcnt     "," s     ", P&noi_sekcnt,				US_INT, 0, P&hid4,	V0, 0, 0},
 {" 81;"," noi_us_main_cnt"," s     ", P&noi_user_main_cnt,US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 82;"," noi_mainex     ","       ", P&noi_mainex,				US_INT, 0, P&hid4,	V0, 0, 0},
{" ->;"," noi_rts_cnt    ","       ", P&noi_rts_cnt,			 US_CHAR, 0, P&hid4,	V0, 0, 0},
{" 83;"," spcnt SPEICH   ","       ", P&spcnt,						 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 84;"," sms-anzahl     ","       ", P&sms_anz,					 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 85;"," sms-count      ","       ", P&sms_count,		 		 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {"[86;"," sstm           ","       ", P&sstm[0],			 HEXBUF_FORM, 0, P&hid4,	V0, 0, 0},
 {"[87;"," sstm_old       ","       ", P&sstm_old[0],	 HEXBUF_FORM, 0, P&hid4,	V0, 0, 0},
 {" 88;"," archiv wr-err  ","       ", P&archivWriteError,							US_CHAR,0, P&hid4,	V0, 0, 0},
 {" 89;"," archiv-par rep ","       ", P&archivParRep,			 						US_CHAR,0, P&hid4,	V0, 0, 0},
 {" ->;"," moni_heap_dummy","       ", P&moni_heap_dummy,			 					US_INT, 0, P&hid4,	V0, 0, 0},	// Josch-SDM
 

 {"*90:"," ZEITMARKE ZEIT ","       ", P&zm_time,										ASCII_FORM, 8, P&hid4,	V0, 0, 0},
 {"*91:"," ZEITMARKE DATUM","       ", P&zm_date,										ASCII_FORM, 8, P&hid4,	V0, 0, 0},
 {"*92:"," S-COMPILE ZEIT ","       ", P&compile_time,							ASCII_FORM, 0, P&hid4,	V0, 0, 0},
 {"*->:"," S-COMPILE DATUM","       ", P&compile_date,							ASCII_FORM, 0, P&hid4,	V0, 0, 0},
 {"*93:"," U-COMPILE ZEIT ","       ", P&user_compile_time,					ASCII_FORM, 0, P&hid4,	V0, 0, 0},
 {"*->:"," U-COMPILE DATUM","       ", P&user_compile_date,					ASCII_FORM, 0, P&hid4,	V0, 0, 0},
 {" 94;"," TRIGPUNKT R5,6k"," %     ", (char *)&Trigpunkt_R56,				 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {"*->;"," TRIGGER R5,6k  ","       ", (char *)&trigger_R56,					  US_INT, 0, P&hid4,	V0, 0, 0},
 {" 95;"," TRIGPUNKT NAMUR"," %     ", (char *)&Trigpunkt_NAMUR,			 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {"*->;"," TRIGGER NAMUR  ","       ", (char *)&trigger_NAMUR,				  US_INT, 0, P&hid4,	V0, 0, 0},
 {" 96;"," TRIGPUNKT KABEL"," %     ", (char *)&Kabelpunkt,						 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {"*->;"," KABELTRIGGER   ","       ", (char *)&kabeltrigger,					  US_INT, 0, P&hid4,	V0, 0, 0},
 {" 97;"," TRIGPUNKT KURZ "," %     ", (char *)&Kurzpunkt,						 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {"*->;"," KURZTRIGGER    ","       ", (char *)&kurztrigger,					  US_INT, 0, P&hid4,	V0, 0, 0},

 {" 98:"," CHAR_TEST1     ","       ", P&char_test1,			 US_CHAR, 0, P&hid4,	V0, 0, 0},
 {" 99:"," TP0-9 LOESCHEN ","       ", P&testClear,				 US_CHAR, 0, P&hid4,	V0, 0, 0},
 
 {" ->;"," TP0            ","       ", P&testPoint[0],			 S_INT, 0, P&hid4,	V0, 0, 0},
 {" ->;"," TP1            ","       ", P&testPoint[1],			 S_INT, 0, P&hid4,	V0, 0, 0},
 {" ->;"," TP2            ","       ", P&testPoint[2],			 S_INT, 0, P&hid4,	V0, 0, 0},
 {" ->;"," TP3            ","       ", P&testPoint[3],			 S_INT, 0, P&hid4,	V0, 0, 0},  
 {" ->;"," TP4            ","       ", P&testPoint[4],			 S_INT, 0, P&hid4,	V0, 0, 0},
 {" ->;"," TP5            ","       ", P&testPoint[5],			 S_INT, 0, P&hid4,	V0, 0, 0},
 {" ->;"," TP6            ","       ", P&testPoint[6],			 S_INT, 0, P&hid4,	V0, 0, 0},
 {" ->;"," TP7            ","       ", P&testPoint[7],			 S_INT, 0, P&hid4,	V0, 0, 0},  
 {" ->;"," TP8            ","       ", P&testPoint[8],			 S_INT, 0, P&hid4,	V0, 0, 0},
 {" ->;"," TP9            ","       ", P&testPoint[9],			 S_INT, 0, P&hid4,	V0, 0, 0},     
  
};  

/*------------------------------ Testgruppe GPRS ------------------------------------------*/
const Pgrup gpr[] = {
 {"***:"," GPRS-TESTGRUPPE","       ", P&Leer15,						ASCII_FORM, 0, P&hid4,	V0, 0, 0},
 {" ->;"," Work Delay Ctr "," sek   ", P&gprs_error_handling.ui_work_delay_ctr,						US_INT, 			0, 	P&hid4,		V0, 0, 0},	
 {" ->;"," Work Reset Val "," sek   ", P&gprs_error_handling.ui_reset_delay_value,				US_INT, 			0, 	P&hid4,		V0, 0, 0},	
 {" ->;"," Work Reset Ctr "," sek   ", P&gprs_error_handling.ui_reset_delay_ctr,					US_INT, 			0, 	P&hid4,		V0, 0, 0},	 
 {" ->;"," Reinit Counter ","       ", P&gprs_error_handling.uc_reinit_counter,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},  
 {" ->;"," Modem Reset Ctr","       ", P&gprs_error_handling.uc_modem_reset_counter,			US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," R66 Reset Ctr  ","       ", P&gprs_error_handling.uc_r66_reset_counter,				US_CHAR, 			0, 	P&hid4,		V0, 0, 0},  
 {" ->;"," Wrong Adr ctr  ","       ", P&gprs_error_handling.uc_wrong_address_counter,		US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
    
 {" 00;"," Error Code 1   ","       ", P&gprs_error_handling.memory[0].uc_error_code,			US_CHAR, 			0, 	P&hid4,		V0, 0, 0},  
 {" 01;"," Error Telegr 1 ","       ", P&gprs_error_handling.memory[0].ucf_telegram[0],		HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 1 Std","       ", P&gprs_error_handling.memory[0].uc_std,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 1 Min","       ", P&gprs_error_handling.memory[0].uc_min,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 1 Sek","       ", P&gprs_error_handling.memory[0].uc_sec,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},      	 
 {" 02;"," Error Code 2   ","       ", P&gprs_error_handling.memory[1].uc_error_code,			US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" 03;"," Error Telegr 2 ","       ", P&gprs_error_handling.memory[1].ucf_telegram[0],		HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 2 Std","       ", P&gprs_error_handling.memory[1].uc_std,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 2 Min","       ", P&gprs_error_handling.memory[1].uc_min,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 2 Sek","       ", P&gprs_error_handling.memory[1].uc_sec,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},  
 {" 04;"," Error Code 3   ","       ", P&gprs_error_handling.memory[2].uc_error_code,			US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" 05;"," Error Telegr 3 ","       ", P&gprs_error_handling.memory[2].ucf_telegram[0],		HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0},
 {" ->;"," Timestamp 3 Std","       ", P&gprs_error_handling.memory[2].uc_std,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" ->;"," Timestamp 3 Min","       ", P&gprs_error_handling.memory[2].uc_min,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" ->;"," Timestamp 3 Sek","       ", P&gprs_error_handling.memory[2].uc_sec,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" 06;"," Error Code 4   ","       ", P&gprs_error_handling.memory[3].uc_error_code,			US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" 07;"," Error Telegr 4 ","       ", P&gprs_error_handling.memory[3].ucf_telegram[0],		HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 4 Std","       ", P&gprs_error_handling.memory[3].uc_std,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" ->;"," Timestamp 4 Min","       ", P&gprs_error_handling.memory[3].uc_min,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" ->;"," Timestamp 4 Sek","       ", P&gprs_error_handling.memory[3].uc_sec,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},       
 {" 08;"," Error Code 5   ","       ", P&gprs_error_handling.memory[4].uc_error_code,			US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 
 {" 09;"," Error Telegr 5 ","       ", P&gprs_error_handling.memory[4].ucf_telegram[0],		HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0},
 {" ->;"," Timestamp 5 Std","       ", P&gprs_error_handling.memory[4].uc_std,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" ->;"," Timestamp 5 Min","       ", P&gprs_error_handling.memory[4].uc_min,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" ->;"," Timestamp 5 Sek","       ", P&gprs_error_handling.memory[4].uc_sec,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 
 {" 10;"," Error Code 6   ","       ", P&gprs_error_handling.memory[5].uc_error_code,			US_CHAR, 			0, 	P&hid4,		V0, 0, 0},  
 {" 11;"," Error Telegr 6 ","       ", P&gprs_error_handling.memory[5].ucf_telegram[0],		HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 6 Std","       ", P&gprs_error_handling.memory[5].uc_std,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 6 Min","       ", P&gprs_error_handling.memory[5].uc_min,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 6 Sek","       ", P&gprs_error_handling.memory[5].uc_sec,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},      	 
 {" 12;"," Error Code 7   ","       ", P&gprs_error_handling.memory[6].uc_error_code,			US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" 13;"," Error Telegr 7 ","       ", P&gprs_error_handling.memory[6].ucf_telegram[0],		HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 7 Std","       ", P&gprs_error_handling.memory[6].uc_std,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 7 Min","       ", P&gprs_error_handling.memory[6].uc_min,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 7 Sek","       ", P&gprs_error_handling.memory[6].uc_sec,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},  
 {" 14;"," Error Code 8   ","       ", P&gprs_error_handling.memory[7].uc_error_code,			US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" 15;"," Error Telegr 8 ","       ", P&gprs_error_handling.memory[7].ucf_telegram[0],		HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0},
 {" ->;"," Timestamp 8 Std","       ", P&gprs_error_handling.memory[7].uc_std,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" ->;"," Timestamp 8 Min","       ", P&gprs_error_handling.memory[7].uc_min,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" ->;"," Timestamp 8 Sek","       ", P&gprs_error_handling.memory[7].uc_sec,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" 16;"," Error Code 9   ","       ", P&gprs_error_handling.memory[8].uc_error_code,			US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" 17;"," Error Telegr 9 ","       ", P&gprs_error_handling.memory[8].ucf_telegram[0],		HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0}, 
 {" ->;"," Timestamp 9 Std","       ", P&gprs_error_handling.memory[8].uc_std,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" ->;"," Timestamp 9 Min","       ", P&gprs_error_handling.memory[8].uc_min,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" ->;"," Timestamp 9 Sek","       ", P&gprs_error_handling.memory[8].uc_sec,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},       
 {" 18;"," Error Code 10  ","       ", P&gprs_error_handling.memory[9].uc_error_code,			US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 
 {" 19;"," Error Telegr 10","       ", P&gprs_error_handling.memory[9].ucf_telegram[0],		HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0},
 {" ->;"," Timestamp10 Std","       ", P&gprs_error_handling.memory[9].uc_std,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" ->;"," Timestamp10 Min","       ", P&gprs_error_handling.memory[9].uc_min,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},   
 {" ->;"," Timestamp10 Sek","       ", P&gprs_error_handling.memory[9].uc_sec,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},  

 {" 20;"," Error Code Idx "," 0..9  ", P&gprs_error_handling.uc_error_code_idx,						US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 	           		  
 {" 21;"," rx overflow ctr","       ", P&gprs_error_handling.ui_buffer_overflow_ctr,      US_INT, 			0, 	P&hid4,		V0, 0, 0},
	
// Modeminfos
 {" ->;"," Sim ID         ","       ", P&gprs_modem_info.ucf_sim_id[0],										ASCII_FORM,  15, 	P&hid4,		V0, 0, 0},
 {" ->;"," Sim ID         ","       ", P&gprs_modem_info.ucf_sim_id[16],									ASCII_FORM,   5, 	P&hid4,		V0, 0, 0},  
 {" ->;"," IMEI           ","       ", P&gprs_modem_info.ucf_imei[0],											ASCII_FORM,  16, 	P&hid4,		V0, 0, 0},
 {" ->;"," Modul Type     ","       ", P&gprs_modem_info.ucf_modul[0],										ASCII_FORM,   6, 	P&hid4,		V0, 0, 0},
 {" ->;"," MCC            ","       ", P&gprs_modem_info.ui_mcc,													US_INT, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," MNC            ","       ", P&gprs_modem_info.ui_mnc,													US_INT, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," LAC            ","       ", P&gprs_modem_info.ui_lac,													US_INT, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," CI             ","       ", P&gprs_modem_info.ui_ci,														US_INT, 			0, 	P&hid4,		V0, 0, 0},   
 {" ->;"," RSSI           ","       ", P&gprs_modem_info.uc_rssi,													US_CHAR, 			0, 	P&hid4,		V0, 0, 0}, 


// Werte f�rs Debuggen  
 {"[->;"," RX Buffer Tel  ","       ", P&ucf_rx_buffer[0],																HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0},			
 {"[->;"," TX Buffer Tel  ","       ", P&ucf_tx_buffer[0],																HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0},	
 {"[->;"," RX Buffer LP   ","       ", P&RxBuf_LP[0],																			HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0},			
 {"[->;"," TX Buffer LP   ","       ", P&TxBuf_LP[0],																			HEXBUF_FORM,	0, 	P&hid4,		V0, 0, 0},
 {" ->;"," Main State     ","       ", P&uc_gprs_main_state,                   						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," Init State     ","       ", P&uc_gprs_init_state,                   						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," Work State     ","       ", P&uc_gprs_work_state,                   						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," Choice         ","       ", P&uc_gprs_choice,                       						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," Responce Code  ","       ", P&uc_gprs_responcecode,                 						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," rx start index ","       ", P&uc_gprs_rx_start_idx,                 						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," telegr ready   ","       ", P&uc_gprs_rx_telegram_ready,            						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," timeout value  ","       ", P&ui_gprs_rx_timeout_value,               					US_INT, 			0, 	P&hid4,		V0, 0, 0},	
 {" ->;"," timeout ctr    ","       ", P&ui_gprs_rx_timeout_ctr,               						US_INT, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," rx lenght      ","       ", P&uc_gprs_rx_lenght,                    						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," overflow requer","       ", P&uc_gprs_rx_buffer_overflow_requered,  						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," TransparentMode","       ", P&uc_gprs_transperantmode_activ,        						US_CHAR, 			0, 	P&hid4,		V0, 0, 0},
 {" ->;"," work handler   ","       ", P&ui_gprs_work_handler,        										US_INT, 			0, 	P&hid4,		V0, 0, 0},   
};

/*------------------------------ System ----------------------------------------------*/
const Pgrup sys[] = {
 {"***;"," SYSTEM-ANZEIGEN","       ", P&Ein_Ausg,					ASCII_FORM, 0, P&hid1,	V0, 0, 0},
 {" 00;"," PARAM. SICHERN "," JA=1  ", P&bicmove_wunsch,	BICMOVE_FORM, 0, P&hid1,	V0, 0, 0},
 {"*01;"," SENSOR_IN1 TEMP"," C    ", P&pt_mewe[0].messw,		ANA_FORM, 1, P&hid1,	V0, 0, 0},
 {" 01;"," SENSOR_IN1 KORR"," Ohm   ", P&Pt_Korr[0],						 S_INT, 1, P&hid1,	V0, 0, 0},
 {" 01;"," SENSOR_IN1 FILT"," 0-9   ", P&Pt_Filt[0],					 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 01;"," SENSOR_IN1 TYP ","       ", P&Tp_Type[0],				 FTYP_FORM, 0, P&hid1,	V0, 0, 0},

 {"*02;"," SENSOR_IN2 TEMP"," C    ", P&pt_mewe[1].messw,		ANA_FORM, 1, P&hid1,	V0, 0, 0},
 {" 02;"," SENSOR_IN2 KORR"," Ohm   ", P&Pt_Korr[1],						 S_INT, 1, P&hid1,	V0, 0, 0},
 {" 02;"," SENSOR_IN2 FILT"," 0-9   ", P&Pt_Filt[1],					 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 02;"," SENSOR_IN2 TYP ","       ", P&Tp_Type[1],					FTYP_FORM, 0, P&hid1,	V0, 0, 0},

 {"*03;"," SENSOR_IN3 TEMP"," C    ", P&pt_mewe[2].messw,		ANA_FORM, 1, P&hid1,	V0, 0, 0},
 {" 03;"," SENSOR_IN3 KORR"," Ohm   ", P&Pt_Korr[2],						 S_INT, 1, P&hid1,	V0, 0, 0},
 {" 03;"," SENSOR_IN3 FILT"," 0-9   ", P&Pt_Filt[2],					 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 03;"," SENSOR_IN3 TYP ","       ", P&Tp_Type[2],				 FTYP_FORM, 0, P&hid1,	V0, 0, 0},

 {"*04;"," SENSOR_IN4 TEMP"," C    ", P&pt_mewe[3].messw,		ANA_FORM, 1, P&hid1,	V0, 0, 0},
 {" 04;"," SENSOR_IN4 KORR"," Ohm   ", P&Pt_Korr[3],						 S_INT, 1, P&hid1,	V0, 0, 0},
 {" 04;"," SENSOR_IN4 FILT"," 0-9   ", P&Pt_Filt[3],					 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 04;"," SENSOR_IN4 TYP ","       ", P&Tp_Type[3],				 FTYP_FORM, 0, P&hid1,	V0, 0, 0},

 {"*05;"," SENSOR_IN5 TEMP"," C    ", P&pt_mewe[4].messw,		ANA_FORM, 1, P&hid1,	V0, 0, 0},
 {" 05;"," SENSOR_IN5 KORR"," Ohm   ", P&Pt_Korr[4],						 S_INT, 1, P&hid1,	V0, 0, 0},
 {" 05;"," SENSOR_IN5 FILT"," 0-9   ", P&Pt_Filt[4],					 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 05;"," SENSOR_IN5 TYP ","       ", P&Tp_Type[4],				 FTYP_FORM, 0, P&hid1,	V0, 0, 0},

 {"*06;"," SENSOR_IN6 TEMP"," C    ", P&pt_mewe[5].messw,		ANA_FORM, 1, P&hid1,	V0, 0, 0},
 {" 06;"," SENSOR_IN6 KORR"," Ohm   ", P&Pt_Korr[5],						 S_INT, 1, P&hid1,	V0, 0, 0},
 {" 06;"," SENSOR_IN6 FILT"," 0-9   ", P&Pt_Filt[5],					 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 06;"," SENSOR_IN6 TYP ","       ", P&Tp_Type[5],				 FTYP_FORM, 0, P&hid1,	V0, 0, 0},

 {"*07;"," SENSOR_IN7 TEMP"," C    ", P&pt_mewe[6].messw,		ANA_FORM, 1, P&hid1,	V0, 0, 0},
 {" 07;"," SENSOR_IN7 KORR"," Ohm   ", P&Pt_Korr[6],						 S_INT, 1, P&hid1,	V0, 0, 0},
 {" 07;"," SENSOR_IN7 FILT"," 0-9   ", P&Pt_Filt[6],					 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 07;"," SENSOR_IN7 TYP ","       ", P&Tp_Type[6],				 FTYP_FORM, 0, P&hid1,	V0, 0, 0},

 {"*08;"," SENSOR_IN8 TEMP"," C    ", P&pt_mewe[7].messw,		ANA_FORM, 1, P&hid1,	V0, 0, 0},
 {" 08;"," SENSOR_IN8 KORR"," Ohm   ", P&Pt_Korr[7],						 S_INT, 1, P&hid1,	V0, 0, 0},
 {" 08;"," SENSOR_IN8 FILT"," 0-9   ", P&Pt_Filt[7],					 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 08;"," SENSOR_IN8 TYP ","       ", P&Tp_Type[7],				 FTYP_FORM, 0, P&hid1,	V0, 0, 0},
 
 {" 09;"," SENSOR-IN LIFE "," 1-8   ", P&Pt_Life,			 			 DIGL_FORM, 8, P&hid1,	V0, 0, 0},
 {" 10;"," ANALOG-IN LIFE "," 3-10  ", P&AE_Life,			 			 DIGL_FORM, 8, P&hid1,	V0, 0, 0},

 {"*11;"," ANALOG_IN3     "," Volt  ", P&ae_mewe[0].messw,		ANA_FORM, 2, P&hid1,	V0, 0, 0},
 {"*12;"," ANALOG_IN4     "," Volt  ", P&ae_mewe[1].messw,		ANA_FORM, 2, P&hid1,	V0, 0, 0},
 {"*13;"," ANALOG_IN5     "," Volt  ", P&ae_mewe[2].messw,		ANA_FORM, 2, P&hid1,	V0, 0, 0},
 {"*14;"," ANALOG_IN6     "," Volt  ", P&ae_mewe[3].messw,		ANA_FORM, 2, P&hid1,	V0, 0, 0},
 {"*15;"," ANALOG_IN7     "," Volt  ", P&ae_mewe[4].messw,		ANA_FORM, 2, P&hid1,	V0, 0, 0},
 {"*16;"," ANALOG_IN8     "," Volt  ", P&ae_mewe[5].messw,		ANA_FORM, 2, P&hid1,	V0, 0, 0},
 {"*17;"," ANALOG_IN9     "," Volt  ", P&ae_mewe[6].messw,		ANA_FORM, 2, P&hid1,	V0, 0, 0},
 {"*18;"," ANALOG_IN10    "," Volt  ", P&ae_mewe[7].messw,		ANA_FORM, 2, P&hid1,	V0, 0, 0},

 {"*31;"," ANALOG-AUSGANG1"," Volt  ", P&AoutSk[0],							US_INT, 2, P&hid1,	V0, 0, 0},
 {" ->;"," SKALIERUNG 0%  "," Volt  ", P&AASkal[0].NullP,				US_INT, 2, P&hid1,	V0, 0, 0},
 {" ->;"," SKALIERUNG 100%"," Volt  ", P&AASkal[0].HundP,				US_INT, 2, P&hid1,	V0, 0, 0},
 {"*32;"," ANALOG-AUSGANG2"," Volt  ", P&AoutSk[1],							US_INT, 2, P&hid1,	V0, 0, 0},
 {" ->;"," SKALIERUNG 0%  "," Volt  ", P&AASkal[1].NullP,				US_INT, 2, P&hid1,	V0, 0, 0},
 {" ->;"," SKALIERUNG 100%"," Volt  ", P&AASkal[1].HundP,				US_INT, 2, P&hid1,	V0, 0, 0},

 {"*33;"," DIGITAL-EINGANG"," IN3-10", P&Diginp,						DIGAE_FORM, 8, P&hid1,	V0, 0, 0},
 {"*34;"," DE BRUCH(NAMUR)"," IN3-10", P&Bruch,							DIGAE_FORM, 8, P&hid1,	V0, 0, 0},
 {"*35;"," DE KURZ (NAMUR)"," IN3-10", P&Kurz,							DIGAE_FORM, 8, P&hid1,	V0, 0, 0},

 {"*36;"," DIGITAL-AUSGANG"," 1-6   ", P&Digout,			 			 DIGL_FORM, 6, P&hid1,	V0, 0, 0},

 {" 37;"," AUSSENTEMP BC  "," C    ", P&Ta1Bc,									 S_INT, 1, P&hid1,	V0, 0, 0},
 {"*38;"," COUNTDOWN  BC  "," min   ", P&CountDwBc,						 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 39;"," VORRANG    BC  "," JA=1  ", P&bc_vorra,						 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" 40;"," SIMULIER   BC  "," min   ", P&bc_simu,						 	 US_CHAR, 0, P&hid1,	V0, 0, 0},
 {" ->;"," Cool BC        ","       ", P&CoolBc,					 	 DIGR_FORM, 8, P&hid2,	V0, 0, 0},
 {" ->;"," Cool BC Status ","       ", P&CoolBcStat,			 	 DIGR_FORM, 8, P&hid2,	V0, 0, 0},
 {" ->;"," Heat BC        ","       ", P&HeatBc,					 	 DIGR_FORM, 8, P&hid2,	V0, 0, 0},
 {" ->;"," Heat BC Status ","       ", P&HeatBcStat,			 	 DIGR_FORM, 8, P&hid2,	V0, 0, 0},
 {" ->;"," C.down CoolHeat"," min   ", P&CountDwBcStat,			 	 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" ->;"," Sperre Broadc. "," JA=1  ", P&bc_sperre,						 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {" ->;"," Aktuelle Ta    "," C    ", P&ta,									ANA_FORM, 1, P&hid2,	V0, 0, 0},


#include "parli_module.h"




 {"*80;"," RESET COUNTER  ","       ", P&Resetcnt,							US_INT, 0, P&hid1,	V0, 0, 0},
 {"*->;"," RESET DATUM    ","       ", P&reset_date,			 	 DATE_FORM, 1, P&hid1,	V0, 0, 0},
 {"*->;"," RESET UHRZEIT  ","       ", P&reset_time,			 	 DATE_FORM, 2, P&hid1,	V0, 0, 0},
 {"*81;"," BOARD I2C ERROR"," 0=NEIN", P&BIC_Error,			 			 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {"*82;"," RTC-UHR ERROR  ","       ", P&rtc_error,				 JANEIN_FORM, 0, P&hid1,	E1, EREIGNIS, 0},
 {"*83;"," MAIN-CRASH:TASK","       ", P&noi_reanimate,			 TASK_FORM, 0, P&hid1,	E1, EREIGNIS, 0},
 
#if ARCHIV_ANL == 1		// Archiv nur mit Ferro-Ram
 {"*84;"," ARCHIVIERUNG ? ","       ", P&archivAktiv,		 JANEIN_FORM, 0, P&hid1,		V0, 0, 0},
 {"*85;"," ANZAHL ARCH-DAE","       ", P&arch_par,				US_CHAR, 		0, P&hid1,	V0, 0, 0},
#endif
#if ARCHIV_SDM == 1		// Josch-SDM : Archiv mit SD-Card-Memory
 {"*86;"," SDM-ARCH-STATUS","       ", P&a_erg_text,	 DYN_ASCII_FORM, 0, P&hid1,	V0, 0, 0},
 {"*87;"," SDM-CARD-STATUS","       ", P&c_erg_text,	 DYN_ASCII_FORM, 0, P&hid1,	V0, 0, 0},
 {"*88;"," SDM-AKT-DAE,EXP","       ", P&sdm_akt_dae,		  	US_INT,  2, P&hid1,	V0, 0, 0},
 {" ->;"," SDM-ARCHIV-INIT","       ", P&werks_sdm_code,		  US_INT,  2, P&hid1,	V1, 0, 0},
 {" ->;"," SDM-DAE-INIT   "," -DAE,E", P&reset_dae,			    	  S_INT, 1, P&hid1,	V1, 0, 0},
 {" ->;"," SDM-ARCHIV-STOP"," JA=1  ", P&sdm_arch_stop,		  US_CHAR, 0, P&hid1,	V0, 0, 0},
 {"*->;"," FerroRAM2 FEHLT","       ", P&ferro_err,			  JANEIN_FORM, 0, P&hid1,	E1, EREIGNIS, 0},
 {"*->;"," SDHC-Card FEHLT","       ", P&card_err,			  JANEIN_FORM, 0, P&hid1,	E1, EREIGNIS, 0},
 {"*->;"," komtab_changed ","       ", P&komtab_changed,			US_INT,  0, P&hid2,	V0, 0, 0},
 {"*->;"," moni_heap_error","       ", P&moni_heap_error,			 US_INT, 0, P&hid2,	V0, 0, 0},
 {" ->;"," test_start     ","       ", P&test_start,			    US_CHAR, 0, P&hid2,	V0, 0, 0},
#endif

 {" 89;"," SCHALTPAUSE    "," s     ", P&Schalt_Pause,				US_CHAR, 	0, P&hid1,	V0, 0, 0},

 {" 90;"," PARAM. SICHERN "," JA=1  ", P&bicmove_wunsch,	BICMOVE_FORM, 0, P&hid1,	V0, 0, 0},
{"*91;"," PROTECTED-VERS.","       ", P&pub_FVers,			 		 DATE_FORM, 0, P&hid2,	V0, 0, 0},
 {"*92;"," PRODUKT-IDF    ","       ", P&Produkt_Idf, 			PROID_FORM, 0, P&hid1,	V0, 0, 0},
 {"*93;"," KATEGORIE-TYP  ","       ", P&Kategorie_Typ,			ASCII_FORM, 0, P&hid2,	V0, 0, 0},
 {"*94;"," KATEGORIE-VERS.","       ", P&Kategorie_Vers,	 	 DATE_FORM, 0, P&hid2,	V0, 0, 0},
 {"*95;"," PROJEKT-TYP    ","       ", P&proj_typ,						 US_CHAR, 0, P&hid2,	V0, 0, 0},
 {"*96;"," PROGRAMM-TYP   ","       ", P&Version_PTyp, 			ASCII_FORM, 0, P&hid1,	V1, 0, 0},
 {"*97;"," PROGR.-VERSION ","       ", P&Version_PVers,			 DATE_FORM, 0, P&hid1,	V1, 0, 0},
 {"*98;"," SYSTEM-VERSION ","       ", P&Version_SVers, 		 DATE_FORM, 0, P&hid1,	V1, 0, 0},
 {" 99;"," KALTSTART      "," JA=1  ", P&Kaltstart,				 KALTST_FORM, 0, P&hid1,	V0, 0, 0},
 {" ->;"," NEUSTART       "," JA=1  ", P&Neustart,					NEUST_FORM, 0, P&hid1,	V0, 0, 0},
};


/* Aufbau der Parli:  
   - char[] grkz       		Gruppenkennzeichen (4 Byte ASCII),
   - struct pg  					komplette Parametergruppe,
   - char		pleng      		L�nge der Parametergruppe  
   - char		*visible			Adresse des Speichers f�r Sichbarkeitsoptionen
*/

/* Zusammenfassung der Parametergruppen zu einer Parli in dieser Reihenfolge */
const Parli Pgruppe[] = {
 {"ANL:", anl, sizeof(anl) / PGLENG, P&anl_vis},

#if NTANZ == 1
 {"FWI:", nt1, sizeof(nt1) / PGLENG, P&nt_vis[NT1]},
#endif

#if KEANZ == 1
 {"KES:", ke1, sizeof(ke1) / PGLENG, P&ke_vis[KE1]},
#endif

#if HKANZ > 1 // Nahw�rmeNetz
 {"NK1:", hk2, sizeof(hk2) / PGLENG, P&hk_vis[HK2]},	// ***AnFre
#endif

#if HKANZ > 0
 {"HKL:", hk1, sizeof(hk1) / PGLENG, P&hk_vis[HK1]},	// Lade-Heizkreis
#endif

#if HKSoLANZ > 0
 {"HKS:", hkSoL, sizeof(hkSoL) / PGLENG, P&hkSoL_vis[SO1]},
#endif

#if WWANZ > 0	// ***AnFre
 {"TWE:", ww1, sizeof(ww1) / PGLENG, P&ww_vis[WW1]},
#endif

#if SOANZ > 0		// ***AnFre
 {"SOL:", so1, sizeof(so1) / PGLENG, P&so_vis[SO1]},
 {"SOS:", so2, sizeof(so2) / PGLENG, P&so_vis[SO1]},
#endif

 {"WEI:", wei, sizeof(wei) / PGLENG, P&so_vis[SO1]},
 {"QRG:", que, sizeof(que) / PGLENG, P&so_vis[SO1]},

#if ZE8WM == 1
 {"WHZ:", ze5, sizeof(ze5) / PGLENG, P&ze_vis[5]},	// ***AnFre Kessel//SiWa ehemalig WZ1
#endif

#if ZE9WM == 1
 {"WSK:", ze6, sizeof(ze6) / PGLENG, P&ze_vis[6]},	// ***AnFre Solar // SiWa ehemalig WZ2
#endif

#if ZE10WM == 1
 {"WN1:", ze7, sizeof(ze7) / PGLENG, P&ze_vis[7]},	// ***AnFre Netz //ehemalig WZ3
#else
	#if ZE10==1
 	{"ZAE:", ze7, sizeof(ze7) / PGLENG, P&ze_vis[7]},
	#endif
#endif

// -------------- Externe Z�hler R37_2 ---------------
#if ZE21==1
 {"ZAE:", x2ze0, sizeof(x2ze0) / PGLENG, P&x2ze_vis[0]},	// ***AnFre Externer Z�hler Gas
#endif

#if DIAG == 1
 {"DIA;", dia, sizeof(dia) / PGLENG, P&dia_vis},				// Sichtbarkeit wie DIA
#endif

//-----------------------------------------------------
//#if HKANZ > 0
// {"HK1:", hk1, sizeof(hk1) / PGLENG, P&hk_vis[HK1]},
// #if ADAP_STAT_HK1 > 0
// {"AD1:", ad1, sizeof(ad1) / PGLENG, P&hk_vis[HK1]},
// #endif 
//#endif
//
//#if HKANZ > 1 
// {"HK2:", hk2, sizeof(hk2) / PGLENG, P&hk_vis[HK2]},
// #if ADAP_STAT_HK2 > 0
// {"AD2:", ad2, sizeof(ad2) / PGLENG, P&hk_vis[HK2]},
// #endif 
//#endif
//
//#if HKANZ > 2
// {"HK3:", hk3, sizeof(hk3) / PGLENG, P&hk_vis[HK3]},
// #if ADAP_STAT_HK3 > 0
// {"AD3:", ad3, sizeof(ad3) / PGLENG, P&hk_vis[HK3]},
// #endif 
//#endif
//
//#if HKANZ > 3
// {"HK4:", hk4, sizeof(hk4) / PGLENG, P&hk_vis[HK4]},
// #if ADAP_STAT_HK4 > 0
// {"AD4:", ad4, sizeof(ad4) / PGLENG, P&hk_vis[HK4]},
// #endif 
//#endif

#if GENI == 1
 {"GBP:", gbp, sizeof(gbp) / PGLENG, P&anl_vis},
 {"GEN;", gen, sizeof(gen) / PGLENG, P&tes_vis},
 {"GEC;", gec, sizeof(gec) / PGLENG, P&tes_vis},	// ToDo vis f�r Geni 
#endif

//#if WILO_MODBUS == 1
	//	{"WLP:", wlp, sizeof(wlp) / PGLENG, P&anl_vis},
//#endif

// #####ulsch : Ferienprogramm #####
#if FER == 1
 {"FER:", fer, sizeof(fer) / PGLENG, P&fer_vis},
#endif

#if QUIT_TASTE == 1	// Quittierbare Gespeicherte St�rmeldungen
 {"QSM:", qsm, sizeof(qsm) / PGLENG, P&qsm_vis},
#endif
#if MBUSANZ > 0
 {"ZMB:", zmb, sizeof(zmb) / PGLENG, P&mbus_vis},
//- {"ZMM:", zmm, sizeof(zmm) / PGLENG, P&mbus_vis},
 {"MBA;", mba, sizeof(mba) / PGLENG, P&tes_vis},
#endif

#if LEIST_BEGR == 1
 {"LBG:", lbg, sizeof(lbg) / PGLENG, P&anl_vis},
#endif				

#if HEIZGRD == 1
/***** ulsch : Heizgradtage *****/ 
 {"HGT:", hgt, sizeof(hgt) / PGLENG, P&hgt_vis}, 
#endif

#if DIAG == 1
 {"DIA;", dia, sizeof(dia) / PGLENG, P&zlt_vis},				// der Einfachheit halber Sichtbarkeit wie ZLT
#endif

#if STEUER_UNI == 1
 {"UNI:", uni, sizeof(uni) / PGLENG, P&anl_vis},
#endif

#if  ( (IMPLEMENT_S1 & GBUS1_IMPL) == GBUS1_IMPL )
 {"TS1;", us1, sizeof(us1) / PGLENG, P&zlt_vis},				// der Einfachheit halber Sichtbarkeit wie ZLT
#endif
#if  ( (IMPLEMENT_S2 & GBUS1_IMPL) == GBUS1_IMPL )
 {"TS2;", us2, sizeof(us2) / PGLENG, P&zlt_vis},				// der Einfachheit halber Sichtbarkeit wie ZLT
#endif
#if  ( (IMPLEMENT_S3 & GBUS1_IMPL) == GBUS1_IMPL )
 {"TS3;", us3, sizeof(us3) / PGLENG, P&zlt_vis},				// der Einfachheit halber Sichtbarkeit wie ZLT
#endif

#if ( ((IMPLEMENT_S1 & FUNK1_IMPL) == FUNK1_IMPL ) || ((IMPLEMENT_S2 & FUNK1_IMPL) == FUNK1_IMPL ) || ((IMPLEMENT_S3 & FUNK1_IMPL) == FUNK1_IMPL) )
 {"RFS;", rf,  sizeof(rf)  / PGLENG, P&funk_vis},
#endif

#if (ANYBUS_MODUL == 1 )
 {"ANY;", any,  sizeof(any)  / PGLENG, P&zlt_vis},
#endif

// Modbus
#if MODBUS_UNI > 0
	{"MOD;", modbusParli, sizeof(modbusParli) / PGLENG, P&sys_vis},
#endif 

//-----------------------------------------------------
	{"ALK;", alk, sizeof(alk) / PGLENG, P&syc_vis},
//WILOAF
#if WILO_MODBUS == 1
	{"WLP:", wlp, sizeof(wlp) / PGLENG, P&zlt_vis},
#endif


	{"ZLT;", zlt, sizeof(zlt) / PGLENG, P&zlt_vis},
	{"TES;", tes, sizeof(tes) / PGLENG, P&tes_vis}, 
	{"GPR;", gpr, sizeof(gpr) / PGLENG, P&tes_vis},
	{"SYS;", sys, sizeof(sys) / PGLENG, P&sys_vis} 
};
const UINT  PARLIMAX = sizeof(Pgruppe) / sizeof(Parli);



//#####ulsch: skalierbare Analogeing�nge, Beispiel
//{"*08:"," DRUCK RUECKLAUF"," bar   ", P&anaInp[U1].mwSkal,			 ANA_FORM, 2, P&vis,	V1, 0, 0},
//-	{"*08:"," DRUCK RUECKLAUF"," bar   ", P&anaInp[U1].mwSkal, 	  ANA_FORM, 0x82, P&kom,	V1, 0, 0},
//-	{" ->;"," 0V Druck RL    "," bar   ", P&AnaInpPara[U1].Skal0,		 		S_INT, 2, P&hid2,	V0, 0, 0},	
//-	{" ->;"," 10V Druck RL   "," bar   ", P&AnaInpPara[U1].Skal10,	 		S_INT, 2, P&hid2,	V0, 0, 0},
//-	{" ->;"," gl.Druck RL    "," s     ", P&AnaInpPara[U1].ZkFilt,		 US_INT, 0, P&hid2,	V0, 0, 0},
//-	{"*->;"," Druck RL       "," V     ", P&AE_UNI[U1],					  	ANA_FORMP, 2, P&hid2,	V0, 0, 0},
//-	{"*->;"," Druck RL       "," %     ", P&anaInp[U1].mwFilt,				 US_INT, 1, P&hid2,	V0, 0, 0},	
//-	{" 09;"," DRUCK RL UGW   "," bar   ", P&AnaInpPara[U1].UGW,	 		    S_INT, 2, P&hid1,	V1, 0, 0},
//-	{" 09;"," DRUCK RL OGW   "," bar   ", P&AnaInpPara[U1].OGW,	 		    S_INT, 2, P&hid1,	V1, 0, 0},
//-	{" ->;"," hysterese sm   "," bar   ", P&AnaInpPara[U1].Hyst,		 	 US_INT, 2, P&hid2,	V0, 0, 0},
//-	{"*10:"," SM DRUCK UGW ? ","       ", P&anaInp[U1].ugwSM,			JANEIN_FORM, 0, P&vis,	A1, EINZEL, 0},
//-	{"*10:"," SM DRUCK OGW ? ","       ", P&anaInp[U1].ogwSM,			JANEIN_FORM, 0, P&vis,	A1, EINZEL, 0},

