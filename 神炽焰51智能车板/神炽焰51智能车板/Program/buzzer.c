#include "buzzer.h"
#include "delay.h"
sbit BZ=P0^0;
sbit LED=P0^1;
void Buzzer(unsigned char function)
{
	unsigned char i;
	switch(function)
	{
		case 1:
		{
			BZ=0;
			LED=0;
			delay_ms(500);
			BZ=1;
			LED=1;
			delay_ms(500);			
		}break;
		
		case 2:
		{
			
			for(i=0;i<2;i++)
			{
				BZ=0;
				LED=0;
				delay_ms(500);
				BZ=1;
				LED=1;
				delay_ms(500);
			}				
		}break;
		
		case 3:
		{
			for(i=0;i<3;i++)
			{
				BZ=0;
				LED=0;
				delay_ms(500);
				BZ=1;
				LED=1;
				delay_ms(500);
			}		
		}break;
		
		case 4:
		{
			for(i=0;i<4;i++)
			{
				BZ=0;
				LED=0;
				delay_ms(500);
				BZ=1;
				LED=1;
				delay_ms(500);
			}			
		}break;
		default :break;
	}
}