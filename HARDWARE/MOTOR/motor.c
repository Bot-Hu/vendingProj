#include "motor.h"
#include "pwm.h"

void MotorControl_Init(void)
{
	/* ����I/O�ڳ�ʼ�� */
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PA,PC�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4|GPIO_Pin_5);	//ֹͣ���
	GPIO_SetBits(GPIOA,GPIO_Pin_8);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC,GPIO_Pin_4|GPIO_Pin_5);	//ֹͣ���
	
	/* PWM��ʼ�� */
	TIM3_PWM_Init(3599,0);			// 20KHz
	MotorSetSpeed(800,MOTOR1);//	��ʼת��
	MotorSetSpeed(800,MOTOR2);//	��ʼת��
}

void MotorSetState(u8 state,u8 MOTORx)
{
	if(MOTORx == MOTOR1){
		switch(state){
			case STOP:	AN1=0;AN2=0;break;
			case LEFT:	AN1=0;AN2=1;break;
			case RIGHT:	AN1=1;AN2=0;break;
			default:	break;
		}
	}
	else if(MOTORx == MOTOR2){
		switch(state){
			case STOP:	BN1=0;BN2=0;break;
			case LEFT:	BN1=0;BN2=1;break;
			case RIGHT:	BN1=1;BN2=0;break;
			default:	break;
		}
	}
}

void MotorSetSpeed(u16 speed,u8 MOTORx)
{
	if(MOTORx == MOTOR1)	PWM_A=speed;
	else if(MOTORx == MOTOR2)	PWM_B=speed;
}

