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

#define Coil_A {IN1(1);IN2(0);IN3(0);IN4(0);}//A相通电，其他相断电
#define Coil_B {IN1(0);IN2(1);IN3(0);IN4(0);}//B相通电，其他相断电
#define Coil_C {IN1(0);IN2(0);IN3(1);IN4(0);}//C相通电，其他相断电
#define Coil_D {IN1(0);IN2(0);IN3(0);IN4(1);}//D相通电，其他相断电
#define Coil_OFF {IN1(0);IN2(0);IN3(0);IN4(0);}//全部断电


void BUJIN_MOTOR_GPIO_Config(void);
void BJ_MOTOR1(u8 speed);


#endif /* __BUJIN_MOTOR_H */
