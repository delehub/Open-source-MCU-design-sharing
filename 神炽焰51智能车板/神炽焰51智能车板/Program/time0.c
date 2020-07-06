#include "time0.h"
#include "delay.h"
#include "speed.h"
sbit PWMX=P1^0;
sbit PWMY=P1^1;
sbit PWMC=P1^2;
unsigned int pwmx=64200,pwmy=64400,pwmc=64600;
//0��pwmx=63500��90��pwmx=64200��180��pwmx=65000
//0��pwmy=63800��90��pwmy=64400��180��pwmy=65000
//0��pwmc=63800��90��pwmc=64600��180��pwmc=65400
void Init_Time0(void)
{
   /*0��=0.5ms, 45��=1ms, 90��=1.5ms, 135��=2ms, 180��=2.5ms*/
	TMOD |= 0x01;//ʹ��ģʽ1��16λ��ʱ����ʹ��"|"���ſ�����ʹ�ö����ʱ��ʱ����Ӱ��		
	TH0=0xDC;//������ֵ��10ms�ж�
	TL0=0x00;
	EA=1;//���жϴ�
	ET0=1;//��ʱ��0�жϴ�
	TR0=1;//��ʱ��0����    
}

void TIME0Interrupt(void) interrupt 1
{
	static unsigned char pwm_flag=0;
	switch(pwm_flag)
  {
		case 0:  PWMX=1; TH0=pwmx/256; TL0=pwmx%256; break;
    case 1:  PWMX=0; TH0=((65536-pwmx)+56320)/256; TL0=((65536-pwmx)+56320)%256; break;
		case 2:  PWMY=1; TH0=pwmy/256; TL0=pwmy%256; break;
		case 3:  PWMY=0; TH0=((65536-pwmy)+56320)/256; TL0=((65536-pwmy)+56320)%256; break;
		case 4:  PWMC=1; TH0=pwmc/256; TL0=pwmc%256; break;
    case 5:  PWMC=0; TH0=((65536-pwmc)+56320)/256; TL0=((65536-pwmc)+56320)%256; break;
		default: break;          
  }
  if(++pwm_flag>5) pwm_flag=0;
}
