/******************** (C) COPYRIGHT 2013 CEPARK多功能开发学习板********************
 * 文件名  ：led.c
 * 描述    ：led 应用函数库
 *          
 * 实验平台：CEPARK多功能开发学习板
 * 硬件连接：-----------------
 *          |   PA0 - LED1    |
 *          |   PA1 - LED2    |
 *          |   PA2 - LED3    |
 *          |   PA3 - LED4    |
 *          |   PA4 - LED5    |
 *          |   PA5 - LED6    |
 *          |   PA6 - LED7    |
 *          |   PA7 - LED8    |
 *           ----------------- 																						 
**********************************************************************************/

#include "led.h"

/*
 * 函数名：LED_GPIO_Config
 * 描述  ：配置LED用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
void LED_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 );	 // turn off all led
}


/******************* (C) COPYRIGHT 2013 CEPARK多功能开发学习板*****END OF FILE****/
