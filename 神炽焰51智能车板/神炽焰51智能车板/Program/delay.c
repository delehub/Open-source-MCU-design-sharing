#include "delay.h"
/*11.0592MHZ�����µ���ʱ����*/
void delay_ms(unsigned int ms)
{
	unsigned int i;
	unsigned char j;
  for(i=0;i<ms;i++)
  {
    for(j=0;j<200;j++);
    for(j=0;j<102;j++);
  }
}