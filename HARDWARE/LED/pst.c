#include "pst.h"
#include "led.h"

void PST_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PA端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = 	GPIO_Mode_IPD;                                                                                                                                                  ;

	GPIO_Init(GPIOC, &GPIO_InitStructure);

}

void PST_Scan(void)
{
	if(PST == 1)			LLED = 1;
	else if(PST == 0)		LLED = 0;

}

