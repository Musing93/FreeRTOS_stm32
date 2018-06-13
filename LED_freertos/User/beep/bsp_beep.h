#ifndef __BEEP_H
#define __BEEP_H

#include "stm32f4xx.h"
#define  BEEP_PIN  					GPIO_Pin_11
#define  BEEP_GPIO_PORT 		GPIOI
#define  BEEP_CLK           RCC_AHB1Periph_GPIOI

void BEEP_GPIO_Config(void);
#define  BEEP_ON            	{BEEP_GPIO_PORT->BSRRL=BEEP_PIN;}
#define  BEEP_OFF						  {BEEP_GPIO_PORT->BSRRH=BEEP_PIN;}
#define  BEEP_ON_1             GPIO_SetBits(BEEP_GPIO_PORT,BEEP_PIN)
#define  BEEP_OFF_1            GPIO_ResetBits(BEEP_GPIO_PORT,BEEP_PIN)
#endif

