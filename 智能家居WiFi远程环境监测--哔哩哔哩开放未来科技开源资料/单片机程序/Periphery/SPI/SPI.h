#ifndef _SPI_H
#define _SPI_H

#include "stm32f10x.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_spi.h"

#define u8 unsigned char 
	
void SPI_Configuration(void);
u8 SPI_SendByte(u8 byte);

#endif
