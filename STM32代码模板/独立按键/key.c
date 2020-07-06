#include"key.h"
void KEY_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;         //定义结构体指针变量
	RCC_APB2PeriphClockCmd(KEY1_GPIO_CLK|KEY2_GPIO_CLK,ENABLE);  
 //开启按键端口的时钟
	/*按键输入控制GPIO端口的步骤*/
	/*
	  {
   1.选择按键的引脚
   2.设置按键的引脚为浮空输入
   3.使用结构体初始化按键
   }
	*/
  //key1
	GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(KEY1_GPIO_PORT, &GPIO_InitStructure);
	//key2
	GPIO_InitStructure.GPIO_Pin = KEY2_GPIO_PIN; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(KEY2_GPIO_PORT, &GPIO_InitStructure);	
	
}
 /*
 * 函数名：Key_Scan
 * 描述  ：检测是否有按键按下
 * 输入  ：GPIOx：x 可以是 A，B，C，D或者 E
 *		     GPIO_Pin：待读取的端口位 	
 * 输出  ：KEY_OFF(没按下按键)、KEY_ON（按下按键）
 */
uint8_t Key_Scan(GPIO_TypeDef* GPIOx,uint16_t GPIO_Pin)
{	/*检测是否有按键按下 */
	if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON )  
	{	 /*等待按键释放 *///松手检测
		while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == KEY_ON);   	
		return 	KEY_ON;	 
	}
	else
		return KEY_OFF;
}