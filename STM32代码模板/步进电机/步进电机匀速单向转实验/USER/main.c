/******************** (C) COPYRIGHT 2013 CEPARK多功能开发学习板********************
 * 文件名  ：main.c
 * 描述    ：步进电机朝一个方向转动         
 * 实验平台：CEPARK多功能开发学习板
 * 库版本  ：ST3.5.0
 * 硬件连接：------------------------
 * 单片机IO |   PB15 - JP32 - IN1    |电极驱动模块
 *          |   PB14 - 				IN2    |
 *          |   PB13 - 				IN3    |
 *          |   PB12 - 				IN4    |
 *           ------------------------ 
 * 硬件连接：步进电极连接到电极驱动模块的JP34
**********************************************************************************/

#include "stm32f10x.h"
#include "bujin_motor.h"
#include "delay.h"

/* 
 * 函数名：main
 * 描述  : 主函数
 * 输入  ：无
 * 输出  : 无
 */
int main(void)
{
  	u8 speed=5;
  	
  	/* 设置系统时钟为72M */
  	SystemInit();
  	
  	BUJIN_MOTOR_GPIO_Config();
  	
  	while (1)
  	{
    	BJ_MOTOR1(speed);	   //步进电机均速转动
  	}
}




/******************* (C) COPYRIGHT 2013 CEPARK多功能开发学习板*****END OF FILE****/
