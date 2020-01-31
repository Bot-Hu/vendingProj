#include "sim900_sms.h"
#include "sys.h"
#include "sim900a.h"
#include "usart2.h"
#include "usart.h"
#include "delay.h"
#include "includes.h"

u8 ch = 0x1A;

void SMS_Send_English(int Quantity_1,int Quantity_2)
{
	sim900a_send_cmd("AT", "OK", 1000);		//模块有效性检查
	USART2_RX_STA = 0;
	
	sim900a_send_cmd("AT+CSCS=\"GSM\"", "OK", 1000);		
	USART2_RX_STA = 0;
	sim900a_send_cmd("AT+CMGF=1", "OK", 1000);		
	USART2_RX_STA = 0;
	sim900a_send_cmd("AT+CMGS=\"13119663587\"", ">", 1000);		

	u2_printf("Drink:%d  Paper:%d",Quantity_1,Quantity_2);
	uart2_send(&ch,1);
	
}

void SMS_Send_Chinese(int Quantity_1,int Quantity_2)
{

	Quantity_1 += 30;
	Quantity_2 += 30;
	
	sim900a_send_cmd("AT", "OK", 1000);		//模块有效性检查
	USART2_RX_STA = 0;
	
	sim900a_send_cmd("AT+CMGF=1", "OK", 1000);		
	USART2_RX_STA = 0;	
	sim900a_send_cmd("AT+CSMP=17,167,2,25", "OK", 1000);		
	USART2_RX_STA = 0;
	sim900a_send_cmd("AT+CSCS=\"UCS2\"", "OK", 1000);		
	USART2_RX_STA = 0;

	sim900a_send_cmd("AT+CMGS=\"00310033003100310039003600360033003500380037\"", ">", 1000);		

	u2_printf("996E6599FF1A00%d002000207EB85DFEFF1A00%d",Quantity_1,Quantity_2);
	uart2_send(&ch,1);
}

void GPRS_Send_To_Onenet(int Quantity_1,int Quantity_2)
{
	char HTTP_Buf[1024];     //HTTP报文长度
	char Drink_NumStr[10];
	char Paper_NumStr[10];
	
	sim900a_send_cmd("AT", "OK", 1000);
	sim900a_send_cmd("AT+CIPSHUT", "OK", 1000);		//关闭所有连接
	Landing_Init(ID,NUM,JIAOBEN);					//登录设备

//	printf("Landing_Init over\r\n");
	delay_ms(1000);
	delay_ms(1000);
		sim900a_send_cmd("AT+CIPSTART=1,\"TCP\",\"183.230.40.33\",\"80\"", "OK", 1000);
		USART2_RX_STA = 0;
		while(1)
		{
			if(USART2_RX_STA & (0x8000))
			{
//				printf("%s\r\n",USART2_RX_BUF);
				break;
			}
		}
		USART2_RX_STA = 0;
		delay_ms(1000);
		delay_ms(1000);
		
	sprintf(Drink_NumStr, "%d",Quantity_1);
	sprintf(Paper_NumStr,"%d",Quantity_2);

	sim900a_send_cmd("AT+CIPSEND=1", ">", 1000);	//进入透传模式
	delay_ms(1000);

	HTTP_PostPkt
	(HTTP_Buf, API_KEY, DEV_ID,  
	"Drink_Number", "Paper_Number",
	Drink_NumStr , Paper_NumStr); //HTTP组包
	uart2_send((u8*)HTTP_Buf,strlen(HTTP_Buf));
	uart2_send(&ch,1);
	
}

