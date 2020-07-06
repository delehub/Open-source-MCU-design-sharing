#ifndef __LCD12864_H__
#define __LCD12864_H__


void wdata(unsigned char dispdata);//显示数字用
void wcode(unsigned char cmdcode);//清屏用
void InitLCD(void);
void Display_Char(unsigned char x,unsigned char y,unsigned char  Char);
void Display_String(unsigned char x,unsigned char y,unsigned char  *s);
void Display_UnsignedInt(unsigned char x,unsigned char y,unsigned int Number,unsigned char Count);
void Display_SignedInt(unsigned char x,unsigned char y,int Number,unsigned char Count);
void Display_Float(unsigned char x,
                    unsigned char y,
                    float Number,
                    unsigned char Count1,
                    unsigned char Count2);
   

#endif