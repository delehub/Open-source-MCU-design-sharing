#include <reg52.h>
#include "delay.h"
#include "int1.h"
#include "direction.h"
#include "avoid.h"
#include "track.h"
#include "uart.h"
#include "time0.h"
#include "time2.h"
#include "radar.h"

sbit BZ=P0^0;//������
sbit LED=P0^1;
sbit PWML=P2^7;
sbit PWMR=P2^2;
extern unsigned char usart_switch;//�������������ɱ�־λ
extern unsigned char usart_data[4];//���ڽ�������
extern unsigned int pwmx,pwmy,pwmc;//X��Y�����������PWM
bit ultrasonic_switch=0;//�������״￪�ر�־λ
unsigned char function=4;//������ţ�1=������ϣ�2=ѭ����3=���������ϣ�4=���ڿ���
int main(void)
{
	unsigned char function_last=4;//�ϴ�ѡ��Ĺ������
	Init_Int1();//�ⲿ�ж�1��ʼ��
	Init_Int0();//�ⲿ�ж�0��ʼ��
	Init_Time0();//��ʱ��0��ʼ��
	Init_Time2();//��ʱ��2��ʼ��
	Init_Uart();
	LED=0;
	while(1)
	{
		if(function_last!=function)//����ϴεĹ����������εĶԲ��ϣ�˵���л��˹�����ţ���Ҫֹͣ�ϴ�С��������״̬
		{
			Stop();
			ultrasonic_switch=0;//�������״￪�ر�־λ
			function_last=function;		
		}
		switch(function)
		{
			case 1://�������
			{
				Avoid();//������Ϻ���
			}break;
			
			case 2://ѭ��
			{
				Track();//ѭ������
			}break;
			
			case 3://����������
			{
				Ultra_Avo();//���������Ϻ���
			}break;
			
			case 4://���ڿ���
			{
				if(usart_switch)
				{
					PWML=PWMR=1;
					switch(usart_data[1])
					{
						case 0x00://�������
						{
							switch(usart_data[2])
							{
								case 0x00:Stop();break;
								case 0x01:Forward();break;
								case 0x02:Back();break;
								case 0x03:Left();break;
								case 0x04:Right();break;
								default :break;
							}
						}break;
						
						case 0x01://̽�յ�
						{
							switch(usart_data[2])
							{
								case 0x00:break;
								case 0x01:break;
								default :break;
							}
						}break;
						
						case 0x02://����
						{
							switch(usart_data[2])
							{
								case 0x00:BZ=1;break;
								case 0x01:BZ=0;break;
								default :break;
							}
						}break;
						
						case 0x03:
						{
							switch(usart_data[2])
							{
								case 0x00:break;
								case 0x01:break;
								default :break;
							}
						}break;
						
						
						case 0x04://�״�ɨ��
						{
							switch(usart_data[2])
							{
								case 0x00:ultrasonic_switch=0;break;
								case 0x01:ultrasonic_switch=1;break;
								default :break;
							}
						}break;
						
						case 0x05://���PWM
						{
							
						}break;
						
						case 0x06://���X
						{
							pwmx=(usart_data[2]*256)+usart_data[3];
						}break;
						
						
						case 0x07://���Y
						{
							pwmy=(usart_data[2]*256)+usart_data[3];
						}break;
		
						default :break;
					}
					usart_switch=0;//�������������ɱ�־λ����
				}
			}break;
			
			default :break;
		}
		/*������*/	
		if(ultrasonic_switch)
		{
			Radar();
		}
		else if(function!=3)
		{
			pwmc=64550;
		}
	}
}