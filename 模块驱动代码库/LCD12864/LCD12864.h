#ifndef __lcd12864_H__
#define __lcd12864_H__
#include "Reg52.h"
#include "intrins.h"
sbit LCD12864_RS=P2^3;    //���е�ָ��/����ѡ���ź�, H����, L����
sbit LCD12864_RW=P2^2;    //���ж�дѡ���ź�, H��, Lд
sbit LCD12864_EN=P2^1;    //����ʹ�ܶ�, H��Ч, L��Ч
#define LCD12864_RS_L LCD12864_RS=0
#define LCD12864_RS_H LCD12864_RS=1
#define LCD12864_RW_L LCD12864_RW=0
#define LCD12864_RW_H LCD12864_RW=1
#define LCD12864_EN_L LCD12864_EN=0
#define LCD12864_EN_H LCD12864_EN=1
//����ָ�Ԥ����
#define	LCD_CLEAR_SCREEN       	0x01 	 	//����	
#define	LCD_ADDRESS_RESET      	0x02		//��ַ����	 
#define	LCD_BASIC_FUNCTION	  	0x30		//����ָ�
#define	LCD_EXTEND_FUNCTION	   	0x34		//����ָ�
//��չָ�Ԥ����
#define	LCD_AWAIT_MODE			0x01	 	//����ģʽ	
#define LCD_ROLLADDRESS_ON		0x03		//�������봹ֱ����ַ
#define LCD_IRAMADDRESS_ON		0x02		//��������IRAM��ַ	
#define	LCD_SLEEP_MODE			0x08	 	//����˯��ģʽ
#define	LCD_NO_SLEEP_MODE		0x0c	 	//����˯��ģʽ
#define LCD_GRAPH_ON			0x36		//�򿪻�ͼģʽ
#define LCD_GRAPH_OFF			0x34		//�رջ�ͼģʽ
#ifndef LCD_COLOR
#define LCD_COLOR_BLACK			1
#define LCD_COLOR_WHITE	
#define LcdData P0
#define uchar unsigned char
/*��protues��������Ҫʹ��CS1��CS2 
 ���ڷ����е�Һ����ʵ�ʵ�Һ����ͬ
 ���Ҳ����ֿ⣬���Գ���������ͬ*/
sbit LCD12864_CS1=P2^4;
sbit LCD12864_CS2=P2^5;
sbit LCD12864_RET=P2^0; //��λ, L��Ч��ָ�Ԥ����
/*-- ����Ϊprotues����Һ���Ŀ�������--*/
#define Disp_On  0x3f      // ��ʾ��ָ�� //
#define Disp_Off 0x3e      // ��ʾ��ָ�� //
#define Col_Add  0x40      // ��λ����0��ָ�� //
#define Page_Add 0xb8      // ��λ����0ҳָ�� //
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
/*----������protues����128X64Һ������ʾ����---*/
void  LCD12864_Init1(void);
void  LCD12864_DisplayChar(unsigned char pag,unsigned char col, unsigned char code *szk);
void  LCD12864_DisplayImg(unsigned char code *img) ;
void  LCD12864_ClearScreen();
void  LCD12864_SelectScreen(unsigned char Scr);


#endif
