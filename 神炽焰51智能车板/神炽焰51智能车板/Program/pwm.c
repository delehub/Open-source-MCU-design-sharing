#include "pwm.h"
sbit PWML=P2^7;
sbit PWMR=P2^2;
unsigned int pwm=60927;
void Int_Pwm(void)
{
  TR1 = 0;
	ES = 0;
  
	PWMR=PWML=0;
	TMOD = 0x11;//使用模式1，16位定时器，使用"|"符号可以在使用多个定时器时不受影响		
	TH1=0xDC;//给定初值，10ms中断
	TL1=0x00;
	EA=1;//总中断打开
	ET1=1;//定时器0中断打开
	TR1=1;//定时器0开启    
}

void TIME1Interrupt(void) interrupt 3
{
	static unsigned char pwm1_flag=0;
	switch(pwm1_flag)
  {
		case 0:  PWML=1; PWMR=1;TH1=pwm/256; TL1=pwm%256; break;
    case 1:  PWML=0; PWMR=0;TH1=((65536-pwm)+56320)/256; TL1=((65536-pwm)+56320)%256; break;
		default: break;          
  }
  if(++pwm1_flag>1) pwm1_flag=0;
}