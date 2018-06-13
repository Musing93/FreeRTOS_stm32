#include "./key/bsp_key.h"

//假延时
void Key_Delay(volatile u32 nCount)
{
	for(; nCount != 0; nCount--)
	{
	}
}

void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef    GPIO_InitStructure;
	
	//开启时钟
	RCC_AHB1PeriphClockCmd (KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE);
	
	//选择按键引脚
	GPIO_InitStructure.GPIO_Pin =KEY1_PIN;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN;//输入模式
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;//不上拉也不下拉
	//初始化KEY1
	GPIO_Init(KEY1_GPIO_PORT,&GPIO_InitStructure);
	//选择按键引脚
	GPIO_InitStructure.GPIO_Pin =KEY2_PIN;
	GPIO_Init(KEY2_GPIO_PORT,&GPIO_InitStructure);
}
//扫描按键
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON)//=1
	{
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin)==KEY_ON);
		return KEY_ON;
		
	}else
		return KEY_OFF;
}

