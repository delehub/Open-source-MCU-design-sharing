#ifndef __USART_H
#define	__USART_H

#include "stm32f10x.h"
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "stdio.h"

#define USART_REC_LEN 1024

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	

void Uart_Init(u32 bound);
void Send_Command(const u8 *com);
void Send_Data(u8 *data, u32 len);
void Receive(u8*Data);



#endif 
