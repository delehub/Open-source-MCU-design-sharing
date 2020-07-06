#ifndef __IIC_H_
#define __IIC_H_


//#include<reg52.h>

sbit SCL=P2^1;
sbit SDA=P2^0;

void I2cStart();
void I2cStop();
unsigned char I2cSendByte(unsigned char dat);
unsigned char I2cReadByte();

#endif
