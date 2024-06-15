//===========================================================//
// Projet Micro - INFO1 - ENSSAT - S2 2018							 //
//===========================================================//
// File                : Programme de départ
// Hardware Environment: Open1768	
// Build Environment   : Keil µVision
//===========================================================//

#include "touch\ili_lcd_general.h"
#include "touch\lcd_api.h"
#include "affichagelcd.h"
#include "touch\touch_panel.h"

#include "global.h"

#include "gestion_I2C.h"
#include "gestion_Timer.h" // include globaldec.h
#include "gestion_Pinsel.h"
#include "gestion_I2C.h"

char chaine_print[30];

#include <stdio.h>


//===========================================================//
// Function: when som1 tap the screen
//===========================================================//
void screenPat(){
	touch_read();
	if(touch_x >= 400 && touch_x <= 2000 && touch_y >= 2100 && touch_y <= 2650){ //restart the count !
		greenButton();
	} else if(touch_x >= 2000 && touch_x <= 3600 && touch_y >= 2100 && touch_y <= 2650){ //stop the count !
		redButton();
	}else if(touch_x >= 400 && touch_x <= 1000 && touch_y >= 1200 && touch_y <= 1700){ //stop the count !
		yellowButton();
	}else if(touch_x >= 400 && touch_x <= 1000 && touch_y >= 1200 && touch_y <= 1700){ //stop the count !
		yellowButton();
	}else if(touch_x >= 400 && touch_x <= 1000 && touch_y >= 700 && touch_y <= 1200){ //stop the count !
		pinkButton();
	}
}

//===========================================================//
// Function: Main
//===========================================================//
int main(void)
{	   
		uint16_t slaveAddr = 81;
		int data = 0x0070;
		int data_recup = 0x70;
	
	  lcd_Initializtion(); // init pinsel ecran et init LCD
		touch_init(); // init pavé tactile
		pin_Configuration(); // initialisation des broches
		initTimer();
		init_i2c_eeprom();
		
    dessiner_rect(10,170,110,50,2,1,Black,Green);
    dessiner_rect(120,170,110,50,2,1,Black,Red);
	  dessiner_rect(10,95,70,50,2,1,Black,Yellow);
		dessiner_rect(10,45,70,50,2,1,Black,0xFB56);
		
		sprintf(chaine_print,"%s","Start");
		LCD_write_english_string (1585,2750,chaine_print,Black,Green);
		
		sprintf(chaine_print,"%s","Stop");
		LCD_write_english_string (2200,2750,chaine_print,Black,Red);
		
		sprintf(chaine_print,"%s","Save");
		LCD_write_english_string (30,115,chaine_print,Black,Yellow);
		
		sprintf(chaine_print,"%s","Reset");
		LCD_write_english_string (30,65,chaine_print,Black,0xFB56);
		

	
	
    while(1) {
			touch_debug();
			if(TP_DOWN() && lcdPress == 0){
				lcdPress = 1; // ecran est appuyé
				screenPat();
			} else if (!TP_DOWN() && lcdPress == 1) {
				lcdPress = 0;
			}
		};
	};
//---------------------------------------------------------------------------------------------	
#ifdef  DEBUG
void check_failed(uint8_t *file, uint32_t line) {while(1);}
#endif
