#ifndef _LCD1602_H_
#define _LCD1602_H_
#include<reg52.h>
#define uchar unsigned char
#define uint  unsigned int
extern void LCD1602_WriteCmd(uchar cmd);
extern void LCD1602_WriteData(uchar dat);
extern void LCD1602_Init(uchar d,uchar c,uchar b);
extern uchar LCD1602_ReadStatus();
extern uchar LCD1602_ReadData();
extern void LCD1602_DefineCGRAM(uchar *sign);
extern void LCD1602_MoveScreen(uchar dir);
extern void LCD1602_MoveCursor(uchar dir);
extern void LCD1602_DisplayChar(uchar hang,uchar lie,uchar ascii);
extern void LCD1602_DisplayString(uchar hang,uchar lie,uchar *str);
extern void LCD1602_PrintHZ(unsigned char sta,unsigned char *hz);
#endif