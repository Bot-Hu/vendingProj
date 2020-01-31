#ifndef __PST_H
#define __PST_H	 
#include "sys.h"

#define PST  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)

void PST_Init(void);//≥ı ºªØ
void PST_Scan(void);
		 				    
#endif
