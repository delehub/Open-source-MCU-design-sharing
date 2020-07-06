#ifndef _IIC_H_
#define _IIC_H_
#include<reg52.h>
#include<intrins.h>
#define uchar unsigned char
#define uint unsigned int 
sbit SDA=P3^6;
sbit SCL=P1^5; 
void IIC_Init();
void IIC_Start();
void IIC_Respons();
void IIC_Stop();
void IIC_WriteByte(uchar dat);
uchar IIC_ReadByte();
void IIC_WriteData(uchar SlA_Address,uchar REG_Address,uchar REG_data);
uchar IIC_ReadData(uchar SlA_Address,uchar REG_Address);

#endif







