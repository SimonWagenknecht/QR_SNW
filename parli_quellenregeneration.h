/*------------------------------ Weichen-Regelung------------ ----------------------------*/
const Pgrup wei[] = {
	{"***:","Quellenregenerat","       ", P&Weimod,							ASCII_FORM, 0, P&vis,		V0, 0, 0},
//{"*01:"," KOLLEKTOR   TS1"," C    ", P&TS1_[0],						 ANA_FORMP, 1, P&vis,		V1, 0, 0},	
//{"*01:"," KOLLEKTOR   TS1"," C    ", P&TS1_[0],					ANA_FORMP, 0x81, P&kom,		E1, FUEHLER, 0},


	{"*->:"," BM PU WEI EIN ?","       ", P&DE_UNI[U2],	JANEIN_FORMOP, 0, P&vis,	V1, 0, 0},

	{"*88:"," HANDBE PU WEI ?","       ", P&wes[0].chpa_puwei_Hau,		  JANEIN_FORM, 0, P&vis,	E1, EREIGNIS, 0},
	{"*89:"," HANDBE RV WEI ?","       ", P&wes[0].chpa_rvwei_Hau,		  JANEIN_FORM, 0, P&vis,	E1, EREIGNIS, 0},
//
 
	{" 98;"," HAND PU WEI    "," HAND=1", P&wes[0].chpa_puwei_Hau,				 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" ->;"," PU WEI  EIN/AUS"," EIN=1 ", P&wes[0].chpa_puwei_ein,			 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" 98;"," HAND RV WEI    "," HAND=1", P&wes[0].chpa_rvwei_Hau,				 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" ->;"," RV WEI stellen "," %     ", P&wes[0].ipa_rvwei_stellung,			 US_INT, 1, P&hid1,	V1, 0, 0},
};
	
/*------------------------------ Quellen-Regelung------------ ----------------------------*/	
const Pgrup que[] = {
{"***:","Quellenregenerat","       ", P&Quemod,							ASCII_FORM, 0, P&vis,		V0, 0, 0},
{"*01:"," Vorlauf   TVQU "," C    ", P&TP_UNI[U2],						 ANA_FORMP, 1, P&vis,		V1, 0, 0},	
{"*01:"," Vorlauf   TVQU "," C    ", P&TP_UNI[U2],					ANA_FORMP, 0x81, P&kom,		E1, FUEHLER, 0},
{"*02:"," Ruecklauf TRQU "," C    ", P&TP_UNI[U3],						 ANA_FORMP, 1, P&vis,		V1, 0, 0},	
{"*02:"," Ruecklauf TRQU "," C    ", P&TP_UNI[U3],					ANA_FORMP, 0x81, P&kom,		E1, FUEHLER, 0},

{"*04:"," Taupunkt     F "," C    ", P&anaInp[U5].mwSkal,			 ANA_FORM, 1, P&vis,	V1, 0 , 0},
{"*04:"," Taupunkt     F "," C    ", P&anaInp[U5].mwSkal, 	  ANA_FORM, 0x81, P&kom,	V1, 0 , 0},
{" ->."," Taup.    0 Volt"," C    ", P&AnaInpPara[U5].Skal0,		 		S_INT, 1, P&hid2,	V0, 0 , 0},	
{" ->."," Taup.   10 Volt"," C    ", P&AnaInpPara[U5].Skal10,			S_INT, 1, P&hid2,	V0, 0 , 0},	
{" ->."," Filterzeit     "," s     ", P&AnaInpPara[U5].ZkFilt,		 US_INT, 0, P&hid2,	V0, 0 , 0},

{"*04:"," DRUCK QRG   PQ "," bar   ", P&anaInp[U6].mwSkal,			 ANA_FORM, 1, P&vis,	V1, 0 , 0},
{"*04:"," DRUCK QRG   PQ "," bar   ", P&anaInp[U6].mwSkal, 	  ANA_FORM, 0x81, P&kom,	V1, 0 , 0},
{" ->."," Druck  0 Volt  "," bar   ", P&AnaInpPara[U6].Skal0,		 		S_INT, 1, P&hid2,	V0, 0 , 0},	
{" ->."," Druck 10 Volt  "," bar   ", P&AnaInpPara[U6].Skal10,			S_INT, 1, P&hid2,	V0, 0 , 0},	
{" ->."," Filterzeit     "," s     ", P&AnaInpPara[U6].ZkFilt,		 US_INT, 0, P&hid2,	V0, 0 , 0},

	{"*->:"," BM PU QU  EIN ?","       ", P&DE_UNI[U1],	JANEIN_FORMOP, 0, P&vis,	V1, 0, 0},

	{"*88:"," HANDBE PU QU ? ","       ", P&qus[0].chpa_puqu_Hau,		  JANEIN_FORM, 0, P&vis,	E1, EREIGNIS, 0},
	{"*89:"," HANDBE RV QU ? ","       ", P&qus[0].chpa_rvqu_Hau,		  JANEIN_FORM, 0, P&vis,	E1, EREIGNIS, 0},
//
 
	{" 98;"," HAND PU QU     "," HAND=1", P&qus[0].chpa_puqu_Hau,				 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" ->;"," PU QU   EIN/AUS"," EIN=1 ", P&qus[0].chpa_puqu_ein,			 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" 98;"," HAND RV QU     "," HAND=1", P&qus[0].chpa_rvqu_Hau,				 US_CHAR, 0, P&hid1,	V1, 0, 0},
	{" ->;"," RV QU  stellen "," %     ", P&qus[0].ipa_rvqu_stellung,			 US_INT, 1, P&hid1,	V1, 0, 0},

};
