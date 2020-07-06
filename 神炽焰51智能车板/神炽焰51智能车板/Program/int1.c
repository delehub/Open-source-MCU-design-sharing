#include "int1.h"
#include "delay.h"
#include "buzzer.h"
#include "pwm.h"
#include "uart.h"
sbit SW=P1^7;//功能选择按键(SW)
extern unsigned char function;//功能序号

void Init_Int1(void)//初始化外部中断INT1
{
	EA=1;//总中断使能
	EX1=1;//外部中断1使能
	IT1=1;//下降沿触发外部中断1
}

void int1(void) interrupt 2//外部中断1中断函数
{
	unsigned int num=20000;
	if(!SW)//功能选择按键(SW)
	{
		if(++function>4)function=1;//功能序号切换1~4
		if(function<4) Int_Pwm();
		else 
		{
			Init_Uart();
		}
		Buzzer(function);//蜂鸣器提示音
	}

	while(num)//等待按键松开
	{
		num--;
		if(!SW) num=20000;
	}
	IE1=0;//清除外部中断1标志位
}