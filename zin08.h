const Pgrup ze5[] = { // IN8
	{"_**:"," WAERMEZAEHLER 1","       ", P&ZE[5],			 				ZE_FORMP, 1,	P&vis,	V0, 0, 0},
#if ZE8WM == 1
	{"*01:"," WAERMEMENGE Q1 "," kWh   ", P&wmengCtr[1].wmeng,	 US_LONG, 0,  P&vis,	V1, 0, 0},
	{"*02:"," LEISTUNG    P1 "," kW    ", P&wmengCtr[1].wmLeistg,US_INT,	0,  P&vis,	V1, 0, 0}, 
	{"*03:"," VOLUMEN     V1 ","       ", P&ZE[5],			 				ZE_FORMP, 0,  P&vis,	V0, 0, 0},
	{"*04:"," VOLUMENSTROM 1 "," m/h  ", P&wmengCtr[1].flow,		 US_LONG,	3,  P&vis,	V1, 0, 0},	// ***AnFre 23.03.2010
	{"*05;"," TEMP.VORLAUF 1 "," C    ", P&WZxTV[1],	 					ANA_FORMP, 1,  P&hid1,	V0, 0, 0},
	{" ->."," Korrektur TV1  "," K     ", P&WZxTVKorr[1],					S_INT, 	1, 	P&hid4,	V0, 0, 0},
	{"*06;"," TEMP.RUECKLAUF1"," C    ", P&WZxTR[1],	 					ANA_FORM, 1,  P&vis,	V0, 0, 0},
	{" ->."," Korrektur TR1  "," K     ", P&WZxTRKorr[1],					S_INT, 	1, 	P&hid4,	V0, 0, 0},
//	{"*08;"," AKT.MON.VOLUM. ","       ", P&ZE[5],							ZE_FORMP, 5,  P&hid1,	V0, 0, 0},

	{"*10:"," JANUAR         "," kWh   ", P&wmengCtr[1].verbr[0],						US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*11:"," FEBRUAR        "," kWh   ", P&wmengCtr[1].verbr[1],				  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*12:"," MAERZ          "," kWh   ", P&wmengCtr[1].verbr[2],				  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*13:"," APRIL          "," kWh   ", P&wmengCtr[1].verbr[3],				  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*14:"," MAI            "," kWh   ", P&wmengCtr[1].verbr[4],				  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*15:"," JUNI           "," kWh   ", P&wmengCtr[1].verbr[5],				  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*16:"," JULI           "," kWh   ", P&wmengCtr[1].verbr[6],				  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*17:"," AUGUST         "," kWh   ", P&wmengCtr[1].verbr[7],				  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*18:"," SEPTEMBER      "," kWh   ", P&wmengCtr[1].verbr[8],				  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*19:"," OKTOBER        "," kWh   ", P&wmengCtr[1].verbr[9],				  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*20:"," NOVEMBER       "," kWh   ", P&wmengCtr[1].verbr[10],			  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*21:"," DEZEMBER       "," kWh   ", P&wmengCtr[1].verbr[11],			  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*22:"," VORJAHR JANUAR "," kWh   ", P&wmengCtr[1].verbr_vj[0],		  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*23:"," VORJAHR FEBRUAR"," kWh   ", P&wmengCtr[1].verbr_vj[1],		  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*24:"," VORJAHR MAERZ  "," kWh   ", P&wmengCtr[1].verbr_vj[2],		  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*25:"," VORJAHR APRIL  "," kWh   ", P&wmengCtr[1].verbr_vj[3],		  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*26:"," VORJAHR MAI    "," kWh   ", P&wmengCtr[1].verbr_vj[4],		  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*27:"," VORJAHR JUNI   "," kWh   ", P&wmengCtr[1].verbr_vj[5],		  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*28:"," VORJAHR JULI   "," kWh   ", P&wmengCtr[1].verbr_vj[6],		  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*29:"," VORJAHR AUGUST "," kWh   ", P&wmengCtr[1].verbr_vj[7],		  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*30:"," VORJAHR SEPT.  "," kWh   ", P&wmengCtr[1].verbr_vj[8],		  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*31:"," VORJAHR OKTOBER"," kWh   ", P&wmengCtr[1].verbr_vj[9],		  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*32:"," VORJAHR NOVEMB."," kWh   ", P&wmengCtr[1].verbr_vj[10],		  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{"*33:"," VORJAHR DEZEMB."," kWh   ", P&wmengCtr[1].verbr_vj[11],		  	US_LONG, 	0, P&vis,  V1, 0 ,0},
	{" 34."," SYNC.WAERMEMENG"," kWh   ", P&wmengCtr[1].wmeng,							US_LONG,	0, P&hid3, V0, 0, 0},
	{" ->."," SYNC.JAN       "," kWh   ", P&wmengCtr[1].verbr[0],						US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.FEB       "," kWh   ", P&wmengCtr[1].verbr[1],				  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.MRZ       "," kWh   ", P&wmengCtr[1].verbr[2],				  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.APR       "," kWh   ", P&wmengCtr[1].verbr[3],				  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.MAI       "," kWh   ", P&wmengCtr[1].verbr[4],				  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.JUN       "," kWh   ", P&wmengCtr[1].verbr[5],				  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.JUL       "," kWh   ", P&wmengCtr[1].verbr[6],				  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.AUG       "," kWh   ", P&wmengCtr[1].verbr[7],				  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.SEP       "," kWh   ", P&wmengCtr[1].verbr[8],				  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.OKT       "," kWh   ", P&wmengCtr[1].verbr[9],				  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.NOV       "," kWh   ", P&wmengCtr[1].verbr[10],			  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.DEZ       "," kWh   ", P&wmengCtr[1].verbr[11],			  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.VORJ.JAN  "," kWh   ", P&wmengCtr[1].verbr_vj[0],		  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.VORJ.FEB  "," kWh   ", P&wmengCtr[1].verbr_vj[1],		  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.VORJ.MRZ  "," kWh   ", P&wmengCtr[1].verbr_vj[2],		  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.VORJ.APR  "," kWh   ", P&wmengCtr[1].verbr_vj[3],		  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.VORJ.MAI  "," kWh   ", P&wmengCtr[1].verbr_vj[4],		  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.VORJ.JUN  "," kWh   ", P&wmengCtr[1].verbr_vj[5],		  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.VORJ.JUL  "," kWh   ", P&wmengCtr[1].verbr_vj[6],		  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.VORJ.AUG  "," kWh   ", P&wmengCtr[1].verbr_vj[7],		  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.VORJ.SEP  "," kWh   ", P&wmengCtr[1].verbr_vj[8],		  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.VORJ.OKT  "," kWh   ", P&wmengCtr[1].verbr_vj[9],		  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.VORJ.NOV  "," kWh   ", P&wmengCtr[1].verbr_vj[10],		  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" ->."," SYNC.VORJ.DEZ  "," kWh   ", P&wmengCtr[1].verbr_vj[11],		  	US_LONG, 	0, P&hid3, V0, 0 ,0},
	{" 35."," WMZ SYNCHRONIS."," JA=1  ", P&wmengCtr[1].syncFlag,						US_CHAR,	0, P&hid3, V0, 0, 0},   
	{" 39."," SYNC. VOLUMEN  ","       ", P&ZE[5],													ZE_FORMP, 6, P&hid3, V0, 0, 0},		// ***AnFre statt Nr. 85:
	
	{" 45;"," MAX LOESCHEN   "," JA=1  ", P&wmengCtr[1].resMax,							US_CHAR,	0, P&hid1, V0, 0, 0},    
//	{"*46:"," VOLUMENSTROM   "," m/h  ", P&wmengCtr[1].flow,								US_LONG,	1, P&vis,	 V1, 0, 0},
//	{"*47:"," LEISTUNG       "," kW    ", P&wmengCtr[1].wmLeistg,						US_INT,		0, P&vis,	 V1, 0, 0}, 
	{"*48;"," VOLUMENSTR.MAX "," m/h  ", P&wmengCtr[1].flow_max,						US_LONG,	3, P&hid1, V0, 0, 0},		// ***AnFre 23.03.2010 
	{"*49;"," LEISTUNG MAX   "," kW    ", P&wmengCtr[1].wmLeistg_max,				US_INT,		0, P&hid1, V0, 0, 0},
 
	#if LEIST_BER_ZE8 == 1
	{" 50;"," LEISTG.MITTELN "," min   ", P&MaxLeistung[1].MittelnLeistg, 	US_CHAR,	0, P&hid1, V0, 0, 0}, 
	{"*51;"," LEISTG.MITTEL  "," kW    ", P&MaxLeistung[1].mittel,					US_INT,		0, P&hid1, V0, 0, 0}, 
	{"*52;"," LEI.MITTEL MAX "," kW    ", P&MaxLeistung[1].mittelMax,				US_INT,		0, P&hid1, V0, 0, 0},
	{"*53;"," DAT.LEI.MI.MAX ","       ", P&MaxLeistung[1].tag, 		 				DATE_FORM,1, P&hid1, V0, 0, 0},
	{"*54;"," ZEIT LEI.MI.MAX"," h:min ", P&MaxLeistung[1].zeit,		 				ZEIT_FORM,0, P&hid1, V0, 0, 0},
	{"*55;"," Ta LEI.MI.MAX  "," C    ", P&MaxLeistung[1].ta,							ANA_FORM, 1, P&hid1, V0, 0, 0},
//	{"*56."," VL LEI.MI.MAX  "," C    ", P&MaxLeistung[1].vl,							ANA_FORM, 1, P&hid1, V1, 0, 0},
//	{"*57."," RL LEI.MI.MAX  "," C    ", P&MaxLeistung[1].rl,							ANA_FORM, 1, P&hid1, V1, 0, 0},
//	{"*58."," VSTR.LEI.MI.MAX"," m/h  ", P&MaxLeistung[1].flow,						US_LONG,	3, P&hid1, V1, 0, 0},	// ***AnFre 23.03.2010
	#endif
	{" 90;"," KOMMASTELLEN   ","       ", P&ZE[5],							ZE_FORMP, 2,  P&hid1,	V0, 0, 0},
	{" 91;"," DIMENSION      ","       ", P&ZE[5],							ZE_FORMP, 3,  P&hid1,	V0, 0, 0},
	{" 92;"," TEILERFAKTOR   ","       ", P&ZE[5],							ZE_FORMP, 4,  P&hid1,	V0, 0, 0},
	{" 93;"," IMPULSWERT     ","       ", P&ZE[5],							ZE_FORMP, 39, P&hid1,	V0, 0, 0},
	{" ->."," Exponent       ","       ", P&ZE[5],							ZE_FORMP, 36, P&hid2,	V0, 0, 0},
	{" 99."," Zwischenzaehler","       ", P&ZE[5],							ZE_FORMP, 8,  P&hid2,	V0, 0, 0},

	{" ->."," Vol.letzter Imp"," l     ", P&wmengCtr[1].volumen,						US_INT,	  0, P&hid2, V0, 0, 0},
	{" ->."," Zeit seit Imp. "," 200ms ", P&wmengCtr[1].zeitdiff,						US_INT,	  0, P&hid2, V0, 0, 0},
	{" ->."," Zeit letzt.Imp."," 200ms ", P&wmengCtr[1].zeitdiffZuletzt,		US_INT,	  0, P&hid2, V0, 0, 0},
// ***AnFre

#endif
 
};
