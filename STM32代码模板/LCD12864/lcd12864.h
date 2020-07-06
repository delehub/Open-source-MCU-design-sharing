#ifndef __LCD12864_H
#define __LCD12864_H			


#include "stm32f10x.h"
		    						  

#define CS_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_8)
#define CS_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_8)

#define SID_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_9)
#define SID_Set() GPIO_SetBits(GPIOA,GPIO_Pin_9)

#define SCLK_Clr() GPIO_ResetBits(GPIOA,GPIO_Pin_10)
#define SCLK_Set() GPIO_SetBits(GPIOA,GPIO_Pin_10)


void  LCD12864_GPIO_Init(void);
void  SandByte(u8 bye);
void  write_com(u8 com);
void  write_data(u8 data);
void  lcd_pos(u8 y,u8 x);
void  write_hz(const u8 *str);
void  drawpic(const u8 *p);
void  LCD12864_Init(void);


#endif  
	 



