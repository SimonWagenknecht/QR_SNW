/*------------------------------ Weichen-Regelung------------ ----------------------------*/
const Pgrup wei[] = {
	{"***:","Quellenregenerat","       ", P&Weimod,							ASCII_FORM, 0, P&vis,		V0, 0, 0},
//{"*01:"," KOLLEKTOR   TS1"," C    ", P&TS1_[0],						 ANA_FORMP, 1, P&vis,		V1, 0, 0},	
//{"*01:"," KOLLEKTOR   TS1"," C    ", P&TS1_[0],					ANA_FORMP, 0x81, P&kom,		E1, FUEHLER, 0},

	{"*01:"," Taupunkt     F "," C    ", P&anaInp[U5].mwSkal,			 ANA_FORM, 1, P&vis,	V1, 0 , 0},
	{"*01:"," Taupunkt     F "," C    ", P&anaInp[U5].mwSkal, 	  ANA_FORM, 0x81, P&kom,	V1, 0 , 0},
	{" ->."," Taup.    0 Volt"," C    ", P&AnaInpPara[U5].Skal0,		 		S_INT, 1, P&hid2,	V0, 0 , 0},	
	{" ->."," Taup.   10 Volt"," C    ", P&AnaInpPara[U5].Skal10,			S_INT, 1, P&hid2,	V0, 0 , 0},	
	{" ->."," Filterzeit     "," s     ", P&AnaInpPara[U5].ZkFilt,		 US_INT, 0, P&hid2,	V0, 0 , 0},

	{"*02:"," RL-SOLAR    TS6"," C    ", P&TS5_[0],						 ANA_FORMP, 1, P&vis,		V0, 0, 0},
	{"*02:"," RL-SOLAR    TS6"," C    ", P&TS5_[0],					ANA_FORMP, 0x81, P&kom,		V0, FUEHLER, 0},
	
	{"*20:"," VORLAUF BERECHN"," C    ", P&wed[0].tvsb,					US_INT, 1, P&vis,		V1, 0, 0},

	{" 30;"," FUNKTION TP    "," EIN=1 ", P&wes[0].ipa_Funktion_TP,				 US_CHAR, 0, P&hid1,	V0, 0, 0},
	{"*31:"," Taupunkt-Alarm ","       ", P&wed[0].chbz_Taupunktschutz,		 	JANEIN_FORM, 0, P&vis,		E1, EREIGNIS, 0},
	{" ->;"," dT-Taup.grenze "," K     ", P&wes[0].ipa_Taupunktgrenze,		 	US_INT, 1, P&vis,		V0, 0, 0},
	{"*32:"," eTank-Max-Alarm","       ", P&wed[0].chbz_eTankschutz,		 	JANEIN_FORM, 0, P&vis,		E1, EREIGNIS, 0},
	{" ->;"," eTank-Maximum  "," C    ", P&wes[0].ipa_eTankgrenze,		 	US_INT, 1, P&vis,		V0, 0, 0},
	{" ->;"," eTank-aktivDau."," min   ", P&wes[0].ipa_eTank_Minlaufzeit,		 	US_INT, 0, P&hid1,		V0, 0, 0},
	{" ->;"," Counter Zeitakt"," s     ", P&wed[0].iCo_QRG,							 	US_INT, 0, P&hid1,		V0, 0, 0},
	{"*->;"," TRQ_saved      "," C    ", P&wed[0].TQRL_recent,					 S_INT, 1, P&hid1,	V0, 0, 0},
	{"*33:"," Niedere Regene.","       ", P&wed[0].chbz_Nieder_QRG,	 JANEIN_FORM, 0, P&vis,		V1, 0, 0},
	{" ->;"," dT-TS5-TRQ     "," K     ", P&wes[0].ipa_Nieder_QRG_ein,		 	US_INT, 1, P&vis,		V0, 0, 0},
	{"*34:"," Hohe Regene.   ","       ", P&wed[0].chbz_Hoch_QRG,	 JANEIN_FORM, 0, P&vis,		V1, 0, 0},
	{" ->;"," dT-TS3-TRH EIN "," K     ", P&wes[0].ipa_Hoch_QRG_ein,		 	US_INT, 1, P&vis,		V0, 0, 0},
	{" ->;"," dT-TS3-TRH AUS "," K     ", P&wes[0].ipa_Hoch_QRG_aus,		 	US_INT, 1, P&vis,		V0, 0, 0},
	{"*35:"," WPU-Betrieb    ","       ", P&qud[0].chbz_WPU_Versorgung,	 JANEIN_FORM, 0, P&vis,		V1, 0, 0},
	{"*->;"," WPU ANFORDERUNG","       ", P&qud[0].chbz_Freigabe_wpu,	 JANEIN_FORM, 0, P&vis,		V0, 0, 0},
	{"*->;"," WPU BM         ","       ", P&qud[0].chbm_WPU,	 JANEIN_FORM, 0, P&vis,		V0, 0, 0},
	{"*->;"," DM Fehler      ","       ", P&qud[0].chz_DM_Fehler,	 JANEIN_FORM, 0, P&vis,		V0, 0, 0},
	{"*36:"," Quellenanhebung","       ", P&wed[0].chbz_Quellenanhebung,	 JANEIN_FORM, 0, P&vis,		V1, 0, 0},

	{"*70:"," PU WEI  EIN ?  ","       ", P&DA_UNI[U3], 				 JANEIN_FORMOP, 0, P&vis,		V1, 0, 0},
	{"*71:"," BM PU WEI EIN ?","       ", P&BM_UNI[U2],	JANEIN_FORMOP, 0, P&vis,	V1, 0, 0},
//
 	{" 80;"," P-VERSTAERKUNG "," %/K   ", P&wes[0].Kp,						US_INT, 2, P&hid1,	V0, 0, 0},
	{" 81;"," D-VERSTAERKUNG ","       ", P&wes[0].Kd,						US_INT, 2, P&hid1,	V0, 0, 0},
	{" 82;"," TASTZEIT       "," s     ", P&wes[0].Ts,						US_INT, 1, P&hid1,	V0, 0, 0},
	{" 83;"," NACHSTELLZEIT  "," s     ", P&wes[0].Tn,						US_INT, 1, P&hid1,	V0, 0, 0},
	
	{" 84;"," VENTILSTELL.MIN"," %     ", P&wes[0].Y_rel_min,	 		US_INT, 1, P&hid1,	V0, 0, 0},
	{" 85;"," OEFFNUNGSBEGINN"," %     ", P&wes[0].Y_rel_beg,	 		US_INT, 1, P&hid1,	V0, 0, 0},
	
	{"*86;"," SOLLWERT       "," C    ", P&wed[0].tsol,					US_INT, 1, P&hid1,	V1, 0, 0},
	{"*87;"," REGELABWEICHUNG"," K     ", P&wed[0].ei,						 S_INT, 1, P&hid1,	V0, 0, 0},
	{"*->;"," dy_rel         ","       ", P&wed[0].dy_rel,				 S_INT, 3, P&hid2,	V0, 0, 0},
 
 	{"*88:"," VENTILSTELLUNG "," %     ", P&AA_UNI[U5],					AOUT_FORMP, 1, P&vis,	V1, 0, 0},

	{"*90:"," HANDBE PU WEI ?","       ", P&wes[0].chpa_pu_Hau,		  JANEIN_FORM, 0, P&vis,	E1, EREIGNIS, 0},
	{"*91:"," HANDBE RV WEI ?","       ", P&wes[0].chpa_rv_Hau,		  JANEIN_FORM, 0, P&vis,	E1, EREIGNIS, 0},
	 
	{" 92;"," HAND PU WEI    "," HAND=1", P&wes[0].chpa_pu_Hau,				 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" ->;"," PU WEI  EIN/AUS"," EIN=1 ", P&wes[0].chpa_pu_ein,			 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" 93;"," HAND RV WEI    "," HAND=1", P&wes[0].chpa_rv_Hau,				 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" ->;"," RV WEI stellen "," %     ", P&wes[0].ipa_rv_stellung,			 US_INT, 1, P&hid1,	V1, 0, 0},
};
	
/*------------------------------ Quellen-Regelung------------ ----------------------------*/	
const Pgrup que[] = {
{"***:","Quellenregenerat","       ", P&Quemod,							ASCII_FORM, 0, P&vis,		V0, 0, 0},
{"*01:"," Vorlauf   TVQU "," C    ", P&TP_UNI[U2],						 ANA_FORMP, 1, P&vis,		V1, 0, 0},	
{"*01:"," Vorlauf   TVQU "," C    ", P&TP_UNI[U2],					ANA_FORMP, 0x81, P&kom,		E1, FUEHLER, 0},
{"*02:"," Ruecklauf TRQU "," C    ", P&TP_UNI[U3],						 ANA_FORMP, 1, P&vis,		V1, 0, 0},	
{"*02:"," Ruecklauf TRQU "," C    ", P&TP_UNI[U3],					ANA_FORMP, 0x81, P&kom,		E1, FUEHLER, 0},

{"*03:"," DRUCK QRG   PQ "," bar   ", P&anaInp[U6].mwSkal,			 ANA_FORM, 1, P&vis,	V1, 0 , 0},
{"*03:"," DRUCK QRG   PQ "," bar   ", P&anaInp[U6].mwSkal, 	  ANA_FORM, 0x81, P&kom,	V1, 0 , 0},
{" ->."," Druck  0 Volt  "," bar   ", P&AnaInpPara[U6].Skal0,		 		S_INT, 1, P&hid2,	V0, 0 , 0},	
{" ->."," Druck 10 Volt  "," bar   ", P&AnaInpPara[U6].Skal10,			S_INT, 1, P&hid2,	V0, 0 , 0},	
{" ->."," Filterzeit     "," s     ", P&AnaInpPara[U6].ZkFilt,		 US_INT, 0, P&hid2,	V0, 0 , 0},

	{"*20:"," VORLAUF BERECHN"," C    ", P&qud[0].tvsb,					US_INT, 1, P&vis,		V1, 0, 0},


	{"*31:"," Taupunkt-Alarm ","       ", P&wed[0].chbz_Taupunktschutz,		 	JANEIN_FORM, 0, P&vis,		V0, EREIGNIS, 0},
	{"*32:"," eTank-Max-Alarm","       ", P&wed[0].chbz_eTankschutz,		 	JANEIN_FORM, 0, P&vis,		V0, EREIGNIS, 0},
	{"*33:"," Niedere Regene.","       ", P&wed[0].chbz_Nieder_QRG,	 JANEIN_FORM, 0, P&vis,		V0, 0, 0},
	{"*34:"," Hohe Regene.   ","       ", P&wed[0].chbz_Hoch_QRG,	 JANEIN_FORM, 0, P&vis,		V0, 0, 0},
	{"*35:"," WPU-Betrieb    ","       ", P&qud[0].chbz_WPU_Versorgung,	 JANEIN_FORM, 0, P&vis,		V0, 0, 0},
	{" ->;"," WPU-QU-Grenze  "," C    ", P&qus[0].ipa_Sollwert_WPU_VL,		 	US_INT, 1, P&vis,		V0, 0, 0},
	{"*->;"," WPU-FREIGABE   ","       ", P&qud[0].chbz_Freigabe_wpu,	 JANEIN_FORM, 0, P&vis,		V0, 0, 0},
	{"*->;"," WPU BM         ","       ", P&qud[0].chbm_WPU,	 JANEIN_FORM, 0, P&vis,		V0, 0, 0},
	{"*->;"," DM Fehler      ","       ", P&qud[0].chz_DM_Fehler,	 JANEIN_FORM, 0, P&vis,		V0, 0, 0},
	{"*36:"," Quellenanhebung","       ", P&wed[0].chbz_Quellenanhebung,	 JANEIN_FORM, 0, P&vis,		V0, 0, 0},


	{"*70:"," PU QU   EIN ?  ","       ", P&DA_UNI[U2], 				 JANEIN_FORMOP, 0, P&vis,		V1, 0, 0},
	{"*71:"," BM PU QU  EIN ?","       ", P&BM_UNI[U1],	JANEIN_FORMOP, 0, P&vis,	V1, 0, 0},
//
  {" 80;"," P-VERSTAERKUNG "," %/K   ", P&qus[0].Kp,						US_INT, 2, P&hid1,	V0, 0, 0},
	{" 81;"," D-VERSTAERKUNG ","       ", P&qus[0].Kd,						US_INT, 2, P&hid1,	V0, 0, 0},
	{" 82;"," TASTZEIT       "," s     ", P&qus[0].Ts,						US_INT, 1, P&hid1,	V0, 0, 0},
	{" 83;"," NACHSTELLZEIT  "," s     ", P&qus[0].Tn,						US_INT, 1, P&hid1,	V0, 0, 0},
	
	{" 84;"," VENTILSTELL.MIN"," %     ", P&qus[0].Y_rel_min,	 		US_INT, 1, P&hid1,	V0, 0, 0},
	{" 85;"," OEFFNUNGSBEGINN"," %     ", P&qus[0].Y_rel_beg,	 		US_INT, 1, P&hid1,	V0, 0, 0},
	
	{"*86;"," SOLLWERT       "," C    ", P&qud[0].tsol,					US_INT, 1, P&hid1,	V1, 0, 0},
	{"*87;"," REGELABWEICHUNG"," K     ", P&qud[0].ei,						 S_INT, 1, P&hid1,	V0, 0, 0},
	{"*->;"," dy_rel         ","       ", P&qud[0].dy_rel,				 S_INT, 3, P&hid2,	V0, 0, 0},
 
 	{"*88:"," VENTILSTELLUNG "," %     ", P&AA_UNI[U6],					AOUT_FORMP, 1, P&vis,	V1, 0, 0},
 
 	{"*90:"," HANDBE PU QU ? ","       ", P&qus[0].chpa_pu_Hau,		  JANEIN_FORM, 0, P&vis,	E1, EREIGNIS, 0},
	{"*91:"," HANDBE RV QU ? ","       ", P&qus[0].chpa_rv_Hau,		  JANEIN_FORM, 0, P&vis,	E1, EREIGNIS, 0},

	{" 92;"," HAND PU QU     "," HAND=1", P&qus[0].chpa_pu_Hau,				 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" ->;"," PU QU   EIN/AUS"," EIN=1 ", P&qus[0].chpa_pu_ein,			 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" 93;"," HAND RV QU     "," HAND=1", P&qus[0].chpa_rv_Hau,				 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" ->;"," RV QU  stellen "," %     ", P&qus[0].ipa_rv_stellung,			 US_INT, 1, P&hid1,	V1, 0, 0},

};
