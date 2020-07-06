#ifndef __DAC_H
#define __DAC_H	     
#include "stm32f10x_dac.h"

#define accuracy 160								    

void Dac1_Init(void);
void Sin_Fun(u16 AM,u16* WAVE_DATA);
void Square_Fun(u16 AM_H,u16 AM_L,u16* WAVE_DATA);
void Triangle_Fun(u16 AM_H,u16 AM_L,u16* WAVE_DATA);
void Dac1_Set_Vol(unsigned int vol);
#endif

















