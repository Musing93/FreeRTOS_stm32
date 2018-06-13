#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "list.h"
#include "my_include.h"//自定义头文件库
extern xQueueHandle xQueue;
static void BSP_init(void);
uint8_t ucTemp=0;
uint8_t RxFlag=0;
int main(void)
{
	xQueue=xQueueCreate(5,sizeof(long));//创建队列	
	BSP_init();
	APPTaskCreate();
	vTaskStartScheduler();
	while(1);
		
}

//设备初始化
static void BSP_init(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);// 中断分组：第四组，4位全用于设置抢占优先级，0位由于响应优先级,中断中也要设置为第四组
	LED_GPIO_Config();
	Key_GPIO_Config();
	BEEP_GPIO_Config();
	USART2_Config();
}

