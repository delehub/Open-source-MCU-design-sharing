#ifndef __Touch_H
#define __Touch_H

#include "stm32f10x_exti.h"
#include "TFT.H"
#include "IO.h"
#include "common.h"
#include "app.h"			//用户任务函数

#define u8 unsigned char
#define u16 unsigned int

#define  CMD_RDX  0xD0	 //触摸IC读坐标积存器
#define  CMD_RDY  0x90

/******************
Touch的IO口定义
******************/
#define IRQ     GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_6)
#define RECS    GPIO_WriteBit(GPIOC,GPIO_Pin_10,Bit_RESET)
#define CS      GPIO_WriteBit(GPIOC,GPIO_Pin_10,Bit_SET)
#define REDCLK  GPIO_WriteBit(GPIOC,GPIO_Pin_11,Bit_RESET)
#define DCLK    GPIO_WriteBit(GPIOC,GPIO_Pin_11,Bit_SET)
#define REDIN   GPIO_WriteBit(GPIOC,GPIO_Pin_9,Bit_RESET)
#define DIN     GPIO_WriteBit(GPIOC,GPIO_Pin_9,Bit_SET)
#define DOUT    GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_7)

typedef struct
{
	int x;
	int y;
	
}TP_PIX;

extern TP_PIX  tp_pix;	  //触控坐标

void Touch_Init(void);
void Delay_Touch(u32 nCount);
u16 ReadFromCharFrom7843(void);         //SPI 读数据
u8 Convert_Pos(TP_PIX *tp_pix);

#endif  
	 
	 



