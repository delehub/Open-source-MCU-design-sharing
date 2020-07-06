#ifndef __DMA_H
#define	__DMA_H

#include "stm32f10x.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_tim.h"
#include "TFT.h"
#include "common.h"

void DMA_Configuration(u8 *adc);

#endif 
