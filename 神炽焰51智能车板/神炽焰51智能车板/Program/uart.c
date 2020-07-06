#include "uart.h"
#incldue "uartjudge.h"
unsigned char aRxBuffer;
sbit PWML=P2^7;
sbit PWMR=P2^2;
void Init_Uart(void)
{
  TR1 = 0;
	ET1=0;
	
	PWML=PWMR=0;  
	TMOD = 0x21;
  SCON = 0x50;
  TH1 = 0xFD;
  TL1 = TH1;
  PCON = 0x00;
	IP=0x10;//串口中断优先级最高
  EA = 1;
  ES = 1;
  TR1 = 1;
}

void SendOneByte(unsigned char c)
{
    SBUF = c;
    while(!TI);
    TI = 0;
}

void UARTInterrupt(void) interrupt 4
{
    if(RI)
    {
      RI = 0;
			aRxBuffer=SBUF;
      usartjudge();
    }
}

