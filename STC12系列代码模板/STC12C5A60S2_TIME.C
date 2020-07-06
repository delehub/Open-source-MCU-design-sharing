#include"MAIN.H"
#include"STC12C5A60S2_TIME.H"

void Timer0Init(void)		//50毫秒@12.000MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xB0;		//设置定时初值 (65536-50000)%256
	TH0 = 0x3C;		//设置定时初值 (65536-50000)/256
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
    
    // 启用中断
    ET0 = 1;
    EA = 1;
}
