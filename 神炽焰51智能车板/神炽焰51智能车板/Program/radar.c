#include "radar.h"
#include "delay.h"
#include "time2.h"
#include "uart.h"
extern unsigned int pwmc;//0��pwm=63800��90��pwm=64600��180��pwm=65400
extern unsigned int distance;//�����������룬��λcm
unsigned char angle=0;//����Ƕ�
unsigned char buff;
bit finish=1;
void Radar(void)
{
	/*-------------���ת���Ƕ�---------------*/
	if(angle<180 && finish)
	{
		angle+=45;//ÿ�νǶ�ת45�㣬ÿ�ȶ�Ӧ��pwm��Ϊ����65400-63800��/180��=9
		pwmc=63800+(angle*9);//0��~180��pwmc=63800~65400
	}
	else if(angle>=45)
	{
		finish=0;
		angle-=45;
		pwmc=63800+(angle*9);//0��~180��pwmc=63800~65400
	}
	else
	{
		finish=1;
	}
	delay_ms(150);//�ȴ������λ
	/*------------������ģ�鿪ʼ���----------*/
	Ultrasonic();
	/*--------------���ڷ�������--------------*/
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