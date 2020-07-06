#include "track.h"
#include "direction.h"
sbit TRAA=P3^5;//ѭ��A(TRAA)
sbit TRAB=P3^6;//ѭ��B(TRAB)
unsigned char tra;//tra=0,����û�������ߡ�tra=1,����ѭ��A��⵽���ߡ�tra=2������ѭ��B��⵽���ߡ�
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