#ifndef __Touch_H
#define __Touch_H

#include "stm32f10x_exti.h"
#include "TFT.H"
#include "IO.h"
#include "common.h"
#include "app.h"			//�û�������

#define u8 unsigned char
#define u16 unsigned int

#define  CMD_RDX  0xD0	 //����IC�����������
#define  CMD_RDY  0x90

/******************
Touch��IO�ڶ���
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

extern TP_PIX  tp_pix;	  //��������

void Touch_Init(void);
void Delay_Touch(u32 nCount);
u16 ReadFromCharFrom7843(void);         //SPI ������
u8 Convert_Pos(TP_PIX *tp_pix);

#endif  
	 
	 



