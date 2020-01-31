#include "includes.h"

/*		�������		*/
//	int Sum = 0; 					//�ܼ�
const char QUE_REN = '1';		//��ȷ�ϡ�����
u8 EN_BUY = 0;
u8 en_refresh = 1;				//����ˢ��
int Quantity_1 = 3;				//��Ʒ1����   ����
int Quantity_2 = 4;				//��Ʒ2����   ֽ��
int Total_1	= 0;				//��������1   �������������
int Total_2	= 0;				//��������2   �����ֽ������

int main(void)
{	
/*	 	��ʼ��		*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	    	//��ʱ������ʼ��	
	uart_init(9600);	 	//����		PA9_PA10	
	USART2_Init(9600);		//SIM900a  	PA2_PA3		TIM2
	LED_Init();         	//LED��ʼ��	 		PA11_PA12
	
	LCD_Init();			   	//��ʼ��LCD
	tp_dev.init();			//��������ʼ��
 	Ultrasoonic_Init();		//��������ʼ��
	MotorControl_Init();	//�����ʼ��
	PST_Init();				//����ģ���ʼ��		PC11
	while(RTC_Init())		//RTC��ʼ��
	{ 
		LCD_ShowString(60,130,200,16,16,(u8*)"RTC ERROR!   ");	
		delay_ms(800);
		LCD_ShowString(60,130,200,16,16,(u8*)"RTC Trying...");	
	}
	Layout();	//�����ʼ��
	PLED = 0;	//����ָʾ����
	LLED = 0;	//��������
/*     ��ʼ������    */
	while(1)
	{
		Menu();
		Refresh();
		Process();	//����1
		PST_Scan();
		
	}	
}



