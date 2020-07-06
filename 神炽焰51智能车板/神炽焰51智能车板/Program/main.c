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

sbit BZ=P0^0;//蜂鸣器
sbit LED=P0^1;
sbit PWML=P2^7;
sbit PWMR=P2^2;
extern unsigned char usart_switch;//串口数组接收完成标志位
extern unsigned char usart_data[4];//串口接收数组
extern unsigned int pwmx,pwmy,pwmc;//X、Y、超声波舵机PWM
bit ultrasonic_switch=0;//超声波雷达开关标志位
unsigned char function=4;//功能序号：1=红外避障，2=循迹，3=超声波壁障，4=串口控制
int main(void)
{
	unsigned char function_last=4;//上次选择的功能序号
	Init_Int1();//外部中断1初始化
	Init_Int0();//外部中断0初始化
	Init_Time0();//定时器0初始化
	Init_Time2();//定时器2初始化
	Init_Uart();
	LED=0;
	while(1)
	{
		if(function_last!=function)//如果上次的功能序号与这次的对不上，说明切换了功能序号，需要停止上次小车余留的状态
		{
			Stop();
			ultrasonic_switch=0;//超声波雷达开关标志位
			function_last=function;		
		}
		switch(function)
		{
			case 1://红外壁障
			{
				Avoid();//红外壁障函数
			}break;
			
			case 2://循迹
			{
				Track();//循迹函数
			}break;
			
			case 3://超声波壁障
			{
				Ultra_Avo();//超声波壁障函数
			}break;
			
			case 4://串口控制
			{
				if(usart_switch)
				{
					PWML=PWMR=1;
					switch(usart_data[1])
					{
						case 0x00://方向控制
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
						
						case 0x01://探照灯
						{
							switch(usart_data[2])
							{
								case 0x00:break;
								case 0x01:break;
								default :break;
							}
						}break;
						
						case 0x02://喇叭
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
						
						
						case 0x04://雷达扫描
						{
							switch(usart_data[2])
							{
								case 0x00:ultrasonic_switch=0;break;
								case 0x01:ultrasonic_switch=1;break;
								default :break;
							}
						}break;
						
						case 0x05://电机PWM
						{
							
						}break;
						
						case 0x06://舵机X
						{
							pwmx=(usart_data[2]*256)+usart_data[3];
						}break;
						
						
						case 0x07://舵机Y
						{
							pwmy=(usart_data[2]*256)+usart_data[3];
						}break;
		
						default :break;
					}
					usart_switch=0;//串口数组接收完成标志位清零
				}
			}break;
			
			default :break;
		}
		/*超声波*/	
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