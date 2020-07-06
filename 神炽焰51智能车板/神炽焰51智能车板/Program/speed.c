#include "speed.h"
unsigned int speedA,speedB,speedpulseA,speedpulseB;
void Speed(void)//利用定时器0中断，60ms计数一次转速
{                                                                                                                                              
	speedA=50*speedpulseA;
	speedB=50*speedpulseB;
	speedpulseA=speedpulseB=0;
}