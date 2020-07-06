#include "dac.h"
#include "math.h"
#include "TIM.h"

u32 Count=0;
extern u16 WAVE_DATA[accuracy];
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//作者:陈开放
//DAC 代码	   
//修改日期:2017/4/20
//版本：V2.0
//版权所有，盗版必究。						  
//////////////////////////////////////////////////////////////////////////////////
//DAC通道1输出初始化
void Dac1_Init(void)
{
  
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //使能PORTA通道时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //使能DAC通道时钟 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // 端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //模拟输入
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4)	;//PA.4 输出高
					
	DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//不使用触发功能 TEN1=0
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//不使用波形发生
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//屏蔽、幅值设置
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1输出缓存关闭 BOFF1=1
  DAC_Init(DAC_Channel_1,&DAC_InitType);	 //初始化DAC通道1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //使能DAC1
  
  DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12位右对齐数据格式设置DAC值

}

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//作者:陈开放
//正弦函数波形发生	   
//修改日期:2017/4/20
//版本：V2.0
//版权所有，盗版必究。						  
//////////////////////////////////////////////////////////////////////////////////

void Sin_Fun(u16 AM,u16* WAVE_DATA)
{
	u32 count=0;
	
	for(count=0;count<accuracy;count++)
	{
		WAVE_DATA[count]=AM/2*sin(count*3.14/(accuracy/2))+AM/2;		
	}	
}

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//作者:陈开放
//方波函数波形发生	   
//修改日期:2017/4/20
//版本：V2.0
//版权所有，盗版必究。						  
//////////////////////////////////////////////////////////////////////////////////

void Square_Fun(u16 AM_H,u16 AM_L,u16* WAVE_DATA)
{
	u32 count=0;
	
	for(count=0;count<accuracy/2;count++)
	{
		WAVE_DATA[count]=AM_H;		
	}
  for(count=accuracy/2;count<accuracy;count++)
	{
	  WAVE_DATA[count]=AM_L;	
	}
}

//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//作者:陈开放
//三角函数波形发生	   
//修改日期:2017/4/20
//版本：V2.0
//版权所有，盗版必究。						  
//////////////////////////////////////////////////////////////////////////////////

void Triangle_Fun(u16 AM_H,u16 AM_L,u16* WAVE_DATA)
{
	u32 count=0;
	u16 Step=0;
	
	Step=(AM_H-AM_L)/(accuracy/2);
	for(count=0;count<accuracy/2;count++)
	{
		WAVE_DATA[count]=AM_L+count*Step;		
	}
  for(count=accuracy/2;count<accuracy;count++)
	{
	  WAVE_DATA[count]=AM_H-(count-accuracy/2)*Step;	
	}
}

//设置通道1输出电压
//vol:0~3300,代表0~3.3V
void Dac1_Set_Vol(unsigned int vol)
{
	float temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12位右对齐数据格式设置DAC值
}

///**********************************
//***********************************
//中断DAC   作者：陈开放
//***********************************
//**********************************/
//void TIM6_IRQHandler(void)
//{ 	
//	if(Count<accuracy-1)
//		Count++;
//	else
//		Count=0;
//	
//	DAC_SetChannel1Data(DAC_Align_12b_R,WAVE_DATA[Count]);//设置DAC值
//	
//	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
//	
//}



















































