#ifndef __lcd12864_H__
#define __lcd12864_H__
#include "Reg52.h"
#include "intrins.h"
sbit LCD12864_RS=P2^3;    //并行的指令/数据选择信号, H数据, L命令
sbit LCD12864_RW=P2^2;    //并行读写选择信号, H读, L写
sbit LCD12864_EN=P2^1;    //并行使能端, H有效, L无效
#define LCD12864_RS_L LCD12864_RS=0
#define LCD12864_RS_H LCD12864_RS=1
#define LCD12864_RW_L LCD12864_RW=0
#define LCD12864_RW_H LCD12864_RW=1
#define LCD12864_EN_L LCD12864_EN=0
#define LCD12864_EN_H LCD12864_EN=1
//基本指令集预定义
#define	LCD_CLEAR_SCREEN       	0x01 	 	//清屏	
#define	LCD_ADDRESS_RESET      	0x02		//地址归零	 
#define	LCD_BASIC_FUNCTION	  	0x30		//基本指令集
#define	LCD_EXTEND_FUNCTION	   	0x34		//扩充指令集
//扩展指令集预定义
#define	LCD_AWAIT_MODE			0x01	 	//待命模式	
#define LCD_ROLLADDRESS_ON		0x03		//允许输入垂直卷动地址
#define LCD_IRAMADDRESS_ON		0x02		//允许输入IRAM地址	
#define	LCD_SLEEP_MODE			0x08	 	//进入睡眠模式
#define	LCD_NO_SLEEP_MODE		0x0c	 	//脱离睡眠模式
#define LCD_GRAPH_ON			0x36		//打开绘图模式
#define LCD_GRAPH_OFF			0x34		//关闭绘图模式
#ifndef LCD_COLOR
#define LCD_COLOR_BLACK			1
#define LCD_COLOR_WHITE	
#define LcdData P0
#define uchar unsigned char
/*在protues仿真中需要使用CS1和CS2 
 由于仿真中的液晶与实际的液晶不同
 而且不带字库，所以程序有所不同*/
sbit LCD12864_CS1=P2^4;
sbit LCD12864_CS2=P2^5;
sbit LCD12864_RET=P2^0; //复位, L有效本指令集预定义
/*-- 以下为protues里面液晶的控制命令--*/
#define Disp_On  0x3f      // 显示开指令 //
#define Disp_Off 0x3e      // 显示关指令 //
#define Col_Add  0x40      // 定位到第0列指令 //
#define Page_Add 0xb8      // 定位到第0页指令 //
#define Start_Line 0xc0 
 
void  LCD12864_CheckBusy(void);
void  LCD12864_WriteData(unsigned char Data);
uchar LCD12864_ReadData(void);
void  LCD12864_WriteCmd(unsigned char CmdCode);
void  LCD12864_WritePixel(unsigned char x,unsigned char y,unsigned char Color);
uchar LCD12864_ReadPixel(unsigned char x,unsigned char y);
void  LCD12864_DrawLineH(unsigned char x,unsigned char y,unsigned char Length,unsigned char Color);
void  LCD12864_DrawLineV(unsigned char x,unsigned char y,unsigned char Length,unsigned char Color);
void  LCD12864_DrawLineR(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char Color);
void  LCD12864_DisplayPicAll(unsigned char *img);
void  LCD12864_DisplayPicup( uchar code *adder);
void  LCD12864_DisplayPicdown( uchar code *adder);
void  LCD12864_SendASCII(uchar hang,uchar lie,char sign);
void  LCD12864_SendGB2312(uchar hang,uchar lie,unsigned int sign);
void  LCD12864_WhiteBack(uchar x,uchar y,uchar width);
void  LCD12864_startprobar(unsigned char x,unsigned char speed);
void  LCD12864_ClearDRAM(void);
void LCD12864_SetMode(unsigned char Select);
void  LCD12864_DrawRectangle(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char Color);
void  LCD12864_DrawCircle(unsigned char x,unsigned char y,unsigned char r,unsigned char Color);
void  LCD12864_ClearGRAM(unsigned char Mode);
void  LCD12864_ClearGDRAM(void);
void  LCD12864_DisplayString(unsigned char x,unsigned char y,unsigned char *Str);
void  LCD12864_DrawCircleDot(unsigned char x,unsigned char y,char xx,char yy,unsigned char Color);
void  LCD12864_Init(void);

void  LCD12864_SetStatus(unsigned char cmd);

void  LCD12864_graphsetmode(unsigned char Select);
/*----以下在protues里面128X64液晶的显示程序---*/
void  LCD12864_Init1(void);
void  LCD12864_DisplayChar(unsigned char pag,unsigned char col, unsigned char code *szk);
void  LCD12864_DisplayImg(unsigned char code *img) ;
void  LCD12864_ClearScreen();
void  LCD12864_SelectScreen(unsigned char Scr);


#endif
