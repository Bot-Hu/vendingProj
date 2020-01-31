#ifndef __ULT_H
#define __ULT_H	 
#include "sys.h"

#define Trig_Pin	GPIO_Pin_15
#define Echo_Pin	GPIO_Pin_0
#define ULT_GPIO	GPIOA
#define ULT_TIM		TIM5


void Ultrasoonic_Init(void);//≥ı ºªØ
u32 Distance_Calculate(u32 count);
void Timer5_Config(void);
void Read_Ult_Once(void);
u32 Read_Ult_Average(int times);
void Ult_Scan_1(int times);
void Ult_Scan_2(int times);
		 				    
#endif

