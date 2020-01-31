#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

#define PWM_B	TIM3->CCR1
#define PWM_A	TIM3->CCR2

void TIM3_PWM_Init(u16 arr,u16 psc);

#endif
