
#include "lpc17xx_i2c.h"
#include <stdint.h>
//#include <stdlib.h>

//===========================================
// initialisation de la mémoire i2c
//===========================================
void init_i2c_eeprom() {
	I2C_Init(LPC_I2C0, 100000);
	I2C_Cmd(LPC_I2C0, ENABLE);
}

//===========================================
// Ecriture dans la mémoire i2c
//===========================================
void i2c_eeprom_write(uint8_t addr, uint8_t data) {
	I2C_M_SETUP_Type i2cSetup;
	uint8_t dataAndReg[2];
	dataAndReg[0] = addr;
	dataAndReg[1] = data;
	
	i2cSetup.sl_addr7bit = 0x51;
	i2cSetup.tx_data = dataAndReg;
  i2cSetup.tx_length = 2;
	
  i2cSetup.rx_data = NULL;
  i2cSetup.rx_length = 0;
  i2cSetup.retransmissions_max = 10;
	i2cSetup.callback = NULL;
	
	I2C_MasterTransferData(LPC_I2C0, &i2cSetup, I2C_TRANSFER_POLLING);
}

//===========================================
// Lecture dans la mémoire i2c
//===========================================
Status i2c_eeprom_read(uint8_t addr, uint8_t* data_recup) {
    I2C_M_SETUP_Type setupi2c;
    
    setupi2c.sl_addr7bit = 0x51; 
    setupi2c.tx_data = &addr; // on se pointe sans rien ecrire
    setupi2c.tx_length = 1;	// avec que 1 de len
    setupi2c.rx_data = data_recup;	// on se pointe pareil mais en mode ecriture
    setupi2c.rx_length = 1;	// on lit que 1 data
    
    I2C_MasterTransferData(LPC_I2C0, &setupi2c, I2C_TRANSFER_POLLING);
}
