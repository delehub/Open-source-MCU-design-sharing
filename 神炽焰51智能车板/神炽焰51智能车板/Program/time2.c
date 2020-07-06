#include "time2.h"
#include "delay.h"
#include "direction.h"
#include <intrins.h>
sbit TRIG=P3^4;
sbit ECHO=P3^2;
sbit LED=P0^1;
extern unsigned int pwmc;//超声波舵机PWM控制
unsigned int distance=0;//超声波测距距离，单位cm
void Init_Time2(void)
{
	RCAP2H=0x00;//T2定时器赋初值
	RCAP2L=0x00;
	EA=1;//开启总中断
	ET2=1;// 定时器2中断打开
	TR2=0;//定时器2停止 
}


void Time2Interrupt(void) interrupt 5
{
	TF2=0;//TIM2需要软件清除标志位

}

void Init_Int0(void)//初始化外部中断INT0
{
	EA=1;//总中断使能
	EX0=1;//外部中断0使能
	IT0=1;//下降沿触发外部中断0
}

void Int0Interrupt(void) interrupt 0//外部中断0中断函数
{
	TR2=0;//定时器2停止
	distance=((TH2*256)+TL2)*0.01845;//距离单位cm，晶振11.0592MHZ
	if(distance>400) distance=400;//限定距离最大值为400cm
}

void Ultrasonic(void)//超声波测距
{
	unsigned char i=0;
	unsigned int ECHO_test=50000;//50ms时间内检测有无超声波信号返回
	TH2=0x00;//T2定时器赋初值
	TL2=0x00;	
	TRIG=1;//发送10us高电平信号触发超声波
	for(i;i<5;i++) _nop_();
	TRIG=0;
	while((!ECHO) && ECHO_test)
	{
		ECHO_test--;
	}
	if(ECHO_test) TR2=1;//定时器2开启
	else distance=400;//若超声波无信号返回则判定为超出探测距离，直接赋值距离变量400cm。
	ECHO_test=50000;
	while(ECHO && ECHO_test)
	{
		ECHO_test--;
	}
}

void Ultra_Avo(void)//超声波壁障
{
	/*中间与某一边小于30cm开始转弯*/
	unsigned int distanceC,distanceA,distanceB;//定义三个方向的距离值，分别为中间，左边，右边
	if(pwmc!=64600){pwmc=64600;LED=0;delay_ms(800);LED=1;}//舵机转到中间
	Ultrasonic();//超声波测距
	delay_ms(1);
	distanceC=distance;
	if(distanceC<=30)
	{
		Stop();
		pwmc=65200;//舵机转到右边
		LED=0;
		delay_ms(800);
		LED=1;
		Ultrasonic();//超声波测距
		delay_ms(2);
		distanceB=distance;
	
		pwmc=63800;//舵机转到左边
		LED=0;
		delay_ms(1200);
		LED=1;
		Ultrasonic();//超声波测距
		delay_ms(2);
		distanceA=distance;
	}

	if(distanceC>30)//判断前方距离是否大于30cm，如果是继续保持前行
	{
		Forward();
	}
	else if((distanceA >= distanceB)&&(distanceA>30))//否则判断左边距离是否大于等于右边且大于30cm，如果是左转一段时间后停下
	{
		Left();
		delay_ms(200);
		Stop();
	}
	else if(distanceB>30)//否则判断右边是否大于30cm，如果是，右转一段时间后停下
	{
		Right();
		delay_ms(200);
		Stop();
	}
	else//否则后退一段时间停下
	{
		Back();
		delay_ms(200);
		Stop();
	}
}
