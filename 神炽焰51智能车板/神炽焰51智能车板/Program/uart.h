#ifndef __UART_H__
#define __UART_H__
#include <reg52.h>
void Init_Uart(void);
void SendOneByte(unsigned char c);
#endif