#ifndef __UART5_H
#define __UART5_H	 
#include "sys.h"  
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32������
//����2��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/29
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 	   

#define UART5_MAX_RECV_LEN		1024				//�����ջ����ֽ���
#define UART5_MAX_SEND_LEN		1024				//����ͻ����ֽ���
#define UART5_RX_EN 			1					//0,������;1,����.

extern u8  UART5_RX_BUF[UART5_MAX_RECV_LEN]; 		//���ջ���,���USART2_MAX_RECV_LEN�ֽ�
extern u8  UART5_TX_BUF[UART5_MAX_SEND_LEN]; 		//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
extern u16 UART5_RX_STA;   						//��������״̬

void UART5_Init(u32 bound);				//����2��ʼ�� 
void TIM3_Set(u8 sta);
void TIM3_Init(u16 arr,u16 psc);
void UART_DMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cpar,u32 cmar);
void UART_DMA_Enable(DMA_Channel_TypeDef*DMA_CHx,u16 len);
void u3_printf(char* fmt, ...);
void uart3_send(u8* buf,u32 num);
//////////////////////////////////////////////////////////////////////////////////////

//#include "stm32f10x.h"
//#include "stdio.h"
//#include <stdarg.h>
//#include <string.h>

///*----------------------USART2******************************/
//#define UART_BUFF_SIZE      1024
//extern uint8_t     uart_buff[UART_BUFF_SIZE];
//extern uint16_t Receive_Length ;
////-----------------------------------------------
//extern uint8_t Strlen;

//extern int fputc(int ch,FILE *p);  //����Ĭ�ϵģ���ʹ��printf����ʱ�Զ�����
//extern void usart_init(void);

//extern void UART5_init(void);
//static char *itoa(int value, char *string, int radix);
////extern void bsp_USART2_IRQHandler(void);

//extern char *get_rebuff(uint8_t *len);
//extern void clean_rebuff(void);
//extern void UART5_printf(USART_TypeDef* USARTx, char *Data,...);
//extern void UART5_SendString(char *s);



#endif













