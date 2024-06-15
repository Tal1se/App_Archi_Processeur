#ifndef __gestion_I2C_H__
#define __gestion_I2C_H__

#include "lpc17xx_timer.h"

void init_i2c_eeprom();
void i2c_eeprom_write(uint8_t addr, uint8_t data);
void i2c_eeprom_read(uint8_t addr, uint8_t *data);

#endif

