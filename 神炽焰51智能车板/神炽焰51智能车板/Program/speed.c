#include "speed.h"
unsigned int speedA,speedB,speedpulseA,speedpulseB;
void Speed(void)//���ö�ʱ��0�жϣ�60ms����һ��ת��
{                                                                                                                                              
	speedA=50*speedpulseA;
	speedB=50*speedpulseB;
	speedpulseA=speedpulseB=0;
}