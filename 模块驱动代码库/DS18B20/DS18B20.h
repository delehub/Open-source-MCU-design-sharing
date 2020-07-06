#ifndef  _DS18B20_H_
#define  _DS18B20_H_
#include <reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar DS18B20_Reset();
uchar DS18B20_ReadBit();
void  DS18B20_GetRom(unsigned char *ROM);
void  DS18B20_WriteBit(uchar aa);
uchar DS18B20_ReadByte();
void  DS18B20_WriteByte(uchar dat);
bit   DS18B20_PowerMode();
uchar DS18B20_MatchRom(uchar *rom);
void  DS18B20_SetResolution(unsigned char res);
long  DS18B20_GetTemperature();
#endif


