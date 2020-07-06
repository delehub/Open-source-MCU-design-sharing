#include "int1.h"
#include "delay.h"
#include "buzzer.h"
#include "pwm.h"
#include "uart.h"
sbit SW=P1^7;//����ѡ�񰴼�(SW)
extern unsigned char function;//�������

void Init_Int1(void)//��ʼ���ⲿ�ж�INT1
{
	EA=1;//���ж�ʹ��
	EX1=1;//�ⲿ�ж�1ʹ��
	IT1=1;//�½��ش����ⲿ�ж�1
}

void int1(void) interrupt 2//�ⲿ�ж�1�жϺ���
{
	unsigned int num=20000;
	if(!SW)//����ѡ�񰴼�(SW)
	{
		if(++function>4)function=1;//��������л�1~4
		if(function<4) Int_Pwm();
		else 
		{
			Init_Uart();
		}
		Buzzer(function);//��������ʾ��
	}

	while(num)//�ȴ������ɿ�
	{
		num--;
		if(!SW) num=20000;
	}
	IE1=0;//����ⲿ�ж�1��־λ
}