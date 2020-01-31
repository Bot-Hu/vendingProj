#include "delay.h"
#include "USART3.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	   
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK STM32������
//����2��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/29
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

//���ڷ��ͻ����� 	
__align(8) u8 UART5_TX_BUF[UART5_MAX_SEND_LEN]; 	//���ͻ���,���UART5_MAX_SEND_LEN�ֽ�
#ifdef UART5_RX_EN   								//���ʹ���˽���   	  
//���ڽ��ջ����� 	
u8 UART5_RX_BUF[UART5_MAX_RECV_LEN]; 				//���ջ���,���UART5_MAX_RECV_LEN���ֽ�.


//ͨ���жϽ�������2���ַ�֮���ʱ������10ms�������ǲ���һ������������.
//���2���ַ����ռ������10ms,����Ϊ����1����������.Ҳ���ǳ���10msû�н��յ�
//�κ�����,���ʾ�˴ν������.
//���յ�������״̬
//[15]:0,û�н��յ�����;1,���յ���һ������.
//[14:0]:���յ������ݳ���
u16 UART5_RX_STA=0;   	 
void UART5_IRQHandler(void)
{
	u8 res;	    
if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET)//���յ�����
	{	 
		res =USART_ReceiveData(UART5);				 
		if(UART5_RX_STA<UART5_MAX_RECV_LEN)		//�����Խ�������
		{
		  TIM_SetCounter(TIM3,0);//���������      
			if(UART5_RX_STA==0)TIM3_Set(1);	 	//ʹ�ܶ�ʱ��4���ж� 
			UART5_RX_BUF[UART5_RX_STA++]=res;		//��¼���յ���ֵ	 
		}else 
		{
			UART5_RX_STA|=1<<15;					//ǿ�Ʊ�ǽ������
		} 
	}  											 
}   
//��ʼ��IO ����3
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void UART5_Init(u32 bound)
{ 	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	 //��ʱ��
	
	/*  ����GPIO��ģʽ��IO�� */
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;//TX			   //�������PB10
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;	    //�����������
	GPIO_Init(GPIOB,&GPIO_InitStructure);  /* ��ʼ����������IO */
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;//RX			 //��������PB11
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;		  //ģ������
	GPIO_Init(GPIOB,&GPIO_InitStructure); /* ��ʼ��GPIO */
	
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ
  
	USART_Init(UART5, &USART_InitStructure); //��ʼ������	3
  
	//����������
 //	USART2->BRR=(pclk1*1000000)/(bound);// ����������	 
	//USART2->CR1|=0X200C;  	//1λֹͣ,��У��λ.
	USART_DMACmd(UART5,USART_DMAReq_Tx,ENABLE);  	//ʹ�ܴ���3��DMA����
	UART_DMA_Config(DMA2_Channel2,(u32)&UART5->DR,(u32)UART5_TX_BUF);//DMA2ͨ��2,����Ϊ����3,�洢��ΪUART5_TX_BUF 
	USART_Cmd(UART5, ENABLE);                    //ʹ�ܴ��� 
	
#ifdef UART5_RX_EN		  	//���ʹ���˽���
	//ʹ�ܽ����ж�
  USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//�����ж�   
	
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	TIM3_Init(99,7199);		//10ms�ж�
	UART5_RX_STA=0;		//����
	TIM3_Set(0);			//�رն�ʱ��3
#endif	 									  	
}

void uart3_send(u8* buf,u32 num)
{
	u32 i;
	for(i=0;i<num;i++)
	{
		while(!(UART5->SR & (1<<7)));
		UART5->DR = buf[i];
	}

}
//����3,printf ����
//ȷ��һ�η������ݲ�����UART5_MAX_SEND_LEN�ֽ�
void u3_printf(char* fmt,...)  
{  
	va_list ap;
	va_start(ap,fmt);
	vsprintf((char*)UART5_TX_BUF,fmt,ap);
	va_end(ap);
//	while(DMA1_Channel7->CNDTR!=0);	//�ȴ�ͨ��7�������   
//	UART_DMA_Enable(DMA1_Channel2,strlen((const char*)UART5_TX_BUF)); 	//ͨ��dma���ͳ�ȥ
	uart3_send(UART5_TX_BUF,strlen((const char*)UART5_TX_BUF));
}


//��ʱ��4�жϷ������		    
void TIM3_IRQHandler(void)
{ 	
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)//�Ǹ����ж�
	{	 			   
		UART5_RX_STA|=1<<15;	//��ǽ������
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx�����жϱ�־    
		TIM3_Set(0);			//�ر�TIM3  
	}   
}
//����TIM4�Ŀ���
//sta:0���ر�;1,����;
void TIM3_Set(u8 sta)
{
	if(sta)
	{
       
		TIM_SetCounter(TIM3,0);//���������
		TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx	
	}else TIM_Cmd(TIM3, DISABLE);//�رն�ʱ��3
}
//ͨ�ö�ʱ���жϳ�ʼ��
//����ʼ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ��
//psc��ʱ��Ԥ��Ƶ��		 
void TIM3_Init(u16 arr,u16 psc)
{	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��//TIM4ʱ��ʹ��    
	
	//��ʱ��TIM3��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE ); //ʹ��ָ����TIM4�ж�,���������ж�

	 	  
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
}
#endif		 
/////////////////////////////////////////USART2 DMA�������ò���//////////////////////////////////	   		    
////DMA1�ĸ�ͨ������
////����Ĵ�����ʽ�ǹ̶���,���Ҫ���ݲ�ͬ��������޸�
////�Ӵ洢��->����ģʽ/8λ���ݿ���/�洢������ģʽ
////DMA_CHx:DMAͨ��CHx
////cpar:�����ַ
////cmar:�洢����ַ    
//void UART_DMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar)
//{
//	DMA_InitTypeDef DMA_InitStructure;
// 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);	//ʹ��DMA����
//  DMA_DeInit(DMA_CHx);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
//	DMA_InitStructure.DMA_PeripheralBaseAddr = cpar;  //DMA����ADC����ַ
//	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA�ڴ����ַ
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;  //���ݴ��䷽�򣬴��ڴ��ȡ���͵�����
//	DMA_InitStructure.DMA_BufferSize = 0;  //DMAͨ����DMA����Ĵ�С
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  //���ݿ���Ϊ8λ
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte; //���ݿ���Ϊ8λ
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  //��������������ģʽ
//	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
//	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
//	DMA_Init(DMA_CHx, &DMA_InitStructure);  //����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��USART1_Tx_DMA_Channel����ʶ�ļĴ���	
//} 
////����һ��DMA����
//void UART_DMA_Enable(DMA_Channel_TypeDef*DMA_CHx,u16 len)
//{
//	DMA_Cmd(DMA_CHx, DISABLE );  //�ر� ָʾ��ͨ��        
//	DMA_SetCurrDataCounter(DMA_CHx,len);//DMAͨ����DMA����Ĵ�С	
//	DMA_Cmd(DMA_CHx, ENABLE);           //����DMA����
//}	   
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// 									 




















