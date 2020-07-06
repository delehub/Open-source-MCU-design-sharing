#ifndef __SEGx4_H__
#define __SEGx4_H__


void SEGx4_Clear(void);

void LED_OUT(unsigned char X);

void SEGx4_ShowChar(unsigned char X,unsigned char Char);
void SEGx4_ShowString(unsigned char X,unsigned char *String);
void SEGx4_Show_intnumber(unsigned char X,unsigned int Number);
void SEGx4_float(unsigned char k,float numb);

#endif