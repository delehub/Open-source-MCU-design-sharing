
#ifndef __STC12C5A60S2_IIC_H__
#define __STC12C5A60S2_IIC_H__
void write_word(unsigned char device_add,unsigned char word_add,unsigned char date) ;//器件地址，存储地址，数据
unsigned char read_word(unsigned char device_add,unsigned char word_add);
//0XA0外部EEPROM器件地址
//0x90外部ADC器件地址
#endif