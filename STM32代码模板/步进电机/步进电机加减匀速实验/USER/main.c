/******************** (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��********************
 * �ļ���  ��main.c
 * ����    ��������K1ʱ ��������ȼ���ת��
						 ������K2ʱ �����������ת��
						 ������K3ʱ ��������ȼ���ת��
 * ʵ��ƽ̨��CEPARK�๦�ܿ���ѧϰ��
 * ��汾  ��ST3.5.0
 * Ӳ�����ӣ�-----------------------
 * ��Ƭ��IO | PA0 - JP69 - key1     |��������ģ��
 *          | PA1 - 			 key2			|
 *          | PA2 - 			 key3     |
 *           -----------------------
 * Ӳ�����ӣ�------------------------
 * ��Ƭ��IO |   PB15 - JP32 - IN1    |�缫����ģ��
 *          |   PB14 - 				IN2    |
 *          |   PB13 - 				IN3    |
 *          |   PB12 - 				IN4    |
 *           ------------------------ 
 * Ӳ�����ӣ������缫���ӵ��缫����ģ���JP34

**********************************************************************************/

#include "stm32f10x.h"
#include "bujin_motor.h"
#include "delay.h"    
#include "key.h"  

  
/* 
 * ��������main
 * ����  : ������
 * ����  ����
 * ���  : ��
 */
int main(void)
{  	
  	u8 i,j;
  	/* ����ϵͳʱ��Ϊ72M */
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
    				BJ_MOTOR1(j);	   //�����������ת��	
    			}
    		}		    
		}  
		if( Key_Scan(GPIOA,GPIO_Pin_1) == KEY_ON  )
		{
			for(j=1;j<20;j++)
    		{
    			for(i=0;i<10;i++)
    			{
    				BJ_MOTOR1(5);	   //�����������ת��	
    			}
    		}			    
		}  
		if( Key_Scan(GPIOA,GPIO_Pin_2) == KEY_ON  )
		{
			for(j=1;j<20;j++)
    		{
    			for(i=0;i<10;i++)
    			{
    				BJ_MOTOR1(j);	   //�����������ת��	
    			} 
    		}			    
		}  
  	}
}




/******************* (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��*****END OF FILE****/
