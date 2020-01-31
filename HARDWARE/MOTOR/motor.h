#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

/*********电机控制_真值表**********
XIN1	 0	     0	     1
XIN2	 0	     1	     0
		停止	正传	反转
**********************************/

#define AN1 PCout(4)
#define AN2 PCout(5)

#define BN1 PAout(5)
#define BN2 PAout(4)

#define	STOP	0
#define	LEFT	1
#define	RIGHT	2

#define	MOTOR1	0
#define	MOTOR2	1

void MotorControl_Init(void);
void MotorSetState(u8 state,u8 MOTORx);
void MotorSetSpeed(u16 speed,u8 MOTORx);

#endif
