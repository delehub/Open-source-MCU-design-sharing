#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_tim.h"

#define u8 unsigned char
#define u16 unsigned int

void GPIO_Configuration(void);
void TIM4_PWM_Configuration(void);

#endif  

