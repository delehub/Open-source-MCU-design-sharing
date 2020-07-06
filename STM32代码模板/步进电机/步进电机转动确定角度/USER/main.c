/******************** (C) COPYRIGHT 2013 CEPARK多功能开发学习板********************
 * 文件名  ：main.c
 * 描述    ：电极转动确定的90度后就停止
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
  	u8 i,j;
	  u8 angle=90;
	  u8 xunhuan=0;
  	/* 设置系统时钟为72M */
  	SystemInit();
  	
  	BUJIN_MOTOR_GPIO_Config();
	
		xunhuan=angle/5.625;   //90/5.625
	
		for(j=0;j<xunhuan;j++)	//电机转动90度
		{
			for(i=0;i<8;i++)
    	{
    		BJ_MOTOR_8P_1(5);	//每个循环8拍 根据28BYJ-48步进电机的资料可知 电机每转过64拍就转动5.625度
    	}
		}
  	
  	while (1)
  	{
				;
  	}
}




/******************* (C) COPYRIGHT 2013 CEPARK多功能开发学习板*****END OF FILE****/
