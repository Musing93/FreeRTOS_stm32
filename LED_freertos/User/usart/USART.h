#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h"
#include <stdio.h>
//USART1≈‰÷√
#define USART1_CLK                 RCC_APB2Periph_USART1
#define USART1_BAUDRATE            115200

//≈‰÷√RX±√˚
#define USART1_RX_GPIO_PORT         GPIOA
#define USART1_RX_PIN								GPIO_Pin_10
#define USART1_RX_GPIO_CLK					RCC_AHB1Periph_GPIOA
#define USART1_RX_AF 								GPIO_AF_USART1
#define USART1_RX_SOURCE						GPIO_PinSource10
//≈‰÷√TX±√˚
#define USART1_TX_GPIO_PORT         GPIOA
#define USART1_TX_PIN								GPIO_Pin_9
#define USART1_TX_GPIO_CLK					RCC_AHB1Periph_GPIOA
#define USART1_TX_AF 								GPIO_AF_USART1
#define USART1_TX_SOURCE						GPIO_PinSource9

//≈‰÷√÷–∂œ
#define USARTx_IRQHandler           USART1_IRQHandler
#define USART1_IRQ									USART1_IRQn


//≈‰÷√USART2
#define USART2_CLK                 RCC_APB1Periph_USART2
#define USART2_BAUDRATE            115200

#define USART2_RX_GPIO_PORT                GPIOD
#define USART2_RX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define USART2_RX_PIN                      GPIO_Pin_6
#define USART2_RX_AF                       GPIO_AF_USART2
#define USART2_RX_SOURCE                   GPIO_PinSource6

#define USART2_TX_GPIO_PORT                GPIOD
#define USART2_TX_GPIO_CLK                 RCC_AHB1Periph_GPIOD
#define USART2_TX_PIN                      GPIO_Pin_5
#define USART2_TX_AF                       GPIO_AF_USART2
#define USART2_TX_SOURCE                   GPIO_PinSource5

//USART÷–∂œ
#define USART2_IRQHandler1  					       USART2_IRQHandler 
#define USART2_IRQ                         USART2_IRQn


void USART2_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch );
void Usart_SendStr_length( USART_TypeDef * pUSARTx, uint8_t *str,uint32_t strlen );
void Usart_SendString( USART_TypeDef * pUSARTx, uint8_t *str);



#endif

