/********************************************************************
*程序名称：DS1302驱动程序头文件
*程序作者：许方超
*版本信息：V1.8
*最后更新：2013-7-1
*更新说明：配合DS1302驱动程序源文件进行相应更改
********************************************************************/
#ifndef _DS1302_H_
#define _DS1302_H_
#include"STC12.H"
#define uint8 unsigned char
#define uint16  unsigned int
sbit  DS1302_CLK = P0^7; /*实时时钟时钟线引脚 */
sbit  DS1302_IO = P0^6;  /*实时时钟数据线引脚 */
sbit  DS1302_RST = P0^5; /*实时时钟复位线引脚 */
#define DS1302_CLK_L  DS1302_CLK=0
#define DS1302_CLK_H  DS1302_CLK=1
#define DS1302_RST_L  DS1302_RST=0
#define DS1302_RST_H  DS1302_RST=1
extern uint8 DS1302_BUFFER[7];
extern uint8 DS1302_BCDtoDEC(uint8 bcd);
extern void  DS1302_WriteByte(uint8 dat);
extern uint8 DS1302_ReadByte(void);
extern uint8 DS1302_DECtoBCD(uint8 dec);
extern void  DS1302_WriteData(uint8 Add, uint8 dat);
extern uint8 DS1302_ReadData(uint8 Add);
extern void  DS1302_InitSet(void);
extern void  DS1302_GetTime();
extern void  DS1302_SetTime(uint8 Year,uint8  Month ,uint8 Day,uint8 Hour,uint8 Minute,uint8 Second,uint8 Week);
#endif