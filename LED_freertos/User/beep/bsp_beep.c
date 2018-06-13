//控制蜂鸣器

#include "./beep/bsp_beep.h"

void BEEP_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(BEEP_CLK,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;//输出
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出
	GPIO_InitStructure.GPIO_Pin=BEEP_PIN;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_2MHz ;
	
	GPIO_Init(BEEP_GPIO_PORT,&GPIO_InitStructure);
	GPIO_ResetBits(BEEP_GPIO_PORT,BEEP_PIN);
}

