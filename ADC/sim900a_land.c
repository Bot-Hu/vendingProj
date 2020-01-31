#include "sim900a_land.h"
#include "sys.h"
#include "sim900a.h"
#include "usart2.h"
#include "usart.h"
#include "delay.h"
void Landing_Init(int id,int num,char *jiaoben )
{
	
//	char LANDING_Buf[200];
	u8 ch = 0x1A;
	
	sim900a_send_cmd("AT", "OK", 1000);		//ģ����Ч�Լ��
	USART2_RX_STA = 0;
	
	

//    SendCmd(CWMODE, "OK", 1000);	//ģ�鹤��ģʽ
//    SendCmd(RST, "OK", 2000);		//ģ������
//    SendCmd(CIFSR, "OK", 1000);		//��ѯ������Ϣ
//    SendCmd(CWJAP, "OK", 2000);		//������Ҫ���ӵ�WIFI�ȵ�SSID������
//    SendCmd(CIPSTART, "OK", 2000);	//TCP����
	sim900a_send_cmd("AT+CGCLASS=\"B\"", "OK", 1000);
	USART2_RX_STA = 0;
	sim900a_send_cmd("AT+CGDCONT=1,\"IP\",\"CMNET\"", "OK", 1000);
	USART2_RX_STA = 0;
	sim900a_send_cmd("AT+CGATT=1", "OK", 1000);
	USART2_RX_STA = 0;		
	sim900a_send_cmd("AT+CIPCSGP=1,\"CMNET\"", "OK", 1000);
	USART2_RX_STA = 0;

/////////��·����////////////////////////////////////////////////////////////
	sim900a_send_cmd("AT+CIPMUX=1", "OK", 1000);						/////
	sim900a_send_cmd("AT+CSTT=\"CNMET\",\"KC\",""","OK", 1000);	/////
	sim900a_send_cmd("AT+CIICR","OK", 1000);							/////
	sim900a_send_cmd("AT+CIFSR", "", 1000);							/////
/////////////////////////////////////////////////////////////////////////////
	
	
//	sim900a_send_cmd("AT+CLPORT=\"TCP\",2002", "OK",1000);
	
	sim900a_send_cmd("AT+CIPSTART=2,\"TCP\",\"183.230.40.40\",1811", "OK", 1000);
	
	USART2_RX_STA = 0;
	
	while(1)
	{
		if(USART2_RX_STA & (0x8000))
		{
//			printf("%s\r\n",USART2_RX_BUF);
			break;
		}
	}
	USART2_RX_STA = 0;
	delay_ms(1000);
	delay_ms(1000);
	sim900a_send_cmd("AT+CIPSEND=2", ">", 1000);	//����͸��ģʽ
	
	//sprintf(LANDING_Buf,"*%d#%d#%s*",ID,NUM,JIAOBEN);
	
//	u2_printf("*127734#0002#sample1*");
	u2_printf("*127734#3116002873#sample1*");
	//uart2_send((u8*)LANDING_Buf,strlen(LANDING_Buf));
//	printf("*127734#3116002873#sample1*\r\n");
	
	uart2_send(&ch,1);
//	printf("%x\r\n",0x1A);
}
