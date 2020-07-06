#ifndef __STC12C5A60S2_EEPROM_H__
#define __STC12C5A60S2_EEPROM_H__
unsigned char IapReadByte(unsigned int addr);
void IapProgramByte(unsigned int addr, unsigned char dat);
void IapEraseSector(unsigned int  addr);
#endif