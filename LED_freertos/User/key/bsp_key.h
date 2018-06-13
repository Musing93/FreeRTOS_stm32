#ifndef __KEY_H
#define __KEY_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "list.h"

#define KEY1_PIN               GPIO_Pin_0
#define KEY1_GPIO_PORT         GPIOA
#define KEY1_GPIO_CLK          RCC_AHB1Periph_GPIOA


#define KEY2_PIN               GPIO_Pin_13
#define KEY2_GPIO_PORT         GPIOC
#define KEY2_GPIO_CLK          RCC_AHB1Periph_GPIOC


#define KEY_ON                 1
#define KEY_OFF                0

void Key_Delay(volatile u32 nCount);
void Key_GPIO_Config(void);
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin);

#endif /*__KEY_H*/

