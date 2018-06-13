#include "./usart/USART.h"   
//中断 为 第四组 配置为10
//配置中断NVIC
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_Structure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//四位全做优先级
	
	NVIC_Structure.NVIC_IRQChannel=USART2_IRQ;
	NVIC_Structure.NVIC_IRQChannelPreemptionPriority=10;//抢占优先级设置为10
	NVIC_Structure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Structure.NVIC_IRQChannelSubPriority=0;
	
	NVIC_Init(&NVIC_Structure);
}


//配置串口
void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_AHB1PeriphClockCmd(USART2_RX_GPIO_CLK|USART2_TX_GPIO_CLK,ENABLE);//使能端口时钟 
	RCC_APB1PeriphClockCmd(USART2_CLK,ENABLE);//使能USART时钟
	
	//连接PX.x到USARTx_TX
	GPIO_PinAFConfig(USART2_RX_GPIO_PORT,USART2_RX_SOURCE,USART2_RX_AF);
	GPIO_PinAFConfig(USART2_TX_GPIO_PORT,USART2_TX_SOURCE,USART2_TX_AF);
	
	//GPIO初始化
	//RX TX相同部分
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//推挽输出、
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	//RX GPIO初始化
	GPIO_InitStructure.GPIO_Pin=USART2_RX_PIN;
	GPIO_Init(USART2_RX_GPIO_PORT,&GPIO_InitStructure);

	//TX GPIO初始化
	GPIO_InitStructure.GPIO_Pin=USART2_TX_PIN;
	GPIO_Init(USART2_TX_GPIO_PORT,&GPIO_InitStructure);	
	
	USART_InitStructure.USART_BaudRate=USART2_BAUDRATE;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None ;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;//不使用校验
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	//初始化USART
	USART_Init(USART2,&USART_InitStructure);
	
	NVIC_Configuration();
	
	//串口中断使能
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	
	//串口使能
	USART_Cmd(USART2,ENABLE);
	
}


/*****************  发送一个字符 **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch )
{
	/* 发送一个字节数据到USART1 */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送完毕 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  指定长度的发送字符串 **********************/
void Usart_SendStr_length( USART_TypeDef * pUSARTx, uint8_t *str,uint32_t strlen )
{
	unsigned int k=0;
    do 
    {
        Usart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(k < strlen);
}

/*****************  发送字符串 **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, uint8_t *str)
{
	unsigned int k=0;
    do 
    {
        Usart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(*(str + k)!='\0');
}
/****USART2 重定向到fprint函数****/
int fputc(int ch,FILE *f)
{
	USART_SendData(USART2,ch);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);//等待发送完成
	
	return ch;
	
}




