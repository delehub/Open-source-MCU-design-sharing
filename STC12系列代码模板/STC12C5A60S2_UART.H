
#ifndef __STC12C5A60S2_UART_H__
#define __STC12C5A60S2_UART_H__

void init_com(void);
void send_char( unsigned char ch1);
void UART_SendString(unsigned char *String);
void UART_SendLine(void);
void UART_SendIntNumber(int Number);
void UART_SendFloatNumber(float Number);
#endif