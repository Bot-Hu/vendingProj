#include "ultrasonic.h"
#include "delay.h"
#include "stdio.h"
#include "motor.h"

u32 count = 0;
u32 Distance = 0;
const u32 Aisle_Width = 3000;		//货道宽度
u32 Detection_Distance = 0;		//检测距离

void Ultrasoonic_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = Trig_Pin;//Trig
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(ULT_GPIO, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = Echo_Pin;//Echo
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(ULT_GPIO, &GPIO_InitStructure);
	
	Timer5_Config();
}

void Timer5_Config(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5,ENABLE);

    TIM_TimeBaseInitStructure.TIM_Prescaler = 71;
    TIM_TimeBaseInitStructure.TIM_Period = 49999;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(ULT_TIM, &TIM_TimeBaseInitStructure);

    TIM_ClearFlag(ULT_TIM, TIM_FLAG_Update);
}

u32 Distance_Calculate(u32 count)
{
    u32 Distance = 0;
    Distance = (u32)(((float)count / 58) * 100);
    return Distance;
}



void Read_Ult_Once(void)
{
	extern u32 count ;
	extern u32 Distance ;
//	delay_init();
	
	GPIO_ResetBits(ULT_GPIO, Trig_Pin);//预先拉低Trig引脚
	GPIO_SetBits(ULT_GPIO, Trig_Pin);
	delay_us(10);
	GPIO_ResetBits(ULT_GPIO, Trig_Pin);//发出10us的脉冲
	ULT_TIM->CNT = 0;
	while(GPIO_ReadInputDataBit(ULT_GPIO, Echo_Pin) == 0);
	TIM_Cmd(ULT_TIM, ENABLE);
	while(GPIO_ReadInputDataBit(ULT_GPIO, Echo_Pin) == 1);
	TIM_Cmd(ULT_TIM, DISABLE);
	count = ULT_TIM->CNT;
	Distance = Distance_Calculate(count);
//	printf("Distance = %d.", Distance / 100);
//	printf("%d cm\r\n", Distance % 100);
	delay_ms(500);
}

u32 Read_Ult_Average(int times)
{

	int i;
	u32 sum = 0;
	delay_init();
	
	
	for(i=0;i<times;i++)
	{
		delay_ms(300);
		Read_Ult_Once();
		sum+=Distance;
	}
	
	Distance=(u32)(((float)sum/times));
//	printf("Average_Distance = %d.", Distance / 100);
//	printf("%d cm\r\n", Distance % 100);
	return Distance;
}

void Ult_Scan_1(int times)
{
	Detection_Distance = Read_Ult_Average(times);
	if(Detection_Distance >= Aisle_Width)
	{
		MotorSetState(LEFT,MOTOR1);
		delay_ms(300);
		MotorSetState(RIGHT,MOTOR1);
		delay_ms(300);
		MotorSetState(STOP,MOTOR1);
	}
}

void Ult_Scan_2(int times)
{
	Detection_Distance = Read_Ult_Average(times);
	if(Detection_Distance >= Aisle_Width)
	{
		MotorSetState(LEFT,MOTOR2);
		delay_ms(300);
		MotorSetState(RIGHT,MOTOR2);
		delay_ms(300);
		MotorSetState(STOP,MOTOR2);
	}
}
