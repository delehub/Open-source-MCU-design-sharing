/********************************************************************
//STM32核心驱动2.8寸TFT触摸屏显示部分测试程序
//显示汉字、字符、清屏以及GUI绘图等功能
//显示只需要配置显示部分的控制线和数据线，配置在user_Config.h文件中
********************************************************************/

/********************************************************************
				包含头文件
********************************************************************/
#include "stm32f10x.h"                   //STM32器件寄存器定义头文件，必须包含
#include "user_Config.h"                 //用户配置头文件，用于配置硬件连接资源,位于项目文件夹下
#include "TFT28.h"											 //TFT相关的函数声明头文件

unsigned int Device_code;                //TFT控制IC型号，2.8寸为ILI9320

GPIO_InitTypeDef GPIO_InitStructure;     //定义一个结构体变量GPIO_InitStructure，用于初始化GPIO操作
ErrorStatus HSEStartUpStatus;

/********************************************************************
				普通延时函数
********************************************************************/
void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}

void delay_ms(unsigned int nCount)
{
      int i,j;                                                                                
    for(i=0;i<nCount;i++)                                                                    
       {
	     for(j=0;j<0x3000;j++);
       }
}

/********************************************************************
				GPIO初始化函数
********************************************************************/
void GPIO_Config(void)
{
	/* 配置数据口的GPIO管脚模式，输出模式*/
  	RCC_APB2PeriphClockCmd(RCC_GPIO_TFT, ENABLE); 					//使能GPIO时钟
  	GPIO_InitStructure.GPIO_Pin = D0|D1|D2|D3|D4|D5|D6|D7; //使用PA0~PA7
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO工作在输出模式
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  	GPIO_Init(GPIO_TFT_DATA, &GPIO_InitStructure);  				//相关的GPIO口初始化
		
		/* 配置控制的GPIO管脚模式，输出模式*/
  	RCC_APB2PeriphClockCmd(RCC_GPIO_CTRB, ENABLE); 					//使能GPIO时钟
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10 |GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13; //使用PB8.9.10.11.12.13
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO工作在输出模式
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  	GPIO_Init(GPIO_CTRB, &GPIO_InitStructure);  						//相关的GPIO口初始化
		
		GPIO_ResetBits(GPIO_CTRB,GPIO_Pin_11);
}


/********************************************************************
                      主函数
********************************************************************/
int main(void)
{
  u16 i;
	GPIO_Config();															//GPIO初始化配置，针对LED灯接口配置
  Device_code=0x9320;                					//TFT控制IC型号，根据实物设置型号，目前有9320和9328两种
  TFT_Initial();                     					//初始化LCD	 

  while(1)                           					//循环执行程序
   {
		 //5种颜色将屏幕分为5个区域
	   Show_RGB(0,240,0,64,Blue);
	   Show_RGB(0,240,64,128,Green);
	   Show_RGB(0,240,128,192,Magenta);
	   Show_RGB(0,240,192,256,Red);
	   Show_RGB(0,240,256,320,Yellow);
		 
		 //第一个区域显示16X16汉字
		 LCD_PutString(24,16,"  合肥炜煌电子有限公司",White,Blue);
     LCD_PutString(24,40,"   面向教学  面向开发",White,Blue);
		 
		 //第二个区域显示Ascii字符中的数字和符号
		 LCD_PutString(80,72,"0123456789",Black,Green);
	   LCD_PutString(16,96,"-)(-/<>;:[]{}\|?-=+*&^%$",Black,Green);
		 
		 //第三个区域显示Ascii字符中字母
		 LCD_PutString(16,136,"abcdefghijklmnopqrstuvwxyz",Blue,Magenta);
	   LCD_PutString(16,156,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",Blue,Magenta);
		 
		 //第四个区域显示TFT控制器IC型号
		 LCD_PutString(16,200,"The Device IC Of TFT Is:",Black,Red);
	   LCD_PutString(96,224,"ILI",Black,Red);
	   LCD_PutChar(120, 224, 0x30+(Device_code>>12), Black, Red);
	   LCD_PutChar(128, 224, 0x30+((Device_code>>8)&0x000f), Black, Red);
	   LCD_PutChar(136, 224, 0x30+((Device_code>>4)&0x000f), Black, Red);
	   LCD_PutChar(144, 224, 0x30+(Device_code&0x000f), Black, Red);
		 
		 //第五个区域打点实现画线
		 for(i=312;i>264;i--){ Put_pixel(68,i,Blue);}
	   for(i=68;i<172;i++) { Put_pixel(i,264,Blue);}
     for(i=264;i<312;i++){ Put_pixel(172,i,Blue);} 
	   for(i=172;i>68;i--) { Put_pixel(i,312,Blue);}
		  
     delay_ms(20000); //显示一段时间
   }  
}


