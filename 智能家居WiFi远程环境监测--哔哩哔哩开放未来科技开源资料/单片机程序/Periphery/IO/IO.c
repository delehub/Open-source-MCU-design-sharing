#include "IO.h"

/**********************************
***********************************
GPIO初始化   作者：陈开放
***********************************
**********************************/
void GPIO_Config(void)
{		
	  GPIO_InitTypeDef GPIO_InitStructure;
	
	  //蜂鸣器
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	  GPIO_Init(GPIOB,&GPIO_InitStructure);
		GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);//初始化关蜂鸣器	
	
		//PM2.5控制脚
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	  GPIO_Init(GPIOA,&GPIO_InitStructure);
		GPIO_WriteBit(GPIOA,GPIO_Pin_1,Bit_RESET);//初始化
	
		//按键
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
		GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11;
	  GPIO_InitStructure.GPIO_Speed=GPIO_Speed_10MHz;
	  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	  GPIO_Init(GPIOB,&GPIO_InitStructure);
		GPIO_WriteBit(GPIOB,GPIO_Pin_1|GPIO_Pin_10|GPIO_Pin_11,Bit_SET);//初始化
}


