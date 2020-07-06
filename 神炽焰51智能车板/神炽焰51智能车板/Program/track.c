#include "track.h"
#include "direction.h"
sbit TRAA=P3^5;//循迹A(TRAA)
sbit TRAB=P3^6;//循迹B(TRAB)
unsigned char tra;//tra=0,代表没遇到黑线。tra=1,代表循迹A检测到黑线。tra=2，代表循迹B检测到黑线。
void Track(void)
{
	if(TRAA) tra=1;
	else if(TRAB) tra=2;
	else tra=0;
	switch(tra)
	{
		case 0:
		{
			Forward();
		}break;
		case 1:
		{
			Left();
		}break;
		case 2:
		{
			Right();
		}break;
		default :break;
	}
}