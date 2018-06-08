/*		Task:	RegelHk			*/

//#####ulsch: 25.02.05 bei Bedarfsabsenkung und kein Frostschutz : hk_abschalten

#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "ustruct.h"
#include "defins.h"
#include "sramext.h"
#include "uramext.h"
#include "uconstext.h"
#include "unoinitext.h"

// Unterprogramme
char  tvsoll_ber(char hk);
void  raum_kaskade(char hk, char ada);
void  rueckl_begr(char hk, char ps);
char  test_aufhe(char hk);
char TestEstrichProg ( char hk );
char RaumAbschaltung	( char hk );

/*---------------------- Task RegelHk -----------------------------------*/
// Gemeinsamer Code f�r bis zu 4 alternierende Regelkreise
// Zeitbasis f�r einen Regelkreis : 1,0 Sekunden
// Zeitbasis f�r den Taskaufruf:		1,0 Sekunden / HKMAX

void RegelHk(void)
{
	static char hk = HKMAX;
	
	float fl_ei = 0;
	float fl_dy_rel = 0;	
	float fl_Y_rel_beg = 0;
	float fl_Y_rel_min = 0;
	char  hkAbschalten = 0;
	char	tvret;
	char hkAbsch;

	int	x1, x2, y;		//f�r Skalierung der Sollwert-Ausgabe 0...10Volt
	// Dynamische Ventilstellung Min ***AnFre 06.06.2012
	int	tvPrim =0;		// Prim�rVorlauf zuweisen HK1 oder HK2
	int korrRL =0;		// korrigierte R�cklauf-Temp.	
	char	externeAnforderung1Aktiv = 0;
	char	externeAnforderung2Aktiv = 0;
		
	// Lokale Pointer auf Hk-Strukturen
	HkDynam    *pHkd;	
	HkStandard *pHks;

	if(++hk >= HKMAX)										// Regelkreis-Index erh�hen
		hk = 0;
	
	// Projektabfrage, ob Regelkreis aktiv
	if(Projekte[proj_typ].hkcode[hk] == 0)
		return;													// Heizkreis nicht aktiv
	
	// Strukturpointer zuweisen
	pHkd = &hkd[hk];	
	pHks = &hks[hk];

	//--------------------------------------------------------------------------
	// Betriebsart, Absenkanzeige
	//--------------------------------------------------------------------------
	if(pHkd->absenSchalter == 1)							
	{	// Schalterabsenkung
		pHkd->regie  = REG_SCHALTER;
		pHkd->absen  = pHkd->absenSchalter ;			// Zustand  Absenkphase
		pHkd->aufhe  = 0 ;												// Zustand  Aufheizphase
		pHkd->absch  = pHkd->abschSchalter ;			// Zustand	Abschaltphase
		pHkd->hunt   = 0;													// Zustand  Heizunterbrechung
		pHkd->stuetz = pHkd->stuetzSchalter;			// Zustand 	St�tzbetrieb
		pHkd->frost  = pHkd->frostSchalter ;			// Zustand	Frostschutzbetrieb
	}
	else if(pHkd->vorra_bed == TRUE)						// bei Vorrang Bedarfsabsenkung vor Zeitabsenkung
	{	// Bedarfsabsenkung
		pHkd->regie  = REG_BEDARF;
		pHkd->absen  = abs_bed[hk].absen ;				// Zustand  Absenkphase
		pHkd->aufhe  = abs_bed[hk].aufhe ;				// Zustand  Aufheizphase
		pHkd->absch  = abs_bed[hk].absch ;				// Zustand	Abschaltphase
		pHkd->hunt   = abs_bed[hk].hunt  ;				// Zustand  Heizunterbrechung
		pHkd->stuetz = abs_bed[hk].stuetz;				// Zustand 	St�tzbetrieb
		pHkd->frost  = abs_bed[hk].frost ;				// Zustand	Frostschutzbetrieb
	}
	else	// Zeitabsenkung
	{
		if(pHkd->absenFerien == 1)								// Ferienbetrieb
		{
			pHkd->regie  = REG_FERIEN;
			pHkd->absen  = pHkd->absenFerien ;			// Zustand  Absenkphase
			pHkd->aufhe  = 0 ;											// Zustand  Aufheizphase
			pHkd->absch  = pHkd->abschFerien ;			// Zustand	Abschaltphase
			pHkd->hunt   = 0;												// Zustand  Heizunterbrechung
			pHkd->stuetz = pHkd->stuetzFerien;			// Zustand 	St�tzbetrieb
			pHkd->frost  = pHkd->frostFerien ;			// Zustand	Frostschutzbetrieb
		}
		else																			// Normal Zeitabsenkung
		{		
			pHkd->regie  = REG_ZEIT;
			pHkd->absen  = abs_ram[hk].absen ;			// Zustand  Absenkphase
			pHkd->aufhe  = abs_ram[hk].aufhe ;			// Zustand  Aufheizphase
			pHkd->absch  = abs_ram[hk].absch ;			// Zustand	Abschaltphase
			pHkd->hunt   = abs_ram[hk].hunt  ;			// Zustand  Heizunterbrechung
			pHkd->stuetz = abs_ram[hk].stuetz;			// Zustand 	St�tzbetrieb
			pHkd->frost  = abs_ram[hk].frost ;			// Zustand	Frostschutzbetrieb
		}	
	}				
	switch(pHkd->regie)
	{
		case REG_SCHALTER:
			memcpy(pHkd->regie_txt, TXT_SCHALTER, 15);
			break;
		case REG_BEDARF:
			memcpy(pHkd->regie_txt, TXT_BEDARF, 15);
			break;
		case REG_FERIEN:
			memcpy(pHkd->regie_txt, TXT_FERIEN, 15);
			break;
		case REG_ZEIT:
			memcpy(pHkd->regie_txt, TXT_ZEIT, 15);
			break;
		default:
			memcpy(pHkd->regie_txt, TXT_DEFAULT, 15);
			break;
	}		
				


	//--------------------------------------------------------------------------
	// Abfrage Handbetrieb
	//--------------------------------------------------------------------------
	if(pHks->Haut == TRUE)			
	{	
		RZU[hk]->wert = pHkd->vzu;								// Handwert[s] f�r Zufahren ausgeben
		if(pHkd->vzu > 0)													// Ausgabe aktiv ?
		{	 pHkd->vzu -= 1;												// Zeit decrementieren
			 pHkd->vauf = 0;												// Vorrang vor Auffahren 
		}                               					
		else																			// Ausgabe f�r Zufahren nicht aktiv
		{	RAUF[hk]->wert = pHkd->vauf;						// Handwert[s] f�r Auffahren ausgeben
			if(pHkd->vauf > 0)											// Ausgabe aktiv ?
				 pHkd->vauf -= 1;											// Zeit decrementieren
		}                               					
		RVENT[hk]->awert = pHks->Vstell;								// Analogventil 0-100,0% 
		hkd[hk].fl_y_rel = (float)pHks->Vstell / 10;

		if(pHkd->vzu > 0 || pHkd->vauf > 0)				// return, solange Ausgabe l�uft (wegen 1 Sekunden Takt) 
			return;
	}                                 					
	else																				// Automatikbetrieb
	{	pHks->Haut = 0;														// evtl. Fehleingaben l�schen
		pHkd->vzu	= 0;														// Handwerte l�schen
		pHkd->vauf	= 0;
	}
	//----------------------------------------------------------------------------
	
	// Regler-Tastzeit
	if(++pHkd->zts < pHks->Ts/10)
		 return;																	// Tastzeit noch nicht erreicht
	pHkd->zts = 0;	 

/* ***************** Sollwert-Berechnung nur f�r Nahw�rmeNetz HKN: *********************** */
 if(hk == HK2 )
 {
	// Sommer/Winter-Automatik
	//-----------------------------------------------------------------------------
	// Entscheidung: zentrale Werte aus ANL oder Extrawerte aus HK
	if(pHks->SoWiExtra == 0)
	{	// zentrale Werte auf Heizkreis kopieren
		pHks->Tae  = Tae;
		pHks->Taa  = Taa;
		pHkd->sowi = sowi;
	}
	else
	{	// Extrawerte f�r den Heizkreis ausgew�hlt
		if(ta1mh.messw <= pHks->Tae) 							// ta1mh <= Winter-Ein-Temp. ?
			pHkd->sowi = 0;													// Winterbetrieb
		else if(ta1mh.messw >= pHks->Taa)					// ta1mh >= Sommer-Ein-Temp. ?
			pHkd->sowi = 1;													// Sommerbetrieb
	}		

	pHkd->somme = pHks->Swhk;										// Sommer/Winter-Automatik nach Statusanzeige		
	if(pHks->Swhk > 0)													// Automatik aktiv ?
	{	
		// Au�entemperatur-Heizgrenze abtesten
		if(ta1m.stat != 0)
			pHkd->heiz_grenz = 0;										// Merker
		else
		{ if(pHkd->heiz_grenz == 1)								// war Merker gesetzt ?
			{	if (ta1m.messw < pHks->TaHeizgrenze - 20)	// Hysterese 2,0K
					pHkd->heiz_grenz = 0;
			}
			else
			{	if (ta1m.messw >= pHks->TaHeizgrenze)
					pHkd->heiz_grenz = 1;
			}
		}			
		
		pHkd->somme = pHkd->sowi | pHkd->heiz_grenz;	// Sommer/Winter-Zustand oder Heizgrenz-Zustand nach Statusanzeige	

		if(pHkd->somme > 0)												// Sommerbetrieb ?
		{	
			if(hkAbschalten == 0)
				hkAbschalten = 1;
		}
	}
	
	// GWW-Vorrang
	//-------------------------------------------------------------------------------
		
	//---------------------------------------------------------------------------------------------------
	// Sonderphasen (Aufheizphase, St�tzbetrieb, Frostschutzbetrieb) testen
	// --> tvsb <-- wird entsprechend gesetzt
	//---------------------------------------------------------------------------------------------------

	hkd[hk].kaskaKorr = 0;
	 
	if ( pHkd->somme == TRUE )	
		; 
	else if(test_aufhe(hk) == 1)																// 1 = Sonderphase
		hkAbschalten = 0;
	else	
	{	
		// ---------------------------- Normalphase -----------------------------------------------
		// Berechnung der Heizungsvorlauftemp.(tvsb) �ber die Heizkennlinie
		tvret = tvsoll_ber(hk);	// wenn ok, dann tvsb berechnet(tvret=1), sonst tvsb = Tvmi (tvret= 0)
		//-----------------------------------------------------------------------------------------

		//-----------------------------------------------------------------------------------------
		// Anlagenschalter steht auf Nichtnutzung HK 
		//-----------------------------------------------------------------------------------------
		if(pHkd->absenSchalter == 1)	
		{	//------------------------------------------------
			// Schalter-Regie
			//------------------------------------------------
			if(pHkd->abschSchalter == TRUE)										// Abschalten ermittelt in Absenk.c (TestSchalter)
			{																									// kommt bei Frostbetrieb hier nicht vorbei
				if(hkAbschalten == 0)
					hkAbschalten = 1;
			}				
			else																							// kein Abschalten
			{	if(tvret)
					pHkd->tvsb -= pHkd->tvabSchalter;							// Berechn. Absenkwert abziehen
			}		
		}
		else
		{	//-----------------------------------------------------------------------------------------
			// Regel- oder Absenkphasen
			//-----------------------------------------------------------------------------------------
			if(pHkd->vorra_bed == TRUE)													// Vorrang Bedarfsabsenkung vor Zeitabsenkung
			{	
				//------------------------------------------------
				// Bedarfs-Regie
				//------------------------------------------------
				// Kaskade mit Kaskadewerten vom RIEcon50
				if(pHkd->bedarf == BEDARF_JA)											// Nur in der Nutzungszeit
				{	
					if ( pHkd->tisobed > 10 && pHkd->tibed > 10 )  	// nur wenn Soll- und Ist-Temp.> 1,0 �C ( sonst Fehler )
						raum_kaskade(hk, 1);													// 1 = R50-Kaskadewerte benutzen
				}						
				else
				{	// Bedarfsabsenkung bei 'Kein  Bedarf'
					if(abs_bed[hk].tvab > 0)												// wenn Absenkwert eingetragen (berechnet in Bedarf.c)
					{	if(abs_bed[hk].absch == TRUE  )								// Abschalten ermittelt in Bedarf.c
						{																							// kommt bei Frostbetrieb hier nicht vorbei
							if(hkAbschalten == 0)
								hkAbschalten = 1;
						}				
						else																					// kein Abschalten
						{	if(tvret)
								pHkd->tvsb -= abs_bed[hk].tvab;						// Absenkwert benutzen
						}								
					}
				}	
			}						
			else	// Zeitabsenkung oder Ferienabsenkung
			{
				//-------------------------------------------------
				// Ferien-Regie
				//-------------------------------------------------
				if( pHkd->vorra_bed == FALSE && ferienStat == 1 && pHkd->tvabFerien )	
				{	
					if(pHkd->abschFerien == TRUE)											// Abschalten ermittelt in Absenk.c (TestFerien)
					{																									// kommt bei Frostbetrieb hier nicht vorbei
						if(hkAbschalten == 0)
							hkAbschalten = 1;
					}				
					else																							// kein Abschalten
					{	if(tvret)
							pHkd->tvsb -= pHkd->tvabFerien;								// Berechn. Absenkwert abziehen
					}		
				}
				else
				{	//-----------------------------------------------
					// Zeit-Regie
					//-----------------------------------------------
					if(abs_ram[hk].tvab == 0)													// kein Absenkwert eingetragen (berechnet in Absenk.c)
					{	// Kaskade mit Raumtemperaturf�hler
						if(TI[hk]->stat == 0 && abs_ram[hk].absen == 0 )// wenn Status ok und nicht in Absenkung
							raum_kaskade(hk, 0);													// 0 = keine R50-Kaskadewerte benutzen
					}
					else
					{	// Absenkung nach Absenktabellen
						if(abs_ram[hk].absch == TRUE  )									// Abschalten ermittelt in Absenk.c
						{																								// kommt bei Frostbetrieb hier nicht vorbei
							if(hkAbschalten == 0)
								hkAbschalten = 1;
						}				
						else																						// kein Abschalten
						{	if(tvret)
								pHkd->tvsb -= abs_ram[hk].tvab;							// Absenkwert benutzen
						}
					}
				}											
			}
		}	
		
		// R�cklauftemperaturbegrenzung
		pHkd->rlbegr = 0;									// Statusanzeige R�cklauftemp.begrenzung l�schen
		if(pHks->Psbegr > 0)							// Begrenzung auf Prim�r-R�cklauftemp. ?
		{	pHks->Psbegr = 1;								// evtl. Fehlbedienung korrigieren
			if(TRP[ANL]->stat == 0)  				// Prim�r-R�cklauff�hler ok ?
				rueckl_begr(hk, 1);						// 1 = Begrenzung auf Prim�r-R�cklauftemp.
		}
		else															// Begrenzung auf Sekund�r-R�cklauftemp. 
		{	if(TRS[hk]->stat == 0)					// Sekund�r-R�cklauff�hler ok ?
				rueckl_begr(hk, 0);						// 0 = Begrenzung auf Sekund�r-R�cklauftemp.
		}		
	
	}	// ------------------------ Ende tvsb-Berechnung in der Normalphase ----------------------------------------


	if ( pHkd->somme == FALSE && FRGHK[hk]->bstat == 0 )		// Freigabe wird im Sommer ignoriert, Sommer dominiert
	{																												// Freigabesignal ist definiert
		if ( FRGHK[hk]->bwert == 0 )
		{																											// Heizkreis nicht freigegeben
			if ( ta1m.stat == 0 && ta1m.messw > pHks->TaFrostgrenze )
			{	if(hkAbschalten == 0)
					hkAbschalten = 1;
			}
			else
				pHkd->tvsb = pHks->Tvmi;
		}
	}

//	// Heizkreis abschalten mangels Bedarf
//	hkAbsch = RaumAbschaltung	( hk );
//	if ( hkAbschalten == 0 )
//		hkAbschalten = hkAbsch;	

// ---- ***AnFre 10.10.2007 Klimaschutz ------------------
// ***AnFre 06.06.2012 entfernt Munzert
//	if(Klima > 0)
//	{
//		pHkd->tvsb -= DTKlima;
//	}					

 }/* Ende ***************** Sollwert-Berechnung nur f�r Nahw�rmeNetz HKN: *********************** */

/* *********************** Sollwert-Berechnung nur f�r Lade-Heizkreis HK1: ********************* */
	if ( hk == HK1 )	// nur f�r Lade-HeizKreis 
	{
		if ( pHkd->bedLadung > 0 )
		{
			hkAbschalten = 0;
			pHkd->tvsb = hkd[HK2].tvsb + pHks->Tvpa;
		}
		else
		{
			pHkd->tvsb = 0;
//			pHkd->absSolBer = 0;	// 03.03.2015 Funktion entfernt 06.01.2017
			hkAbschalten = 1;
		}
	}	
/* Ende ****************** Sollwert-Berechnung nur f�r Lade-Heizkreis HK1: ********************* */

/* ******* Externe Anforderung UST1 und/oder UST2 f�r Nahw�rmeNetz HKN: und Lade-Heizkreis HK1:************ */

// ---- Anforderung externe HAST1 ------- ***AnFre 06.06.2012 ---------------
		if ( pHks->ExtAnf1_Ja > 0)
		{ 
			pHkd->ExtAnf1Hk.messw = ExtAnf1.messw;
			pHkd->ExtAnf1Hk.stat	= ExtAnf1.stat;

			if ( pHkd->ExtAnf1Hk.stat == 0 )
			{ 
			 	if ( hkAbschalten == 0 )
			 	{	// keine Abschaltbedingung
					if ( (pHkd->ExtAnf1Hk.messw + pHks->TvAnhExt) > pHkd->tvsb )
					{
						pHkd->tvsb = pHkd->ExtAnf1Hk.messw + pHks->TvAnhExt;
						externeAnforderung1Aktiv	=	1;		
					}
				}
				else
				{ // HK ist abgeschaltet
					if ( pHkd->ExtAnf1Hk.messw > 200 )
					{
						hkAbschalten = 0;
						pHkd->tvsb = pHkd->ExtAnf1Hk.messw + pHks->TvAnhExt;
						externeAnforderung1Aktiv	=	1;		
					}
				}
			}
		}
		else
		{
			pHkd->ExtAnf1Hk.messw	=	0;		
			pHkd->ExtAnf1Hk.stat	=	0;		
			externeAnforderung1Aktiv	=	0;		
		}

// ---- Anforderung externe HAST2 ------- ***AnFre 06.06.2012 ---------------
		if ( pHks->ExtAnf2_Ja > 0)
		{
			pHkd->ExtAnf2Hk.messw = ExtAnf2.messw;
			pHkd->ExtAnf2Hk.stat	= ExtAnf2.stat;

			if ( pHkd->ExtAnf2Hk.stat == 0 )
			{ 
			 	if ( hkAbschalten == 0 )
			 	{	// keine Abschaltbedingung
					if ( pHkd->ExtAnf2Hk.messw + pHks->TvAnhExt > pHkd->tvsb )
					{
						pHkd->tvsb = pHkd->ExtAnf2Hk.messw + pHks->TvAnhExt;
						externeAnforderung2Aktiv	=	1;		
					}
				}
				else
				{ // HK ist abgeschaltet
					if ( pHkd->ExtAnf2Hk.messw > 200 )
					{
						hkAbschalten = 0;
						pHkd->tvsb = pHkd->ExtAnf2Hk.messw + pHks->TvAnhExt;
						externeAnforderung2Aktiv	=	1;		
					}
				}
			}
		}
		else
		{
			pHkd->ExtAnf2Hk.messw	=	0;		
			pHkd->ExtAnf2Hk.stat	=	0;		
			externeAnforderung2Aktiv	=	0;		
		}
		
		pHkd->extAnfAktiv = externeAnforderung1Aktiv || externeAnforderung2Aktiv;
		if ( pHkd->extAnfAktiv > 0 )
			hkdSoL[HK1].solLadung_war = 0;	//f�r Drehzahl Pumpennachlauf l�schen
		
/* Ende ******* Externe Anforderung UST1 und/oder UST2 ******************************** */
	
/* ***AnFre 03.03.2015 Berechnete Absenkung f�r LadeHeizkreis wenn HKS: "Solares Heizen Ein" */
// Funktion wieder entfernt !!! 06.01.2017
//	 if(hk == HK1 )
//	 {
//		pHkd->absSolBer = 0;
//	 	if ( hkdSoL[HK1].hkSolJa > 0 && pHkd->tvsb > 199 )
//		{
//			if ( ts3 > pHkd->tvsb )
//			{
//				pHkd->absSolBer = (((ts3 - pHkd->tvsb) * pHks->AbsenkFaktor) + 50) / 100;
//				if ( pHkd->absSolBer > pHks->AbsenkSol )
//					pHkd->absSolBer = pHks->AbsenkSol;
//			}
//		}
//		if ( pHkd->tvsb > pHkd->absSolBer )
//			pHkd->tvsb -= pHkd->absSolBer;
//	 }
	
/* ----------------------------- Maximalwertbegrenzung ---------------------------------*/
	if(pHkd->tvsb > pHks->Tvma)
		 pHkd->tvsb = pHks->Tvma;
	else if(pHkd->tvsb < pHks->Tvmi)
		 pHkd->tvsb = pHks->Tvmi;	

//	***AnFre 06.06.2012  solare Anhebung und Legionelle gilt nur f�r Nahw�rmeNetz in HKN: (HK2)
// ACHTUNG: Ausserhalb von TVMAX, TVMIN 
	 if(hk == HK2 )
	 {
			if ( pHkd->legio > 0 && pHkd->tvsb < pHks->Twwleg )
			{
				pHkd->tvsb = pHks->Twwleg;
			} 
	
			if ( pHkd->solAnheb > 0 && pHkd->tvsb > 199 )
			{
				pHkd->tvsb = pHkd->tvsb + pHks->SolAnhebung;
			} 
	 }
 // ***AnFre Bei "Wartung erforderlich" ( Notbetrieb )		 
	if ( NotBetr == 1 )
	{
		pHkd->tvsb = sos[SO1].NotTemp;
	}

// Test: Estrich-Programm
	pHkd->estrichProg = TestEstrichProg ( hk );
	if ( pHkd->estrichProg == TRUE )
	{
		pHkd->tvsb = pHkd->estrichTemp * 10;
		if (pHkd->tvsb > pHks->Tvma )
	 		pHkd->tvsb = pHks->Tvma;
	 	hkAbschalten = 0;							// alle Abschaltbedingungen ( Sommer ! ) sind unwirksam
	}

	//-------------------------------------------------------------------
	// Untersuchung auf hkAbschalten
	//-------------------------------------------------------------------

	#if SSF == 1
	if ( ssfEinAnl == TRUE )							// Abgasmessung
	{
		if ( hkAbschalten )
		{
			hkAbschalten = 0;									// Programm l�uft nicht �ber Funktion hk_abschalten (),
			pHkd->tvsb  = 0;									// der Kessel wird bei Abgasmessung immer eingeschaltet. Wenn im Sommer jedoch tvsb
		}																		// ver�ndert w�rde, schaltete bei Mehr-Kessel-Anlagen u.U. nicht nur der zu messende.
	}
	#endif	
	
	if(hkAbschalten != 0)
	{
		hk_abschalten ( hk, hkAbschalten )	;
		return;																		// TASK ENDE	!!!!!
	}	
	//-------------------------------------------------------------------

//// ***AnFre 21.01.2010 --------------------- entfernt 06.06.2012
//// f�r die Regelung ist tvsb_solar g�ltig
// 	pHkd->tvsb_solar = pHkd->tvsb;
//// Absenkung Regel-Sollwert bei Solarer-Heizung HKS: 
// 	if ( hkdSoL[HK1].hkSolJa > 0 )
//	{
//		if ( pHkd->tvsb > 199 )
// 			pHkd->tvsb_solar -= hksSoL[HK1].TvAbsenk;
//	}
		

		// Schornsteinfeger-Funktion. Solltemp.wird bei laufender Estrich-Trocknung	nicht ver�ndert !	
	#if SSF == 1
	if ( ssfEinAnl == TRUE && pHkd->estrichProg == FALSE )
	{
		pHkd->tsol = pHks->Tvma;
		pHkd->fl_tsol	= (float)pHkd->tsol / 10;
	}
	else
	#endif	

	// D�mpfung des berechneten Sollwertes: tvsb --> ged�mpfte tsol
	if( (pHkd->regstart == 0) || (pHkd->wwvorKorr > 0) )	// nach Reset oder bei gleit. WW-Vorrang
	{	 pHkd->tsol			= pHkd->tvsb;									// keine Filterung
		 pHkd->fl_tsol	= (float)pHkd->tsol / 10;
		 pHkd->regstart	= 1;
	}	 
	else
	{
		pHkd->fl_tsol = g_filter(pHkd->fl_tsol, pHkd->tvsb, pHks->Ts, pHks->Fzk);
		pHkd->tsol 	  = (int)(pHkd->fl_tsol * 10);					// f�r Anzeige
	}

	//	----------------------------------------------------------------------
	//	Reglertyp: P- / PID-Regler
	//	----------------------------------------------------------------------
	// Test Vorlauff�hler
	if(TVS[hk]->stat == 0)	// Status: 0...Ok, 41H...�berlauf,  21H...Unterlauf
	{	
		// Regelabweichung Soll - Ist
		fl_ei	= pHkd->fl_tsol - (float)TVS[hk]->messw / 10;
		
		// -------------- PID-Regelalgorithmus ---------------------------------
		// Berechnung der relativen Stellgr��en
		fl_dy_rel = Dy_rel ( pHks->Kp, pHks->Kd, pHks->Ts, pHks->Tn, 
														fl_ei, pHkd->fl_ei1, pHkd->fl_ei2 );

		// Leistungs-Begrenzung
		#if LEIST_BEGR > 0
		if ( pHks->LeistBegrTs > 0 )
		{
			if ( grenzLeistung.begrenzung == 1 )
			{ // Ventil f�hrt nicht weiter Auf
				if ( fl_dy_rel > 0 ) 
					fl_dy_rel = 0;
			}
			else	if ( grenzLeistung.begrenzung == 2 )
			{ // Ventil f�hrt pro Tastzeit LeistBegrTs % Zu 
				if ( fl_dy_rel > ((float)pHks->LeistBegrTs *(-1))) 
					fl_dy_rel = (float)pHks->LeistBegrTs*(-1);
			}
		}
		#endif

		pHkd->fl_y_rel += fl_dy_rel;
		
		pHkd->dy_rel	= (int)(fl_dy_rel * 1000);					// f�r debug

		//---------------------------------------------------------------------
		// Regelabweichungen merken
		pHkd->fl_ei2 = pHkd->fl_ei1;
		pHkd->fl_ei1 = fl_ei;						
		// Parameterumwandlung float to int
		pHkd->ei = (int)(fl_ei * 10);											// [0,1%] zur Anzeige
		
		//--------------------------------------------------------------------------
		// Abfrage Handbetrieb
		//--------------------------------------------------------------------------
		if(pHks->Haut == TRUE)			
			hkd[hk].fl_y_rel = (float)pHks->Vstell / 10;		// PID-Wert durch Handwert �berschreiben
		else
		{
			// Berechnung und Ausgabe der absoluten Stellgr��en
			// --------------------------------------------------------------------
			// Ausgabe an 3-Punkt Ventil
			if ( pHks->Vst > 0 )
			{	
				pHkd->stellzeit = (int)( fl_dy_rel * (float)pHks->Hub * 60 / (float)pHks->Vst ); // [0.01 s]			
				pHkd->stellsum += pHkd->stellzeit;			
				if(abs(pHkd->stellsum) >= 100)								// ab 1 Sekunde ausgeben
				{
					pHkd->fahren		= pHkd->stellsum / 100;			// nur ganze Sekunden fahren
					pHkd->stellsum	= pHkd->stellsum % 100; 		// Rest merken
					if(pHkd->fahren > 0)		
						RAUF[hk]->wert = (char)pHkd->fahren;
					else
						RZU[hk]->wert  = (char)abs(pHkd->fahren);	
				}
			}	

			// Dynamische Ventilstellung Min ***AnFre 06.06.2012
			// Temperatur zuweisen
			if ( hk == HK1 )	// Ladekreis
			{
				if ( TVKE[KE1]->stat == 0 )
					tvPrim = TVKE[KE1]->messw;
				else
					tvPrim = 0;
			}
			if ( hk == HK2 )	// Netzkreis
			{
				if ( TW2_[0]->stat == 0 )
					tvPrim = TW2_[0]->messw;
				else
					tvPrim = 0;
			}
			if ( TRS[hk]->stat == 0 && pHkd->tvsb > TRS[hk]->messw && tvPrim > TRS[hk]->messw )
			{
				korrRL = TRS[hk]->messw - pHks->RLKorrMin;
			}
			else
			{
				korrRL = 0;
			}
			// Berechnung dynamische Ventil-Min-Stellung				
			if ( pHks->RLKorrMin > 0  && pHkd->tvsb > 0  && tvPrim > 0 && korrRL > 0 )
			{
				pHkd->ventMinBer = ( (((pHkd->tvsb - korrRL) *10) / ((tvPrim - korrRL)/10)) *10 );
			}
			else
			{
				pHkd->ventMinBer = 0;
			}
			if ( pHkd->ventMinBer > 1000 )					// 100,0%
				pHkd->ventMinBer = 1000;
			if ( pHkd->ventMinBer < pHks->Y_rel_min )
				pHkd->ventMinBer = pHks->Y_rel_min;

			
			// Ausgabe an 0-10V Ventil
			fl_Y_rel_beg = (float)pHks->Y_rel_beg / 10;			// Beginn der Ventil�ffnung
			fl_Y_rel_min = (float)pHkd->ventMinBer / 10;		// Minimalbegrenzung	***AnFre 06.06.2012
			
			if(pHkd->fl_y_rel  > 100)												// Begrenzung max 100 %
				 pHkd->fl_y_rel  = 100;
			
			if(fl_dy_rel > 1)																// nur bei positiver �nderung
			{	if(pHkd->fl_y_rel < fl_Y_rel_beg)							// und Wert kleiner als Ventil�ffnungsbeginn,
					 pHkd->fl_y_rel = fl_Y_rel_beg;							// dann Setzen auf Ventil�ffnungsbeginn
			}
			
			if(pHkd->fl_y_rel  < fl_Y_rel_min)								
				 pHkd->fl_y_rel  = fl_Y_rel_min;							// Minimalbegrenzung

// -------- ***AnFre 12.02.2009 'Solare Heizunterst�tzung f�r HK1' -----------
	// Konventionelles Ventil:Regel-Beginn erst wenn RVENTSO[HK1] "AUF"	ist
			if(hk == HK1 )
			{	
				if ( hkdSoL[HK1].hkSolJa == 1 )
				{
					if ( hkdSoL[HK1].y_rel <= hksSoL[HK1].RVSoMax - 50)			// ab 5 % unter RVENTSO-Max
					 pHkd->fl_y_rel  = fl_Y_rel_min;

	// RV-Begrenzung auf 70%, wenn "Solares Heizen"
					if ( pHkd->fl_y_rel > ((float)pHks->VentMaxSolar / 10) )
						pHkd->fl_y_rel = (float)pHks->VentMaxSolar / 10;
				}
	 		}
				
			pHkd->y_rel = (int)(pHkd->fl_y_rel * 10);				// Zur Anzeige und Weiterverarbeitung
			RVENT[hk]->awert = pHkd->y_rel;									// Ausgabe an Stellventil
		}
	}	

// -------- ***AnFre 04.11.2009 STW-Abschaltung -----------
	if ( STWHK[hk]->bwert == TRUE )
	{
		RVENT[hk]->awert = 0;					// Ausgabe 0 Volt an Stellventil
	}		
}

/*---------------------- Ende Task RegelHk -----------------------------------*/


/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Berechnung der Vorlauf-Soll-Temperatur �ber die Heizkennlinie */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//  IN: hk.....Heizkreis
// OUT:	tvsb...berechnete Vorlauftemperatur [0.1�C]
char tvsoll_ber(char hk)
{
	float fl_tvsb, fl_steigung, fl_niveau, fl_tadiff;
	char ret;
	
	fl_tvsb = fl_steigung = fl_niveau = fl_tadiff = 0;
	
	fl_steigung		=  (float)hks[hk].Anst / 100;
	fl_niveau			=  (float)hks[hk].Tvpa / 10;
	fl_tadiff			=  (float)hks[hk].Taha / 10 - (float)ta1m.messw / 10;
	
	if(fl_tadiff < 0)		// wenn Ta gr��er als Ta am Heizkurvenanfang
	{	// Vorlauf Minimum einstellen
		hkd[hk].tvsb = hks[hk].Tvmi;
		ret = 0;					// Return not ok
	}
	else
	{	// Vorlauf Berechnung
		fl_tvsb = fl_niveau + fl_steigung * fl_tadiff + (float)0.05; //mit Rundung auf 1/10
		// float to integer
		hkd[hk].tvsb = (int)(fl_tvsb * 10);
		ret = 1;					// Return ok
	}
	hkd[hk].tvsb_hkl = hkd[hk].tvsb;	// Merken f�r debug
	
// ##### ulsch : Adaption = temperaturabhaengige Korrektur der Heizkurve
	hkd[hk].tvsb += hkd[hk].adaptKorr;
	
	
	return(ret);
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* Raumtemperatur-abhaengige TVSOLL-Verschiebung								 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//  IN: hk.....Heizkreis
//			ada....1 = Soll. und Isttemp.  von R50 benutzen
//			tvsb...schon berechnete  Vorlauftemperatur (Heizkennlinie)
// OUT:	tvsb...verschobene Vorlauftemperatur
void raum_kaskade(char hk, char ada)
{
	int mwAdap = 0;
	long kas;
	int eik = 0;		

		
//ulsch: wenn eine Adaption der Heizkennlinie durchgef�hrt wird, soll die Kaskade nur zur Anhebung des Vorlauf-Sollwertes 
// benutzt werden (Raum-Ist < Soll) und nur, wenn der RIEcon50 Unterversorgung	(bezieht sich auf alle R�ume) signalisiert	
//ulsch: 27.03.07: per Parametrierung soll die Kaskade trotz Adaption uneingeschr�nkt wirken ( Parameter KaskMode ) !
	switch ( hk )
	{
		case HK1 :
			#if ADAP_STAT_HK1 > 0
			mwAdap = mwAdaption[HK1][0].messw;
			#endif
			break;	
		case HK2 :
			#if ADAP_STAT_HK2 > 0
			mwAdap = mwAdaption[HK2][0].messw;
			#endif
			break;
		case HK3 :
			#if ADAP_STAT_HK3 > 0
			mwAdap = mwAdaption[HK3][0].messw;
			#endif
			break;	
		case HK4 :
			#if ADAP_STAT_HK4 > 0
			mwAdap = mwAdaption[HK4][0].messw;
			#endif
			break;												
	}

	if ( hks[hk].KaskMode == 0 )
	{
		if ( mwAdap == 50 || mwAdap == 80 || ( mwAdap == 20 && ( hkd[hk].tisobed < hkd[hk].tibed ) ) )
		{
			hkd[hk].kaskaKorr = 0;
			return;
		}
	}
				
	if(ada == 0)
	{	// Regelabweichung RAUM-SOLL - RAUM-IST
		// int Zeiger TI[] wird in Load_Userdef() ("UserReply.c") in Abh�ngigkeit vom
		// aktuellen Projekt geladen. Projektdefinitionen sind "UserConst.c" festgelegt
		
		// 090106: wirksame Raum-Soll-Temp. wird  durch Parameter KaskBegr begrenzt
		if ( hks[hk].Tiso <= hks[hk].KaskBegr )
			eik = hks[hk].Tiso - TI[hk]->messw;
		else if ( TI[hk]->messw < hks[hk].KaskBegr )	// Raumtemp. < KaskBegr : statt Tiso gilt KaskBegr 
			eik = hks[hk].KaskBegr - TI[hk]->messw;
		else if ( TI[hk]->messw > hks[hk].Tiso )			// Raumtemp. > Tiso
			eik = hks[hk].Tiso - TI[hk]->messw;
		else																					// Raumtemp. > KaskBegr, aber < Tiso
			eik = 0; 		
	}
	
	if(ada == 1)
	{ // Regelabweichung RAUM-SOLL-ADAP - RAUM-IST-ADAP
		if ( hkd[hk].tisobed <= hks[hk].KaskBegr )
			eik = hkd[hk].tisobed - hkd[hk].tibed;
		else if ( hkd[hk].tibed < hks[hk].KaskBegr )
			eik = hks[hk].KaskBegr - hkd[hk].tibed;
		else if ( hkd[hk].tibed > hkd[hk].tisobed )
			eik = hkd[hk].tisobed - hkd[hk].tibed;
		else
			eik = 0;
	}
	
	kas = (long)eik * hks[hk].Kpk / 100;				// 071012: Wirkung der Kaskade begrenzt auf +20,0/-10,0
	if ( kas > 200 )
		kas = 200;
	else if ( kas < -100 )
		kas = -100;
		
	hkd[hk].kaskaKorr = (int)kas;
	
	hkd[hk].tvsb += (int)kas;
		
}

/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* R�cklauftemperatur-abhaengige TVSOLL-Verschiebung						 */
/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//  IN: hk.....Heizkreis
//			ps.....Begrenzung auf Prim�r(1)- oder Sekund�r(0)- R�cklauftemp.
//			(tvsb...berechnete  Vorlauftemperatur (Heizkennlinie + Kaskade)
// OUT:	tvsb...verschobene Vorlauftemperatur
void rueckl_begr(char hk, char ps)
{
	float fl_tvsb, fl_absenk, fl_eir, fl_tr;
	
	fl_tvsb = fl_absenk = fl_eir = fl_tr = 0;
	
	// welche R�cklauftemperatur ?
	if(ps == 1)														// Begrenzung auf Prim�rr�cklauftemp. ?
		fl_tr = (float)TRP[ANL]->messw / 10;
	else																	// Begrenzung auf Sekund�rr�cklauftemp.
		fl_tr = (float)TRS[hk]->messw / 10;				
		
	// Abweichung R�CKLAUF - R�CKLAUF.MAX
	fl_eir = fl_tr - (float)hks[hk].Trma / 10;
	
	if(fl_eir >= 0)									// nur wenn MAX �berschritten
	{	hkd[hk].rlbegr = 1;					// Statusanzeige R�cklaufbegrenzung setzen
		
		// Errechne Absenkwert.
		fl_absenk = fl_eir * (float)hks[hk].Kpr / 100;
		hkd[hk].rlKorr = (int)(fl_absenk *10 );					// ***AnFre f�r Anzeige in hk1.h: Korrekur RL
		
		// Lade berechnete  Vorlauftemperatur nach Heizkurve + Kaskade
		fl_tvsb = (float)hkd[hk].tvsb / 10;

		// Verschiebung berechnen
		if(fl_tvsb > fl_absenk + 1)				// Sicherstellen, dass das Ergebnis positiv ist
			fl_tvsb = fl_tvsb - fl_absenk;
		else
			fl_tvsb = 1;										// mindestens 1�C
		
		// float to integer
		hkd[hk].tvsb = (int)(fl_tvsb * 10);
	}
	else
	{
		hkd[hk].rlKorr = 0;
	}

}	


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
/* 		Sonderphasen testen (Aufheizphase, St�tzbetrieb, Frostschutzbetrieb)				*/
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
//  IN: hk.....Heizkreis
// OUT: tvsb...Sonderphase aktiv  : return 1
char test_aufhe(char hk)
{
	char ret;
	
	ret = 0;
	
	if(hkd[hk].absenSchalter == 1)
	{
		if(hkd[hk].stuetzSchalter == 1)					// St�tzbetrieb
		{	tvsoll_ber ( hk );										// nach Heizkennlinie
			ret = 1;													
		}
		else if(hkd[hk].frostSchalter == 1)			// Frostschutzbetrieb
		{	hkd[hk].tvsb =  hks[hk].Tvmi;					// Minimalwert laden
			ret = 1;													
		}
	}
	else
	{	if(hkd[hk].vorra_bed == TRUE)						// Vorrang Bedarfsabsenkung vor Zeitabsenkung
		{
			// Bedarfsabsenkung	(Phasen ermittelt in Bedarf.c)
			
			if(abs_bed[hk].aufhe == 1)						// Aufheizphase
			{	hkd[hk].tvsb =  hks[hk].Tvma;				// Maximalwert laden
				ret = 1;
			}
			else if(abs_bed[hk].stuetz == 1)			// St�tzbetrieb
			{	tvsoll_ber ( hk );									// nach Heizkennlinie
//#####090116 auf Wunsch des Chefs
				hkd[hk].tvsb -= abs_bed[hk].tvab;		// Absenkwert benutzen
				ret = 1;													
			}
			else if(abs_bed[hk].frost == 1)				// Frostschutzbetrieb
			{	hkd[hk].tvsb =  hks[hk].Tvmi;				// Minimalwert laden
				ret = 1;													
			}
		}
		else		// Zeitabsenkung	(Phasen ermittelt in Absenk.c)
		{	
			if(hkd[hk].absenFerien == 1)					// Ferienbetrieb
			{
				if(hkd[hk].stuetzFerien == 1)				// St�tzbetrieb
				{	tvsoll_ber ( hk );								// nach Heizkennlinie
//#####090116
					hkd[hk].tvsb -= hkd[hk].tvabFerien;		// Berechn. Absenkwert abziehen
					ret = 1;													
				}
				else if(hkd[hk].frostFerien == 1)		// Frostschutzbetrieb
				{	hkd[hk].tvsb =  hks[hk].Tvmi;			// Minimalwert laden
					ret = 1;													
				}
			}
			else	// Absenkbetrieb
			{
				if(abs_ram[hk].aufhe == 1)					// Aufheizphase
				{	hkd[hk].tvsb =  hks[hk].Tvma;			// Maximalwert laden
					ret = 1;
				}
				else if(abs_ram[hk].stuetz == 1)		// St�tzbetrieb
				{	tvsoll_ber ( hk );								// nach Heizkennlinie
//#####090116
					hkd[hk].tvsb -= abs_ram[hk].tvab;			// Absenkwert benutzen
					ret = 1;													
				}
				else if(abs_ram[hk].frost == 1)			// Frostschutzbetrieb
				{	hkd[hk].tvsb =  hks[hk].Tvmi;			// Minimalwert laden
					ret = 1;													
				}
			}	
		}
	}
		
	return(ret);
}


char TestEstrichProg ( char hk )	
{
	HkDynam *pHkd;	
	HkStandard *pHks;
	char fbh;
	char tg;
	UINT start, jetzt;							// als Tag des Jahres
	datum heute;
	char ret = FALSE;

	// Strukturpointer zuweisen
	pHkd = &hkd[hk];	
	pHks = &hks[hk];

	if ( hk == HK1 )
		fbh	= FBH_HK1;
	else if ( hk == HK2 )
		fbh	= FBH_HK2;
	else if ( hk == HK3 )
		fbh	= FBH_HK3;
	else if ( hk == HK4 )
		fbh	= FBH_HK4;
	else
		fbh = 0;	

	if ( fbh > 0 )
	{
		tg = 0;
		while ( tg < ESTR_STUFEN && pHks->EstrichTemp[tg] != 0 )
			tg++;												// Anzahl Estrich-Tage 	
		if ( tg > 0 )
		{
			if (  pHks->StartAufheiz.jahr == Jahr && Mon == pHks->StartAufheiz.monat && Tag >= pHks->StartAufheiz.tag && Tag < pHks->StartAufheiz.tag + tg )
			{
				pHkd->estrichTag = Tag - pHks->StartAufheiz.tag + 1;
				ret = TRUE;			
			}
								
			else if ( pHks->StartAufheiz.jahr == Jahr && Mon == pHks->StartAufheiz.monat + 1 )
			{
				start = DayOfYear ( pHks->StartAufheiz );
				heute.tag = Tag;
				heute.monat = Mon;
				heute.jahr = Jahr;
				jetzt = DayOfYear ( heute );
				if ( jetzt < start + tg )	
				{
					pHkd->estrichTag = jetzt-start + 1;
					ret = TRUE;			
				}
			}
									
			else if ( pHks->StartAufheiz.jahr == Jahr - 1 && Mon == 1 && pHks->StartAufheiz.monat == 12 )
			{
				if ( ( 31 - pHks->StartAufheiz.tag + 1 + Tag ) <= tg )
				{
					pHkd->estrichTag = 31 - pHks->StartAufheiz.tag + Tag + 1;
					ret = TRUE;			
				}					
			}
		}
	}		

	if ( ret == TRUE )
		pHkd->estrichTemp = pHks->EstrichTemp[pHkd->estrichTag - 1];
	else
	{
		pHkd->estrichTemp = 0;
		pHkd->estrichTag = 0;
	}	
		
	return ( ret );
}


char RaumAbschaltung	( char hk )
{
	char hkAbschalten = 0;
	char raumbedarf = 0;
		
	if ( hk == HK1 )
		raumbedarf = BEDARF_HK1;
	else if  ( hk == HK2 )
		raumbedarf = BEDARF_HK2;
	else if  ( hk == HK3 )
		raumbedarf = BEDARF_HK3;
	else if  ( hk == HK4 )
		raumbedarf = BEDARF_HK4;
	
	if ( raumbedarf == TRUE )
	{
		// keine Abschaltung, wenn Funktion nicht freigegeben, Au�entemp.gest�rt oder <= Frostgrenze,
		// externe Raum-Soll- oder -Ist-Temp.gest�rt (<= 1�C) oder Ist-Temp. < Soll
		if ( hks[hk].AbschRaumanf != TRUE || ta1m.stat != 0 || hkd[hk].tibed <= 10 || hkd[hk].tisobed <= 10  )
		{
			hkd[hk].raumAbsch = 0;							// nicht auswertbar
			hkd[hk].ventOffenBer = 0;
		}
		else if ( ta1m.messw <= hks[hk].TaFrostgrenze	)
		{
			hkd[hk].raumAbsch = 2;							// nicht abschalten
			hkd[hk].ventOffenBer = 0;
		}
		else
		{
			if ( hks[hk].VentilAuswert == TRUE )
			{
				// Plausibilit�t der Ventilstellungen pr�fen
				// ventGesamt: Anzahl der R�ume in Nutzung/Vorheizen. ventOffen: Anzahl der offenen Ventile
				// gest�rte R�ume unber�cksichtigt
				if ( ( hkd[hk].ventGesamt == 0 ) || ( hkd[hk].ventOffen > hkd[hk].ventGesamt ) )
				{
					hkd[hk].raumAbsch = 0;					// nicht auswertbar
					hkd[hk].ventOffenBer = 0;
				}
				else 
				{
					hkd[hk].ventOffenBer = 	100 * hkd[hk].ventOffen  /  hkd[hk].ventGesamt;
					if ( hkd[hk].tibed < hkd[hk].tisobed )
						hkd[hk].raumAbsch = 2;				// nicht abschalten					
					else if ( hkd[hk].ventOffenBer <= hks[hk].VentOffenMax )
						hkd[hk].raumAbsch = 1;				// abschalten
					else
						hkd[hk].raumAbsch = 2;				// nicht abschalten
				}
			}
			else
			// Ventile nicht auswerten, Raum-Ist >= Soll
			{
				hkd[hk].ventOffenBer = 0;
				if ( hkd[hk].tibed < hkd[hk].tisobed )
					hkd[hk].raumAbsch = 2;				// nicht abschalten	
				else
					hkd[hk].raumAbsch = 1;				// abschalten
			}
		}
	}
	if ( hkd[hk].raumAbsch == 1 )
		hkAbschalten = 1;
	return ( hkAbschalten );
}

