#ifndef __LCD12864_H__
#define __LCD12864_H__
void InitLCD(void);
void Display_Char(unsigned char x,unsigned char y,unsigned char  Char);
void Display_String(unsigned char x,unsigned char y,unsigned char  *s);
void Display_Int(unsigned char x,unsigned char y,int Number); 
void Display_Float(unsigned char X,unsigned char Y,float FloatNumber);
   

#endif