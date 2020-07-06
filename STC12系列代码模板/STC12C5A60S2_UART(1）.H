#ifndef __STC12C5A60S2_UART_H__
#define __STC12C5A60S2_UART_H__

#define  FOSC 11059200

//**************************************************************************************************
//  UART 函数调用声明
//**************************************************************************************************
//  UART 初始化 
void UART_Init(unsigned long Baud);

//  UART 发送字符、字符串
void UART_SendChar(unsigned char  _CHAR);
void UART_SendStrg     (unsigned char *_STRG);
void UART_SendStrg_Line(unsigned char *_STRG);

//  UART 发送数组 
void UART_SendArry(unsigned char *_ARRY,unsigned char _CUNT);

#endif