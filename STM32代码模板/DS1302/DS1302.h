#ifndef __DS1302_H
#define	__DS1302_H

#include "stm32f10x.h"

#define SCLK_OUT(a)	if (a)	\
							GPIO_SetBits(GPIOB,GPIO_Pin_10);\
							else		\
							GPIO_ResetBits(GPIOB,GPIO_Pin_10)
							
#define RST_OUT(a)	if (a)	\
							GPIO_SetBits(GPIOB,GPIO_Pin_8);\
							else		\
							GPIO_ResetBits(GPIOB,GPIO_Pin_8)
														
#define IO_OUT(a)	if (a)	\
							GPIO_SetBits(GPIOB,GPIO_Pin_9);\
							else		\
							GPIO_ResetBits(GPIOB,GPIO_Pin_9)
							
#define DS1302_IO_IN      GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)


void DS1302_GPIO_Init(void);
void DS1302_DATA_OUT(void);
void DS1302_DATA_IN(void);
void DS1302_init(u8 year,u8 mon,u8 day,u8 shi,u8 fen,u8 miao);        //DS1302 的 初 始 化
u8  DS1302_readByte(void);
void  DS1302_writeByte(u8 tdata);
void DS1302_write(u8 tadd,u8 tdata);
u8 DS1302_read(u8 tadd);
void DS1302_set_time(void);	 //设置时间
void DS1302_read_time(void);    //读取时间


#endif 
