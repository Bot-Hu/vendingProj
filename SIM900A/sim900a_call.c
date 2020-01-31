#include "sim900a_call.h"
#include "sim900a.h"
#include "usart2.h"
#include "usart.h"
#include "delay.h"

void CALL_Init(u8 num)
{
//	sim900a_send_cmd("AT+CIPSHUT", "OK", 1000);		//�ر���������
	
//	sim900a_send_cmd("AT", "OK", 1000);
	
//	sim900a_send_cmd("AT+ATE1", "OK", 1000);
	
	//sim900a_send_cmd("AT+COLP=1", "OK", 1000);
	
	sim900a_send_cmd("ATD13119663587;", "", 1000);
		
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);

}


void CALL_Temp_Scanf(u8 air_temp,u8 fun_temp,u8 room_temp)
{
	if(air_temp>27)	
	{
		printf("�յ��¶ȹ���/r/n");
		CALL_Init(air_temp);
	}
	
	if(fun_temp>27)	
	{
		printf("�յ��¶ȹ���/r/n");
		CALL_Init(fun_temp);
	}
	
	if(room_temp>27)	
	{
		printf("�յ��¶ȹ���/r/n");
		CALL_Init(room_temp);
	}
}

void CALL_Humi_Scanf(u8 room_humi)
{
	if(room_humi>60)	
	{
		printf("ʪ�ȹ���/r/n");
		CALL_Init(room_humi);
	}
}

void CALL_Close_Scanf(u8 water_leakage , u8 smoke_detector , u8 room_door_isClose , u8 cabinet_door_isClose)
{
	if(water_leakage>0)	
	{
		printf("ˮ��ͷ�����쳣/r/n");
		CALL_Init(water_leakage);
	}
	
	if(smoke_detector>0)	
	{
		printf("�����쳣/r/n");
		CALL_Init(smoke_detector);
	}
	
	if(room_door_isClose>0)	
	{
		printf("�����ſ����쳣/r/n");
		CALL_Init(room_door_isClose);
	}
	
	if(cabinet_door_isClose>0)	
	{
		printf("���񿪹��쳣/r/n");
		CALL_Init(cabinet_door_isClose);
	}
	
	
}



