#include "pwm.h"

void TIM3_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	 //使能TIM3时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能GPIOA时钟
	
	// TIM3 GPIO初始化
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);	//PA6 TIM3_CH1 PWMB            PA7 TIM3_CH2 PWMA
	
	//定时器设置
	TIM_TimeBaseInitStruct.TIM_Period = arr;
	TIM_TimeBaseInitStruct.TIM_Prescaler = psc;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;	//向上计数
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitStruct.TIM_OCMode = TIM_OCMode_PWM1;	//选择定时器模式:TIM脉冲宽度调制模式1
	TIM_OCInitStruct.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStruct.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStruct.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM3,&TIM_OCInitStruct);	//CH1
	TIM_OC2Init(TIM3,&TIM_OCInitStruct);	//CH2

	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);  //CH1预装载使能
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);  //CH2预装载使能
	
	TIM_ARRPreloadConfig(TIM3,ENABLE); //使能TIM3在ARR上的预装载寄存器
	TIM_Cmd(TIM3,ENABLE);  //使能TIM3
}
