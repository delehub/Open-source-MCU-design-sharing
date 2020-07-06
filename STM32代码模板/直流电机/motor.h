#ifndef __MOTOR_H
#define __MOTOR_H
#include "stm32f10x.h"
#define A1_On         	GPIO_SetBits(GPIOE,GPIO_Pin_0)
#define A1_Off         	GPIO_ResetBits(GPIOE,GPIO_Pin_0)
#define A2_On        	GPIO_SetBits(GPIOE,GPIO_Pin_2)
#define A2_Off         	GPIO_ResetBits(GPIOE,GPIO_Pin_2)
#define B1_On         	GPIO_SetBits(GPIOE,GPIO_Pin_4)
#define B1_Off         	GPIO_ResetBits(GPIOE,GPIO_Pin_4)
#define B2_On         	GPIO_SetBits(GPIOE,GPIO_Pin_6)
#define B2_Off         	GPIO_ResetBits(GPIOE,GPIO_Pin_6)
void Motor_Init(void);          //控制引脚设置
void Motor_Forward(void);      //前进
void Motor_Back(void);        //后退
void Motor_Stop(void);        //暂停
void Motor_TurnRight(void);   //右转弯
void Motor_TurnLeft(void);    //左转弯
#endif
