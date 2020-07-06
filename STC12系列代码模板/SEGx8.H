#ifndef __SEGx8_H__
#define __SEGx8_H__


extern unsigned char ShowData[8];
void SEGx8_Show(unsigned char Wei);
void SEGx8_ShowString(unsigned char X,unsigned char *String);
void SEGx8_ShowIntNumber(int Number);
void SEGx8_ShowFloatNumber(float Number);
#endif
