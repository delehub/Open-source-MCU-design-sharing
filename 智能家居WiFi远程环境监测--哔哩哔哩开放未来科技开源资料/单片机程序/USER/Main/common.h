#ifndef __common_H
#define __common_H

#include "stm32f10x.h"
#include "misc.h"

#define u8  unsigned char
#define u16 unsigned int

u8 average(u8 *adc,u16 star,u16 end);
void sort(u8 *adc,u16 star,u16 end);
u16 ABS(int Data);
void Display_TH(u16 value,u8 *BUFF);
void Display_P(u16 value,u8 *BUFF);
void Display_G(u16 value,u8 *BUFF);
void delay(u32 nCount);
void delayus(unsigned int time);
void delayms(unsigned int time);
void delay_init(void);
void delay_us(u32 nus);
void delay_ms(u16 nms);
#endif 
