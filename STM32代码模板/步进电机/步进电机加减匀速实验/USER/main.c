/******************** (C) COPYRIGHT 2013 CEPARK多功能开发学习板********************
 * 文件名  ：main.c
 * 描述    ：当按下K1时 步进电机匀加速转动
						 当按下K2时 步进电机匀速转动
						 当按下K3时 步进电机匀减速转动
 * 实验平台：CEPARK多功能开发学习板
 * 库版本  ：ST3.5.0
 * 硬件连接：-----------------------
 * 单片机IO | PA0 - JP69 - key1     |独立按键模块
 *          | PA1 - 			 key2			|
 *          | PA2 - 			 key3     |
 *           -----------------------
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
#include "key.h"  

  
/* 
 * 函数名：main
 * 描述  : 主函数
 * 输入  ：无
 * 输出  : 无
 */
int main(void)
{  	
  	u8 i,j;
  	/* 设置系统时钟为72M */
  	SystemInit();
  	
  	Key_GPIO_Config();
  	
  	BUJIN_MOTOR_GPIO_Config();
  	
  	while (1)
  	{
    	
    	if( Key_Scan(GPIOA,GPIO_Pin_0) == KEY_ON  )
		{
			for(j=20;j>1;j--)
    		{
    			for(i=0;i<10;i++)
    			{
    				BJ_MOTOR1(j);	   //步进电机加速转动	
    			}
    		}		    
		}  
		if( Key_Scan(GPIOA,GPIO_Pin_1) == KEY_ON  )
		{
			for(j=1;j<20;j++)
    		{
    			for(i=0;i<10;i++)
    			{
    				BJ_MOTOR1(5);	   //步进电机匀速转动	
    			}
    		}			    
		}  
		if( Key_Scan(GPIOA,GPIO_Pin_2) == KEY_ON  )
		{
			for(j=1;j<20;j++)
    		{
    			for(i=0;i<10;i++)
    			{
    				BJ_MOTOR1(j);	   //步进电机减速转动	
    			} 
    		}			    
		}  
  	}
}




/******************* (C) COPYRIGHT 2013 CEPARK多功能开发学习板*****END OF FILE****/
