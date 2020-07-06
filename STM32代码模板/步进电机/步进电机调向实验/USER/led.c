/******************** (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��********************
 * �ļ���  ��led.c
 * ����    ��led Ӧ�ú�����
 *          
 * ʵ��ƽ̨��CEPARK�๦�ܿ���ѧϰ��
 * Ӳ�����ӣ�-----------------
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
 * ��������LED_GPIO_Config
 * ����  ������LED�õ���I/O��
 * ����  ����
 * ���  ����
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


/******************* (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��*****END OF FILE****/
