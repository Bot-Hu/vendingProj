#include "includes.h"

/*		定义参数		*/
//	int Sum = 0; 					//总价
const char QUE_REN = '1';		//“确认”付款
u8 EN_BUY = 0;
u8 en_refresh = 1;				//允许刷新
int Quantity_1 = 3;				//商品1数量   饮料
int Quantity_2 = 4;				//商品2数量   纸巾
int Total_1	= 0;				//购买数量1   购买的饮料数量
int Total_2	= 0;				//购买数量2   购买的纸巾数量

int main(void)
{	
/*	 	初始化		*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	delay_init();	    	//延时函数初始化	
	uart_init(9600);	 	//蓝牙		PA9_PA10	
	USART2_Init(9600);		//SIM900a  	PA2_PA3		TIM2
	LED_Init();         	//LED初始化	 		PA11_PA12
	
	LCD_Init();			   	//初始化LCD
	tp_dev.init();			//触摸屏初始化
 	Ultrasoonic_Init();		//超声波初始化
	MotorControl_Init();	//电机初始化
	PST_Init();				//光敏模块初始化		PC11
	while(RTC_Init())		//RTC初始化
	{ 
		LCD_ShowString(60,130,200,16,16,(u8*)"RTC ERROR!   ");	
		delay_ms(800);
		LCD_ShowString(60,130,200,16,16,(u8*)"RTC Trying...");	
	}
	Layout();	//界面初始化
	PLED = 0;	//工作指示灯亮
	LLED = 0;	//照明灯灭
/*     初始化结束    */
	while(1)
	{
		Menu();
		Refresh();
		Process();	//串口1
		PST_Scan();
		
	}	
}



