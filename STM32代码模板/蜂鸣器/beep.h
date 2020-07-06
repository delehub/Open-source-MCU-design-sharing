#ifndef __BEEP_H
#define	__BEEP_H

#include "stm32f10x.h"

/*
 * 0	 ·äÃùÆ÷¿ª
 * 1	 ·äÃùÆ÷¹Ø
 */
#define ON			0
#define OFF			1

#define Beep_Turn(a)	if (a)	\
					GPIO_SetBits(GPIOB,GPIO_Pin_0);\
					else		\
					GPIO_ResetBits(GPIOB,GPIO_Pin_0)
					

void Beep_Gpio_Config(void);

#endif /* __BEEP_H */
