#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "list.h"
#include "semphr.h"
#include "my_include.h"
//ȫ�ֶ���
xQueueHandle xQueue;
//������ֵ�ź��������Ϊ��
SemaphoreHandle_t  Binary_USART=NULL;

extern uint8_t RxFlag;
//������
TaskHandle_t xHandleTaskLed1;
TaskHandle_t xHandleTaskKey;
TaskHandle_t xHandleUSART;
//����Led1 ��˸���� 1s
static void vTaskCMD(void *pvParameters)
{
	//LED1_ON;
	BaseType_t err=pdFAIL;
	Binary_USART=xSemaphoreCreateBinary();//������ֵ��,��ʱBinary_USART�ǿ�
	while(1)
	{
		if(Binary_USART!=NULL)//�ǿ�
		{
			printf("�ȴ���ֵ�ź�\n");
			err=xSemaphoreTake(Binary_USART,portMAX_DELAY);//portMAX_DELAY
			printf("��ö�ֵ�ź�\n");			
		}		
	}	
}

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


//����key1 2 ,0.03��ɨ��һ��,key1���� LED�������Key2���£�����ָ�
static void vTaskKey(void *pvParameters)
{
	while(1)
	{
		if(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN)==KEY_ON)
		{
			while(Key_Scan(KEY1_GPIO_PORT,KEY1_PIN)==KEY_ON)
				;//�ȴ������ſ�
			xSemaphoreGive(Binary_USART);
			//vTaskSuspend(xHandleTaskLed1);
		}
		if(Key_Scan(KEY2_GPIO_PORT,KEY2_PIN)==KEY_ON)
		{
			while(Key_Scan(KEY2_GPIO_PORT,KEY2_PIN)==KEY_ON)
				;//�ȴ������ſ�
			xSemaphoreGive(Binary_USART);
			//vTaskResume(xHandleTaskLed1);
		}
		vTaskDelay(30);//����
	}
}

//���з�������
static void vTaskSender(void *Value)//�������Ϊ����Ҫ���͵�ֵ
{
	long lValueToSend;
	lValueToSend=(long) Value;
	portBASE_TYPE xStatus;
	
//	uint8_t pcWriteBuffer[500];
	
	while(1)
	{
		xStatus=xQueueSendToBack(xQueue,&lValueToSend,1000);
		if(xStatus!=pdPASS)//���Ͳ��ɹ�
		{
			//printf("sender wait \n");
		}
	}	
}
//���н�������
static void vTaskReceiver(void *pvParameters)
{
		long lReceiveValue;
		portBASE_TYPE xStatus;
		const portTickType wait_time=1000/portTICK_PERIOD_MS;//�趨ʱ��Ϊ100ms
		while(1)
		{
//			if(uxQueueMessagesWaiting(xQueue)!=0)//������в�Ϊ��
//					Usart_SendString(USART2,(uint8_t *)"������������δ����ȡ");
			
			xStatus=xQueueReceive(xQueue,&lReceiveValue,wait_time);
			
			if(xStatus==pdPASS)//1,��ȡ�ɹ�
			{
					printf("The rec data is %ld \n",lReceiveValue);
			}
//			else 
//					Usart_SendString(USART2,(uint8_t *)"read fail\n");		
		}
}


//�������
void APPTaskCreate(void)
{
		xTaskCreate(vTaskCMD,"Task USART CMD",300,NULL,6,&xHandleUSART);//USART ��ֵ������LED
//		xTaskCreate(vTaskLed1,"Task Led1",300,NULL,4,&xHandleTaskLed1);//Led1����
		xTaskCreate(vTaskKey,"Task Key",512,NULL,5,&xHandleTaskKey);//key����
//		xTaskCreate(vTaskSender,"Task queue sender1",1000,(void *)100,8,NULL);//queue���� ���������Ϊ100
//		xTaskCreate(vTaskSender,"Task queue sender2",1000,(void *)200,8,NULL);//queue���� ���������Ϊ100
//		xTaskCreate(vTaskReceiver,"Task queue receive",1000,NULL,9,NULL);//queue ��������
}
