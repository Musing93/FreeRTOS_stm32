#include "./usart/USART.h"   
//�ж� Ϊ ������ ����Ϊ10
//�����ж�NVIC
static void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_Structure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);//��λȫ�����ȼ�
	
	NVIC_Structure.NVIC_IRQChannel=USART2_IRQ;
	NVIC_Structure.NVIC_IRQChannelPreemptionPriority=10;//��ռ���ȼ�����Ϊ10
	NVIC_Structure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Structure.NVIC_IRQChannelSubPriority=0;
	
	NVIC_Init(&NVIC_Structure);
}


//���ô���
void USART2_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	RCC_AHB1PeriphClockCmd(USART2_RX_GPIO_CLK|USART2_TX_GPIO_CLK,ENABLE);//ʹ�ܶ˿�ʱ�� 
	RCC_APB1PeriphClockCmd(USART2_CLK,ENABLE);//ʹ��USARTʱ��
	
	//����PX.x��USARTx_TX
	GPIO_PinAFConfig(USART2_RX_GPIO_PORT,USART2_RX_SOURCE,USART2_RX_AF);
	GPIO_PinAFConfig(USART2_TX_GPIO_PORT,USART2_TX_SOURCE,USART2_TX_AF);
	
	//GPIO��ʼ��
	//RX TX��ͬ����
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;//���������
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	//RX GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin=USART2_RX_PIN;
	GPIO_Init(USART2_RX_GPIO_PORT,&GPIO_InitStructure);

	//TX GPIO��ʼ��
	GPIO_InitStructure.GPIO_Pin=USART2_TX_PIN;
	GPIO_Init(USART2_TX_GPIO_PORT,&GPIO_InitStructure);	
	
	USART_InitStructure.USART_BaudRate=USART2_BAUDRATE;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None ;
	USART_InitStructure.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_InitStructure.USART_Parity=USART_Parity_No;//��ʹ��У��
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	//��ʼ��USART
	USART_Init(USART2,&USART_InitStructure);
	
	NVIC_Configuration();
	
	//�����ж�ʹ��
	USART_ITConfig(USART2,USART_IT_RXNE,ENABLE);
	
	//����ʹ��
	USART_Cmd(USART2,ENABLE);
	
}


/*****************  ����һ���ַ� **********************/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch )
{
	/* ����һ���ֽ����ݵ�USART1 */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ�������� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

/*****************  ָ�����ȵķ����ַ��� **********************/
void Usart_SendStr_length( USART_TypeDef * pUSARTx, uint8_t *str,uint32_t strlen )
{
	unsigned int k=0;
    do 
    {
        Usart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(k < strlen);
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, uint8_t *str)
{
	unsigned int k=0;
    do 
    {
        Usart_SendByte( pUSARTx, *(str + k) );
        k++;
    } while(*(str + k)!='\0');
}
/****USART2 �ض���fprint����****/
int fputc(int ch,FILE *f)
{
	USART_SendData(USART2,ch);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);//�ȴ��������
	
	return ch;
	
}




