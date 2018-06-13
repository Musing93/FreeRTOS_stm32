#include "./task/bsp_task.h"
#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "list.h"
#include "my_include.h"
//全局队列
xQueueHandle xQueue;

//任务句柄
TaskHandle_t xHandleTaskLed1;
TaskHandle_t xHandleTaskKey;
//任务Led1 闪烁周期 1s
static void vTaskLed1(void *pvParameters)
{
	//uint8_t pcWriteBuffer[500];
	while(1)
	{
		LED1_ON;
		vTaskDelay(500);
		LED1_OFF;
		vTaskDelay(500);
		
//		vTaskList((char *)&pcWriteBuffer);
//		printf("tsak                state   priority   stacks_remain NO\r\n");
//    printf("%s\r\n", pcWriteBuffer);
//		printf("*********");
		
	}
}


//任务key1 2 ,0.03秒扫描一次,key1按下 LED任务挂起，Key2按下，任务恢复
static void vTaskKey(void *pvParameters)
{
	while(1)
	{
		if(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN)==KEY_ON)
		{
			while(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN)==KEY_ON)
				;//等待按键放开
			vTaskSuspend(xHandleTaskLed1);
		}
		if(Key_Scan(KEY2_GPIO_PORT,KEY2_PIN)==KEY_ON)
		{
			while(Key_Scan(KEY2_GPIO_PORT,KEY2_PIN)==KEY_ON)
				;//等待按键放开
			vTaskResume(xHandleTaskLed1);
		}
		vTaskDelay(30);//阻塞
	}
}

//队列发送任务
static void vTaskSender(void *Value)//输入参数为队列要发送的值
{
	long lValueToSend;
	lValueToSend=(long) Value;
	portBASE_TYPE xStatus;
	
//	uint8_t pcWriteBuffer[500];
	
	while(1)
	{
		xStatus=xQueueSendToBack(xQueue,&lValueToSend,1000);
		if(xStatus!=pdPASS)//发送不成功
		{
			//printf("sender wait \n");
		}
	}	
}
//队列接收任务
static void vTaskReceiver(void *pvParameters)
{
		long lReceiveValue;
		portBASE_TYPE xStatus;
		const portTickType wait_time=1000/portTICK_PERIOD_MS;//设定时间为100ms
		while(1)
		{
//			if(uxQueueMessagesWaiting(xQueue)!=0)//如果队列不为空
//					Usart_SendString(USART2,(uint8_t *)"队列中有数据未被读取");
			
			xStatus=xQueueReceive(xQueue,&lReceiveValue,wait_time);
			
			if(xStatus==pdPASS)//1,读取成功
			{
					printf("The rec data is %ld \n",lReceiveValue);
			}
//			else 
//					Usart_SendString(USART2,(uint8_t *)"read fail\n");		
		}
}


//任务汇总
void APPTaskCreate(void)
{
		xTaskCreate(vTaskLed1,"Task Led1",300,NULL,4,&xHandleTaskLed1);//Led1任务
		xTaskCreate(vTaskKey,"Task Key",512,NULL,5,&xHandleTaskKey);//key任务
//		xTaskCreate(vTaskSender,"Task queue sender1",1000,(void *)100,8,NULL);//queue任务 ，传入参数为100
//		xTaskCreate(vTaskSender,"Task queue sender2",1000,(void *)200,8,NULL);//queue任务 ，传入参数为100
//		xTaskCreate(vTaskReceiver,"Task queue receive",1000,NULL,9,NULL);//queue 接收任务
}
