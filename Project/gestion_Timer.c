#include "gestion_Timer.h"

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"
#include "lpc17xx_libcfg_default.h"
#include "lpc17xx_timer.h"

#include "affichagelcd.h"
#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"

#include <stdio.h>
#include <stdlib.h>
#include "globaldec.h"



#define precision 2500;
#define demie_periode 100;

uint8_t compteur = 0;
uint32_t port0 = 0;

uint16_t addrTimer = 0x81;
uint16_t addrCompteur = 0x82;

uint8_t data_recup;
uint8_t data_recup_compt = 0;

int nombre = 0x00;
uint8_t nombreAddr = 0;
uint8_t process = 1;
int i2c_processing = 0;

void i2c_eeprom_write(uint8_t addr, uint8_t data);
void i2c_eeprom_read(uint8_t addr, uint8_t* data_recup);

//==========================================
//Affiche ecran
//==========================================
void afficher_ecran() {
		i2c_eeprom_read(addrTimer, &data_recup);
		i2c_eeprom_read(addrCompteur, &data_recup_compt);
		
		sprintf(chaine,"nb save : %d    ", data_recup_compt);
		LCD_write_english_string (100,80,chaine,White,Blue);
		
	
		sprintf(chaine,"val mem : %d    ", data_recup);
		LCD_write_english_string (100,100,chaine,White,Blue);
		
		sprintf(chaine,"timer : %d    ", nombre);
		LCD_write_english_string (100,120,chaine,White,Blue);
}

//================================================
// Timer handler, pas besoin d'appel fonction
//================================================
void TIMER0_IRQHandler(void) {
    if(compteur == 100) {
        if(process == 1 && i2c_processing == 0) {	
					nombre = nombre+1;
			
					afficher_ecran();
					i2c_processing = 0;
				}
				compteur = 0;
				
    } else {
        compteur++;
    }
		
    TIM_ClearIntPending(LPC_TIM0, TIM_MR0_INT);
}

 
//==========================================
//Initialisation du timer
//==========================================
void initTimer() {
	PINSEL_CFG_Type configPinsel; // pour pin connect bloc 
	TIM_TIMERCFG_Type configTimer ; // pour timer mode et precision
	TIM_MATCHCFG_Type maconfigmatch ; // pour timer match
  // remplissage pour P1.28 sur MAT0.0
  configPinsel.Portnum=PINSEL_PORT_1;
  configPinsel.Pinnum=PINSEL_PIN_28;
  configPinsel.Funcnum=PINSEL_FUNC_3;
  configPinsel.Pinmode=0;
  configPinsel.OpenDrain=PINSEL_PINMODE_NORMAL;
  // appel de la fonction qui va initialiser les registres
  PINSEL_ConfigPin(&configPinsel);
	
	
  // remplissage pour choisir le mode timer et la precision
  configTimer.PrescaleOption = TIM_PRESCALE_TICKVAL; // valeur donnee en tick
  configTimer.PrescaleValue = 2500; //Pr�cision
  // appel de la fonction qui va initialiser les registres
  TIM_Init(LPC_TIM0,TIM_TIMER_MODE,&configTimer);
  // remplissage pour choisir les actions quand �a match
	

  maconfigmatch.ExtMatchOutputType= TIM_EXTMATCH_TOGGLE; // inverse la sortie a chaque match
  maconfigmatch.IntOnMatch = ENABLE; // pas d'interruption generee quand ca match
  maconfigmatch.StopOnMatch = DISABLE ;
  maconfigmatch.MatchChannel = 0; // on utilise MR0
  maconfigmatch.MatchValue = 100; // correspond a la duree d'une demie-periode 
  maconfigmatch.ResetOnMatch = ENABLE; // remet TC a 0 quand ca match
  // appel de la fonction qui va initialiser les registres
  TIM_ConfigMatch(LPC_TIM0,&maconfigmatch);
    
  NVIC_EnableIRQ(TIMER0_IRQn);
    
  // lancement du timer-compteur 
  TIM_Cmd(LPC_TIM0,ENABLE);
}

void greenButton() {
	process = 1;
	sprintf(chaine,"%s","Stop ");
	LCD_write_english_string (2200,2750,chaine,Black,Red);
	sprintf(chaine,"%s","Start  ");
	LCD_write_english_string (1585,2750,chaine,Black,Green);
			
	afficher_ecran();
}

void redButton() {
		if(process == 0) { // timer is not running
			sprintf(chaine,"%s","Start  ");
		  LCD_write_english_string (1585,2750,chaine,Black,Green);
			nombre = 0;
			
			afficher_ecran();
		} else {  //timer is running
			process = 0;
			
			sprintf(chaine,"%s","Reset");
		  LCD_write_english_string (2200,2750,chaine,Black,Red);
			sprintf(chaine,"%s","Restart");
		  LCD_write_english_string (1585,2750,chaine,Black,Green);
			afficher_ecran();
		}

}



void yellowButton(){
					data_recup_compt = data_recup_compt +1;
					i2c_eeprom_write(addrTimer,(uint8_t)nombre);
					i2c_eeprom_write(addrCompteur,data_recup_compt);
	        afficher_ecran();
					i2c_processing = 0;
}

void pinkButton(){
	data_recup_compt = 0;
	i2c_eeprom_write(addrCompteur,data_recup_compt);
	i2c_processing = 0;
}


