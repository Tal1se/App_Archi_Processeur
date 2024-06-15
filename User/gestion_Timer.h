#ifndef __gestion_Timer_H__
#define __gestion_Timer_H__

#include "lpc17xx_timer.h"

void TIMER0_IRQHandler(void);
void initTimer();
void greenButton();
void redButton();
void yellowButton();
void pinkButton();

#endif
