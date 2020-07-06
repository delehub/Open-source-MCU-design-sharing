#include "time2.h"
#include "delay.h"
#include "direction.h"
#include <intrins.h>
sbit TRIG=P3^4;
sbit ECHO=P3^2;
sbit LED=P0^1;
extern unsigned int pwmc;//���������PWM����
unsigned int distance=0;//�����������룬��λcm
void Init_Time2(void)
{
	RCAP2H=0x00;//T2��ʱ������ֵ
	RCAP2L=0x00;
	EA=1;//�������ж�
	ET2=1;// ��ʱ��2�жϴ�
	TR2=0;//��ʱ��2ֹͣ 
}


void Time2Interrupt(void) interrupt 5
{
	TF2=0;//TIM2��Ҫ��������־λ

}

void Init_Int0(void)//��ʼ���ⲿ�ж�INT0
{
	EA=1;//���ж�ʹ��
	EX0=1;//�ⲿ�ж�0ʹ��
	IT0=1;//�½��ش����ⲿ�ж�0
}

void Int0Interrupt(void) interrupt 0//�ⲿ�ж�0�жϺ���
{
	TR2=0;//��ʱ��2ֹͣ
	distance=((TH2*256)+TL2)*0.01845;//���뵥λcm������11.0592MHZ
	if(distance>400) distance=400;//�޶��������ֵΪ400cm
}

void Ultrasonic(void)//���������
{
	unsigned char i=0;
	unsigned int ECHO_test=50000;//50msʱ���ڼ�����޳������źŷ���
	TH2=0x00;//T2��ʱ������ֵ
	TL2=0x00;	
	TRIG=1;//����10us�ߵ�ƽ�źŴ���������
	for(i;i<5;i++) _nop_();
	TRIG=0;
	while((!ECHO) && ECHO_test)
	{
		ECHO_test--;
	}
	if(ECHO_test) TR2=1;//��ʱ��2����
	else distance=400;//�����������źŷ������ж�Ϊ����̽����룬ֱ�Ӹ�ֵ�������400cm��
	ECHO_test=50000;
	while(ECHO && ECHO_test)
	{
		ECHO_test--;
	}
}

void Ultra_Avo(void)//����������
{
	/*�м���ĳһ��С��30cm��ʼת��*/
	unsigned int distanceC,distanceA,distanceB;//������������ľ���ֵ���ֱ�Ϊ�м䣬��ߣ��ұ�
	if(pwmc!=64600){pwmc=64600;LED=0;delay_ms(800);LED=1;}//���ת���м�
	Ultrasonic();//���������
	delay_ms(1);
	distanceC=distance;
	if(distanceC<=30)
	{
		Stop();
		pwmc=65200;//���ת���ұ�
		LED=0;
		delay_ms(800);
		LED=1;
		Ultrasonic();//���������
		delay_ms(2);
		distanceB=distance;
	
		pwmc=63800;//���ת�����
		LED=0;
		delay_ms(1200);
		LED=1;
		Ultrasonic();//���������
		delay_ms(2);
		distanceA=distance;
	}

	if(distanceC>30)//�ж�ǰ�������Ƿ����30cm������Ǽ�������ǰ��
	{
		Forward();
	}
	else if((distanceA >= distanceB)&&(distanceA>30))//�����ж���߾����Ƿ���ڵ����ұ��Ҵ���30cm���������תһ��ʱ���ͣ��
	{
		Left();
		delay_ms(200);
		Stop();
	}
	else if(distanceB>30)//�����ж��ұ��Ƿ����30cm������ǣ���תһ��ʱ���ͣ��
	{
		Right();
		delay_ms(200);
		Stop();
	}
	else//�������һ��ʱ��ͣ��
	{
		Back();
		delay_ms(200);
		Stop();
	}
}
