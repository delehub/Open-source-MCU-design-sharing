#include "uartjudge.h"
unsigned char usart_data[4];//Êı¾İusart_data[1]~ussart_data[3]
unsigned char usart_cound=0;
unsigned char usart_test1=0;
unsigned char usart_test2=0;
unsigned char usart_switch=0;
extern unsigned char aRxBuffer;
void usartjudge(void)
{
	if(!usart_switch)
	{
		if(usart_test2) usart_cound++;
		else usart_cound=0;
		if(aRxBuffer==0xFE)
		{
			if(usart_test2)
			{
				usart_test1=1;		
			}
			else if(!usart_test1)
			{
				usart_test1=1;
				usart_test2=0;
				usart_cound=0;
			}
			else 
			{
				usart_test1=0;
				usart_cound=0;
			}
		}
		else if(usart_test1 && aRxBuffer==0xEF)
		{
			usart_test1=0;
			usart_test2=1;
			usart_cound=0;
		}
		else if(!usart_test2)
		{
			usart_test1=0;
		}
		else if(usart_test1 && usart_test2) usart_test1=0;
		if(usart_test2 && usart_cound>0)
		{
			usart_data[usart_cound]=aRxBuffer;
			if(usart_cound>2)
			{			
				usart_switch=1;
				usart_test1=0;
				usart_test2=0;
			}
		}
	}
}