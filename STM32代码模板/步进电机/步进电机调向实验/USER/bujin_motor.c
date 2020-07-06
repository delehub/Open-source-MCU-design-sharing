/******************** (C) COPYRIGHT 2013 CEPARK多功能开发学习板********************
 * 文件名  ：bujin_motor.c
 * 描述    ：bujin_motor 应用函数库
 *          
 * 实验平台：CEPARK多功能开发学习板
 * 硬件连接：-----------------
 *          |   PB15 - IN1    |
 *          |   PB14 - IN2    |
 *          |   PB13 - IN3    |
 *          |   PB12 - IN4    |
 *           ----------------- 																						 
**********************************************************************************/

#include "bujin_motor.h"   
#include "delay.h"   

/*
 * 函数名：BUJIN_MOTOR_GPIO_Config
 * 描述  ：配置步进电机用到的I/O口
 * 输入  ：无
 * 输出  ：无
 */
void BUJIN_MOTOR_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB, ENABLE);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void BJ_MOTOR_8P_1(u8 Speed)	//步进电机顺时针匀速转动
{
	Coil_A       
    delay_ms(Speed);
    Coil_DA                 	//遇到Coil_AB1  用{A1=1;B1=1;C1=0;D1=0;}代替
    delay_ms(Speed);         	//改变这个参数可以调整电机转速 ,
                            	//数字越小，转速越大,力矩越小
	Coil_D      
    delay_ms(Speed);
    Coil_CD
    delay_ms(Speed);
	Coil_C       
    delay_ms(Speed);
    Coil_BC
    delay_ms(Speed);
	Coil_B       
    delay_ms(Speed);
    Coil_AB
    delay_ms(Speed);
}

void BJ_MOTOR_8P_2(u8 Speed)	//步进电机逆时针匀速转动
{
	Coil_A       
    delay_ms(Speed);
    Coil_AB                		//遇到Coil_AB1  用{A1=1;B1=1;C1=0;D1=0;}代替
    delay_ms(Speed);         	//改变这个参数可以调整电机转速 ,
                            	//数字越小，转速越大,力矩越小
	Coil_B       
    delay_ms(Speed);
    Coil_BC
    delay_ms(Speed);
	Coil_C       
    delay_ms(Speed);
    Coil_CD
    delay_ms(Speed);
	Coil_D       
    delay_ms(Speed);
    Coil_DA
    delay_ms(Speed);
}





/******************* (C) COPYRIGHT 2013 CEPARK多功能开发学习板*****END OF FILE****/
