#include "Motor.h"
#include "sys.h"
void Motor_Init(void)
{
  GPIO_InitTypeDef GPIO_Initstructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE,ENABLE);
  GPIO_Initstructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_2|GPIO_Pin_4|GPIO_Pin_6;
  GPIO_Initstructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_Initstructure.GPIO_Speed=GPIO_Speed_50MHz;
  GPIO_Init(GPIOE,&GPIO_Initstructure);
}

void Motor_Forward(void)
{
	A1_On;
	A2_Off;
	B1_On;
	B2_Off;	
}
void Motor_Back(void)
{
	A1_Off;
	A2_On;
	B1_Off;
	B2_On;
}

void Motor_Stop(void)
{
	A1_Off;
	A2_Off;
	B1_Off;
	B2_Off;
}

void Motor_TurnRight(void)
{
A1_On;
	A2_Off;
	B1_Off;
	B2_Off;	
}
void Motor_TurnLeft(void)
{
 	 A1_Off;
	 A2_Off;
	 B1_Off;
	 B2_On;
}




void Delay_ms(uint32_t ms)    //利用系统SysTick延时
{
    uint32_t i;
	SysTick_Config(72000);
	for(i=0;i<ms;i++)
	{
		while(!((SysTick->CTRL)&(1<<16)));
	}
	SysTick->CTRL&=SysTick_CTRL_ENABLE_Msk;	
}



