#ifndef _ADC0804_H_
#define _ADC0804_H_
#include <reg52.h>
#define uchar unsigned char
#define uint  unsigned int
sbit ADC0804_CS=P2^3;
sbit ADC0804_RD=P2^4;
sbit ADC0804_WR=P2^5;
sbit ADC0804_INT=P2^6;
#define  ADC0804_CS_H   ADC0804_CS=1
#define  ADC0804_CS_L   ADC0804_CS=0
#define	 ADC0804_RD_H   ADC0804_RD=1
#define	 ADC0804_RD_L   ADC0804_RD=0
#define  ADC0804_WR_H   ADC0804_WR=1
#define  ADC0804_WR_L   ADC0804_WR=0
#define  ADC0804_DATA   P1
#define  ADC0804_Delay 	ADC0804_Delay100us()

void ADC0804_Start();
uchar ADC0804_ReadData();
uint ADC0804_GetVoltage(uchar V);
#endif