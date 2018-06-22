//// -------------------- Funktion: Regelung der Quellenregeneration (Weichen- und Quellenkreis) (1s-Takt) ------------
//// 16.06.2016_SiWa

#include <string.h>
#include "struct.h"
#include "ustruct.h"
#include "defins.h"
#include "sramext.h"
#include "uramext.h"
#include "standdef.h"
#include "unoinitext.h"
#include "uconstext.h"
//#include "Int_Regeldifferenz.h"

void Steuer_QRG (void)
{
	
	 
	static char neustart_SiWa = 1;		// Programmstart
	static char sch_current_BM = 0;
	static char sch_recent_BM = 1; 
	
				 char Steuerungsfall_WEI = 3;
				 char Steuerungsfall_QU = 3;	
				 
	float fl_ei = 0;  		// Regelabweichung
	float fl_dy_rel = 0;	// Berechnung der relativen Stellgröße
	float fl_Y_rel_beg = 0; 	
	float fl_Y_rel_min = 0; 
/*------------------------Steuerung des Weichenkreis------------------------*/

// Handbetrieb Weichenpumpe PU WEI 
if (wes[0].chpa_pu_Hau > 0)
	{
		DA_UNI[U3]->wert = wes[0].chpa_pu_ein;
	}

// Handbetrieb Regelventil RV WEI 
if (wes[0].chpa_rv_Hau > 0)
	{
		AA_UNI[U5]->awert = wes[0].ipa_rv_stellung;
	}

// Funktion: "Letzte" Rücklauftemperatur speichern

			// Einschaltwert "sod[SO1].TQRL_recent" generieren --> Nach jedem Ausschalten der Betriebsmeldung WPU wird der Wert der Rücklauftemp in der Quelle abgespeichert
					if (neustart_SiWa == 0)
						{
							sch_current_BM = BM_UNI[U1]->bwert;  // Quellenkreispumpe
							
						if (sch_recent_BM == 0 && sch_current_BM ==0)  // negative Flanke
								{
									sch_recent_BM = 1;
									wed[0].TQRL_recent = TP_UNI[U3]->messw;
								}	
						else if (sch_recent_BM == 1 && sch_current_BM ==1) // positive Flanke
											{
											sch_recent_BM = 0;
											}		
						}
				
			//				
					if (neustart_SiWa > 0)
						{

							{
								neustart_SiWa = 0;
								wed[0].TQRL_recent = 150;
							}
						}
					
					
				if(wes[0].ipa_Funktion_TP > 0)
					{	
						// Sollwertberechnung für RV WEI
								wed[0].tvsb = anaInp[U5].mwSkal.messw + wes[0].ipa_Taupunktgrenze + 20;
						// Dämpfung des berechneten Sollwertes: tvsb --> gedämpfte tsol
							if( wed[0].regstart == 0) 	// nach Reset oder bei gleit. WW-Vorrang
							{	 wed[0].tsol			= wed[0].tvsb;												// keine Filterung
								 wed[0].fl_tsol	= (float)wed[0].tsol / 10;
								 wed[0].regstart	= 1;
							}	 
							else
							{
								wed[0].fl_tsol = g_filter(wed[0].fl_tsol, wed[0].tvsb, wes[0].Ts, wes[0].Fzk);
								wed[0].tsol 	  = (int)(wed[0].fl_tsol * 10);					// für Anzeige
							}
				 	}
				 	else
				 		{
				 			wed[0].tvsb = 0;
				 		}
			
// Betriebszustände

// Alarme bzw. Schutzfunktionen
// 1. Taupunktschutz

	if (wes[0].ipa_Funktion_TP > 0 && TS5_[0]->messw < anaInp[U5].mwSkal.messw + wes[0].ipa_Taupunktgrenze)
		{
			wed[0].chbz_Taupunktschutz = 1;
		}
		else if (TS5_[0]->messw > anaInp[U5].mwSkal.messw + wes[0].ipa_Taupunktgrenze + 30 || wes[0].ipa_Funktion_TP == 0)
			{
				wed[0].chbz_Taupunktschutz = 0;
			}

// 2. E-Tankschutz
				// Mindestlaufzeit der Quellenregeneration zur Kontrolle der max. Beladungstemperatur
				if (wed[0].chbz_Nieder_QRG > 0 || wed[0].chbz_Hoch_QRG > 0 || wed[0].chbz_Quellenanhebung > 0)
					{
						if(wed[0].iCo_QRG == 0)
							{
								wed[0].iCo_QRG = 0;
							}
							else
								{
									wed[0].iCo_QRG = wed[0].iCo_QRG - 1;
								}
					}
					else
						{
							wed[0].iCo_QRG = wes[0].ipa_eTank_Minlaufzeit * 60;
						}
						
						// Einschalten der eTankschutzes
						if (wed[0].iCo_QRG == 0 && TP_UNI[U3]->messw >= wes[0].ipa_eTankgrenze)
							{
								wed[0].chbz_eTankschutz = 1;
							}
						// Auscshalten des eTankschutzes
						if (wed[0].chbz_eTankschutz > 0)
							{
								if (TP_UNI[U3]->messw <= wes[0].ipa_eTankgrenze - 50) //qud[0].chpa_bmwpu > 0 && AA_UNI[U6]->awert > 999 && TP_UNI[U3]->messw <= wes[0].ipa_eTankgrenze - 50)
									{
										wed[0].chbz_eTankschutz = 0;
									}
							}	
						

// Quellenregeneration und Quellenanhebung
	// 3. Niedertemperaturquellenregeneration
			// Einschalten
		  if (wed[0].chbz_Nieder_QRG == 0)
		  	{
				if ( wed[0].chbz_Taupunktschutz == 0 &&  wed[0].chbz_eTankschutz == 0
					 &&  (sod[SO1].kollEin > 0 || sod[SO1].puffEin > 0) && 
					 ((TP_UNI[U1]->messw > TP_UNI[U3]->messw + wes[0].ipa_Nieder_QRG_ein || TP_UNI[U1]->messw > wed[0].TQRL_recent + wes[0].ipa_Nieder_QRG_ein) 
					 && TS3_[0]->messw < TRS[HK1]->messw - 40)  )
					{
						wed[0].chbz_Nieder_QRG = 1;
					}
				}
			// Ausschalten
			if (wed[0].chbz_Nieder_QRG == 1)
		  	{
				if ( wed[0].chbz_Taupunktschutz > 0 ||  wed[0].chbz_eTankschutz > 0 || 
					(sod[SO1].kollEin == 0 && sod[SO1].puffEin == 0) 
					|| (TP_UNI[U1]->messw < TP_UNI[U3]->messw + 10 && TP_UNI[U1]->messw < wed[0].TQRL_recent + 10) 
					|| TS3_[0]->messw > TRS[HK1]->messw )
					{
						wed[0].chbz_Nieder_QRG = 0;
					}
				}	

	// 4. Hochtemperaturquellenregeneration
			// Einschalten
		  if (wed[0].chbz_Hoch_QRG == 0)
		  	{
				if ( wed[0].chbz_Taupunktschutz == 0 &&  wed[0].chbz_eTankschutz == 0 &&  
					 (sod[SO1].kollEin > 0 || sod[SO1].puffEin > 0) && 
					 ((TP_UNI[U1]->messw > TP_UNI[U3]->messw + wes[0].ipa_Nieder_QRG_ein || TP_UNI[U1]->messw > wed[0].TQRL_recent + wes[0].ipa_Nieder_QRG_ein) 
					 && TS3_[0]->messw > TRS[HK1]->messw + wes[0].ipa_Hoch_QRG_ein)  )
					{
						wed[0].chbz_Hoch_QRG = 1;
					}
				}
			// Ausschalten
			if (wed[0].chbz_Hoch_QRG == 1)
		  	{
				if ( wed[0].chbz_Taupunktschutz > 0 ||  wed[0].chbz_eTankschutz > 0 || 
					(sod[SO1].kollEin == 0 && sod[SO1].puffEin == 0) || 
					TP_UNI[U1]->messw < TP_UNI[U3]->messw + 10  || TS3_[0]->messw < TRS[HK1]->messw + wes[0].ipa_Hoch_QRG_aus)
					{
						wed[0].chbz_Hoch_QRG = 0;
					}
				}	
	
	// 5. Quellenanhebung
			// Einschalten
		  if (wed[0].chbz_Quellenanhebung == 0)
		  	{
				if ( (wed[0].chbz_Hoch_QRG > 0 || wed[0].chbz_Nieder_QRG > 0) && qud[0].chbz_WPU_Versorgung > 0 && TP_UNI[U2]->messw < qus[0].ipa_Sollwert_WPU_VL - 40  )
					{
						wed[0].chbz_Quellenanhebung = 1;
					}
				}
			// Ausschalten
			if (wed[0].chbz_Quellenanhebung == 1)
		  	{
				if ( (wed[0].chbz_Hoch_QRG == 0 && wed[0].chbz_Nieder_QRG == 0) || qud[0].chbz_WPU_Versorgung == 0 || TP_UNI[U2]->messw > qus[0].ipa_Sollwert_WPU_VL - 20  )
					{
						wed[0].chbz_Quellenanhebung = 0;
					}
				}				
			
			// Steuerung von RV WEI und PU WEI
			// Steuerungsfälle

			if ((wed[0].chbz_Quellenanhebung > 0 || wed[0].chbz_Hoch_QRG > 0 || wed[0].chbz_Nieder_QRG > 0) && TS5_[0]->stat == 0 && wes[0].ipa_Funktion_TP > 0)		
				Steuerungsfall_WEI = 1;
			if ((wed[0].chbz_Quellenanhebung > 0 || wed[0].chbz_Hoch_QRG > 0 || wed[0].chbz_Nieder_QRG > 0) && wes[0].ipa_Funktion_TP == 0)	
				Steuerungsfall_WEI = 2;
			if (wed[0].chbz_Quellenanhebung == 0 && wed[0].chbz_Hoch_QRG == 0 && wed[0].chbz_Nieder_QRG == 0)	
				Steuerungsfall_WEI = 3;
			
			switch (Steuerungsfall_WEI)
				{
					case 1:
						
							// Regelabweichung Soll - Ist
							fl_ei	= -wed[0].fl_tsol + (float)TS5_[0]->messw / 10;
							
							// -------------- PID-Regelalgorithmus ---------------------------------
							// Berechnung der relativen Stellgrößen
							fl_dy_rel = Dy_rel ( wes[0].Kp, wes[0].Kd, wes[0].Ts, wes[0].Tn, 
																			fl_ei, wed[0].fl_ei1, wed[0].fl_ei2 );
 	
							wed[0].fl_y_rel += fl_dy_rel;
							
							wed[0].dy_rel	= (int)(fl_dy_rel * 1000);					// für debug
 	
							//---------------------------------------------------------------------
							// Regelabweichungen merken
							wed[0].fl_ei2 = wed[0].fl_ei1;
							wed[0].fl_ei1 = fl_ei;						
							// Parameterumwandlung float to int
							wed[0].ei = (int)(fl_ei * 10);											// [0,1%] zur Anzeige
							                            
								// Ausgabe an 0-10V Ventil                                               
	                                                                         
								// Begrenzung der PID-Stellgröße (anti windup) auf Kp * ei (gleitend) ode
								wed[0].fl_y_rel = anti_windup( wed[0].fl_y_rel, wes[0].Kp, wes[0].Wup,  fl_ei );		// in Funktion.c 
								wed[0].si_y_rel = (int)(wed[0].fl_y_rel * 10);		// debug                 
								                                                                         
								// Abfrage Ventilstellungsbegrenzungen			                             
								if(wes[0].Y_rel_beg > 0)													// Ventilöffnungsbeginn g
								{                                                                        
									if(fl_dy_rel > 1)															// nur bei positiver Ände
									{	if(wed[0].fl_y_rel < fl_Y_rel_beg)						// und Wert kleiner als V
											 wed[0].fl_y_rel = fl_Y_rel_beg;						// dann Setzen auf Ventil
									}                                                                      
								}	                                                                       
								if(wes[0].Y_rel_min > 0)													// Minimalbegrenzung gese
								{			                                                                   
									if(wed[0].fl_y_rel  < fl_Y_rel_min)						// Wert kleiner als Minim
										 wed[0].fl_y_rel  = fl_Y_rel_min;						// dann setzen auf Minima
								}		                                                                     
									                                                                       
								// Ausgabe der PID-Stellgröße als Stellsignal an den Systemausgang mit Be
								wed[0].y_rel = y_stell(wed[0].fl_y_rel);					// in Funktion.c         
 							 
 							 
 							  if (wes[0].chpa_rv_Hau == 0)
 							   	{                                                                       
										AA_UNI[U5]->awert = wed[0].y_rel;									// Ausgabe an Stellventil   
									}
								
								if (wes[0].chpa_pu_Hau == 0)
									{
										DA_UNI[U3]->wert = 1;
									}
						break;						
						
						case 2:
						
									wed[0].tvsb = 0;
									
							  if (wes[0].chpa_rv_Hau == 0)
 							   	{                                                                       
										AA_UNI[U5]->awert = 100;									// Ausgabe an Stellventil   
									}
								
								if (wes[0].chpa_pu_Hau == 0)
									{
										DA_UNI[U3]->wert = 1;
									}
						break;
						
						case 3:
						
									wed[0].tvsb = 0;
									
							  if (wes[0].chpa_rv_Hau == 0)
 							   	{                                                                       
										AA_UNI[U5]->awert = 0;									// Ausgabe an Stellventil   
									}
								
								if (wes[0].chpa_pu_Hau == 0)
									{
										DA_UNI[U3]->wert = 0;
									}
						break;
						
				}
/*------------------------Steuerung des Quellenkreis------------------------*/

// Handbetrieb Quellenpumpe PU QU 
if (qus[0].chpa_pu_Hau > 0)
	{
		DA_UNI[U2]->wert = qus[0].chpa_pu_ein;
	}	

// Handbetrieb Regelventil RV QU 
if (qus[0].chpa_rv_Hau > 0)
	{
		AA_UNI[U6]->awert = qus[0].ipa_rv_stellung;
	}

// Betriebszustände
		// 6. Wärmepumpenversorgung
		if (qud[0].chbz_Freigabe_wpu > 0 || qud[0].chbm_WPU > 0)
			{
				qud[0].chbz_WPU_Versorgung = 1;
			}
			else
				{
					qud[0].chbz_WPU_Versorgung = 0;
				}
		
			// Steuerung von RV QU und PU QU
			// Steuerungsfälle

			if ( 	(qud[0].chbz_WPU_Versorgung == 0 && wed[0].chbz_Hoch_QRG == 0 && wed[0].chbz_Nieder_QRG == 0) 
					|| wed[0].chbz_eTankschutz > 0 )		
				Steuerungsfall_QU = 3;
			if ((wed[0].chbz_Hoch_QRG > 0 || wed[0].chbz_Nieder_QRG > 0) && qud[0].chbz_WPU_Versorgung == 0 )
				Steuerungsfall_QU = 2;
			if (qud[0].chbz_WPU_Versorgung > 0)
				Steuerungsfall_QU = 1;
				
				switch (Steuerungsfall_QU)
				{
					case 1:
					
					// Sollwertberechnung für RV QU
							qud[0].tvsb = qus[0].ipa_Sollwert_WPU_VL;
					// Dämpfung des berechneten Sollwertes: tvsb --> gedämpfte tsol
							if( qud[0].regstart == 0) 	// nach Reset oder bei gleit. WW-Vorrang
							{	 qud[0].tsol			= qud[0].tvsb;												// keine Filterung
								 qud[0].fl_tsol	= (float)qud[0].tsol / 10;
								 qud[0].regstart	= 1;
							}	 
							else
							{
								qud[0].fl_tsol = g_filter(qud[0].fl_tsol, qud[0].tvsb, qus[0].Ts, qus[0].Fzk);
								qud[0].tsol 	  = (int)(qud[0].fl_tsol * 10);					// für Anzeige
							}
							
							// Regelabweichung Soll - Ist
							fl_ei	= qud[0].fl_tsol - (float)TP_UNI[U2]->messw / 10;
							
							// -------------- PID-Regelalgorithmus ---------------------------------
							// Berechnung der relativen Stellgrößen
							fl_dy_rel = Dy_rel ( qus[0].Kp, qus[0].Kd, qus[0].Ts, qus[0].Tn, 
																			fl_ei, qud[0].fl_ei1, qud[0].fl_ei2 );
 	
							qud[0].fl_y_rel += fl_dy_rel;
							
							qud[0].dy_rel	= (int)(fl_dy_rel * 1000);					// für debug
 	
							//---------------------------------------------------------------------
							// Regelabweichungen merken
							qud[0].fl_ei2 = qud[0].fl_ei1;
							qud[0].fl_ei1 = fl_ei;						
							// Parameterumwandlung float to int
							qud[0].ei = (int)(fl_ei * 10);											// [0,1%] zur Anzeige
							                            
								// Ausgabe an 0-10V Ventil                                               
	                                                                         
								// Begrenzung der PID-Stellgröße (anti windup) auf Kp * ei (gleitend) ode
								qud[0].fl_y_rel = anti_windup( qud[0].fl_y_rel, qus[0].Kp, qus[0].Wup,  fl_ei );		// in Funktion.c 
								qud[0].si_y_rel = (int)(qud[0].fl_y_rel * 10);		// debug                 
								                                                                         
								// Abfrage Ventilstellungsbegrenzungen			                             
								if(qus[0].Y_rel_beg > 0)													// Ventilöffnungsbeginn g
								{                                                                        
									if(fl_dy_rel > 1)															// nur bei positiver Ände
									{	if(qud[0].fl_y_rel < fl_Y_rel_beg)						// und Wert kleiner als V
											 qud[0].fl_y_rel = fl_Y_rel_beg;						// dann Setzen auf Ventil
									}                                                                      
								}	                                                                       
								if(qus[0].Y_rel_min > 0)													// Minimalbegrenzung gese
								{			                                                                   
									if(qud[0].fl_y_rel  < fl_Y_rel_min)						// Wert kleiner als Minim
										 qud[0].fl_y_rel  = fl_Y_rel_min;						// dann setzen auf Minima
								}		                                                                     
									                                                                       
								// Ausgabe der PID-Stellgröße als Stellsignal an den Systemausgang mit Be
								qud[0].y_rel = y_stell(qud[0].fl_y_rel);					// in Funktion.c         
 							 
 							 
 							   if (qus[0].chpa_rv_Hau == 0)
 							   	{                                                                       
										AA_UNI[U6]->awert = qud[0].y_rel;									// Ausgabe an Stellventil   
									}
								
								if (qus[0].chpa_pu_Hau == 0)
									{
										DA_UNI[U2]->wert = 1;
									}
						
						
					break;
					case 2:
								// Sollwertberechnung für RV QU
									qud[0].tvsb = 0;
						
								 if (qus[0].chpa_rv_Hau == 0)
 							   	{                                                                       
										AA_UNI[U6]->awert = 1000;									// Ausgabe an Stellventil   
									}
								
								if (qus[0].chpa_pu_Hau == 0)
									{
										DA_UNI[U2]->wert = 1;
									}
									
					break;
					case 3:
						
								// Sollwertberechnung für RV QU
									qud[0].tvsb = 0;

								if (qus[0].chpa_rv_Hau == 0)
 							   	{                                                                       
										AA_UNI[U6]->awert = 0;									// Ausgabe an Stellventil   
									}
								
								if (qus[0].chpa_pu_Hau == 0)
									{
										DA_UNI[U2]->wert = 0;
									}
					break;
					//default:
				}
}	// Ende Steuer_QRG
		
 
