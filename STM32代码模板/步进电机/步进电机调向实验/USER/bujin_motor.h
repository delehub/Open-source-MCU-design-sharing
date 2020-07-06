#ifndef __BUJIN_MOTOR_H
#define	__BUJIN_MOTOR_H

#include "stm32f10x.h"


#define IN1(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_15);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_15)
					
#define IN2(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_14);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_14)					

#define IN3(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_13);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_13)

#define IN4(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_12);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_12)

#define Coil_AB {IN1(1);IN2(1);IN3(0);IN4(0);}//AB��ͨ�磬������ϵ�
#define Coil_BC {IN1(0);IN2(1);IN3(1);IN4(0);}//BC��ͨ�磬������ϵ�
#define Coil_CD {IN1(0);IN2(0);IN3(1);IN4(1);}//CD��ͨ�磬������ϵ�
#define Coil_DA {IN1(1);IN2(0);IN3(0);IN4(1);}//DA��ͨ�磬������ϵ�
#define Coil_A {IN1(1);IN2(0);IN3(0);IN4(0);}//A��ͨ�磬������ϵ�
#define Coil_B {IN1(0);IN2(1);IN3(0);IN4(0);}//B��ͨ�磬������ϵ�
#define Coil_C {IN1(0);IN2(0);IN3(1);IN4(0);}//C��ͨ�磬������ϵ�
#define Coil_D {IN1(0);IN2(0);IN3(0);IN4(1);}//D��ͨ�磬������ϵ�
#define Coil_OFF {IN1(0);IN2(0);IN3(0);IN4(0);}//ȫ���ϵ�


void BUJIN_MOTOR_GPIO_Config(void);
void BJ_MOTOR_8P_1(u8 Speed);
void BJ_MOTOR_8P_2(u8 Speed);


#endif /* __BUJIN_MOTOR_H */
