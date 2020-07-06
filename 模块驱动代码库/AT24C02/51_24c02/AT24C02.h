#ifndef _AT24C02_H_
#define _AT24C02_H_
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long
#include "IIC.h"
#include "Delay.h"
void IIC_AT24C02_writebyte(uint addr,uchar dat); 
void IIC_AT24C02_writepage(uint addr,unsigned char *pbuf);
uchar IIC_AT24C02_readbyte(uchar address);
void IIC_AT24C02_readpage(uint addr,uint length,unsigned char *pbuf);
#endif













