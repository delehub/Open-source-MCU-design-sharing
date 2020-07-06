#include "radar.h"
#include "delay.h"
#include "time2.h"
#include "uart.h"
extern unsigned int pwmc;//0°pwm=63800，90°pwm=64600，180°pwm=65400
extern unsigned int distance;//超声波测距距离，单位cm
unsigned char angle=0;//舵机角度
unsigned char buff;
bit finish=1;
void Radar(void)
{
	/*-------------舵机转动角度---------------*/
	if(angle<180 && finish)
	{
		angle+=45;//每次角度转45°，每度对应的pwm量为（（65400-63800）/180）=9
		pwmc=63800+(angle*9);//0°~180°pwmc=63800~65400
	}
	else if(angle>=45)
	{
		finish=0;
		angle-=45;
		pwmc=63800+(angle*9);//0°~180°pwmc=63800~65400
	}
	else
	{
		finish=1;
	}
	delay_ms(150);//等待舵机到位
	/*------------超声波模块开始测距----------*/
	Ultrasonic();
	/*--------------串口发送数据--------------*/
	SendOneByte(0xfe);
	SendOneByte(0xef);
	SendOneByte(0x05);
	SendOneByte(0x00);
	buff=angle/256;
	SendOneByte(buff);
	buff=angle%256;
	SendOneByte(buff);
	buff=distance/256;
	SendOneByte(buff);
	buff=distance%256;
	SendOneByte(buff);
}