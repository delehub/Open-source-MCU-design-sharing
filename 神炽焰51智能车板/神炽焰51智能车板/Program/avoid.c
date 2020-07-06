#include "avoid.h"
#include "direction.h"
#include "delay.h"
sbit AVOA=P1^3;//壁障A(AVOA)
sbit AVOB=P1^4;//壁障B(AVOB)
unsigned char avo;//avo=0,代表没遇到障碍物。avo=1，代表壁障A检测到障碍物。avo=2，代表壁障B检测到障碍物。
void Avoid(void)
{
	if(!AVOA) avo=1;
	else if(!AVOB) avo=2;
	else avo=0;
	switch(avo)
	{
		case 0:
		{
			Forward();
		}break;
		case 1:
		{
			Back();
			delay_ms(200);
			Right();
			delay_ms(200);
			Stop();
		}break;
		case 2:
		{
			Back();
			delay_ms(200);
			Left();
			delay_ms(200);
			Stop();	
		}break;
		default :break;
	}
}