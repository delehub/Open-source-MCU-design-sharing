/******************** (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��********************
 * �ļ���  ��key.c
 * ����    ������Ӧ�ú�����        
 * ʵ��ƽ̨��CEPARK�๦�ܿ���ѧϰ��
 * Ӳ�����ӣ�-------------------------
 *          | PA0 - key1             |
 *          | PA1 - key2			 			 |
 *          | PA2 - key3             |
 *          | PA3 - key4						 |
 *          | PA4 - key5             |
 *          | PA5 - key6			  		 |
 *          | PA6 - key7             |
 *          | PA7 - key8			 			 |
 *           -------------------------
 * ��汾  ��ST3.5.0
**********************************************************************************/

#include "key.h" 
#include "delay.h" 

 /*
 * ��������Key_GPIO_Config
 * ����  �����ð����õ���I/O��
 * ����  ����
 * ���  ����
 */
void Key_GPIO_Config(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;

  	/*���������˿ڣ�PB0����ʱ��*/
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7; 
 	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 

	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

 /*
 * ��������Key_Scan
 * ����  ������Ƿ��а�������
 * ����  ��GPIOx��x ������ A��B��C��D���� E
 *		     GPIO_Pin������ȡ�Ķ˿�λ 	
 * ���  ��KEY_OFF(û���°���)��KEY_ON�����°�����
 */
u8 Key_Scan(GPIO_TypeDef* GPIOx,u16 GPIO_Pin)
{			
		/*����Ƿ��а������� */
   	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON ) 
	  {	   
	 	 /*��ʱ����*/
	  	delay_ms(30);		
	   		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
					{	 
						/*�ȴ������ͷ� */
						//while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   
			 			return 	KEY_ON;	 
					}
			else
					return KEY_OFF;
		}
	else
		return KEY_OFF;
}
