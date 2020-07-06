#include "common.h"

static u8  fac_us=0;							//us延时倍乘数			   
static u16 fac_ms=0;							//ms延时倍乘数,在ucos下,代表每个节拍的ms数

/**********************************
***********************************
数组取段求平均值    作者：陈开放
注：adc取ADC_1，ADC_2
    star数组开始位
    end数组结束位
***********************************
**********************************/
u8 average(u8 *adc,u16 star,u16 end)
{
	u16 temp;
  u16 sum=0;
	for(temp=star;temp<end;temp++)
	  sum=sum+adc[temp];
  return (sum/(end-star));
}

/**********************************
***********************************
数组取段升序排序   作者：陈开放
注：adc取ADC_1，ADC_2
    star数组开始位
    end数组结束位
***********************************
**********************************/
void sort(u8 *adc,u16 star,u16 end)
{
	u16 i,j,t;
	for(j=star;j<end-1;j++)
	{
		for(i=j+1;i<end;i++)
		{
			if(adc[j]>adc[i])
			{
			t=adc[j];
			adc[j]=adc[i];
			adc[i]=t;
			}
		}
	}
}
/**********************************
***********************************
变量取正  作者：陈开放
***********************************
**********************************/
u16 ABS(int Data)
{
	if(Data<0)
		Data=0;
	
	return Data;
}

/**********************************
***********************************
计算各位显示数大小   作者：陈开放
***********************************
**********************************/
void Display_TH(u16 value,u8 *BUFF)
{
	*(BUFF+2)=value/1000+0x30;
	*(BUFF+3)=value%1000/100+0x30;
	*(BUFF+4)=value%1000%100/10+0x30;
	*(BUFF+6)= value%1000%100%10+0x30;
}
/**********************************
***********************************
计算各位显示数大小   作者：陈开放
***********************************
**********************************/
void Display_P(u16 value,u8 *BUFF)
{
	*(BUFF+6)=value/100+0x30;
	*(BUFF+7)=value%100/10+0x30;
	*(BUFF+8)=value%100%10+0x30;
}
/**********************************
***********************************
计算各位显示数大小   作者：陈开放
***********************************
**********************************/
void Display_G(u16 value,u8 *BUFF)
{
	*(BUFF+2)=value/100+0x30;
	*(BUFF+3)=value%100/10+0x30;
	*(BUFF+4)=value%100%10+0x30;
}
/**********************************
***********************************
延时      作者：陈开放
***********************************
**********************************/
void delay(u32 nCount)
{
	u32 count;
	for(;nCount>0;nCount--)
	  for(count=1000;count>0;count--);
}

/********************************************************************
				延时us,ms
********************************************************************/
void delayus(unsigned int time)
{
 unsigned int i=0;
	while(time--)
	{
		i=10;
		while(i--);		
	}
}

void delayms(unsigned int time)
{
 unsigned int i=0;
	while(time--)
	{
		i=12000;
		while(i--);		
	}
}


void delay_init()
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//选择外部时钟  HCLK/8
	fac_us=SystemCoreClock/8000000;				//为系统时钟的1/8  
	fac_ms=(u16)fac_us*1000;					
}	 
//延时nus
//nus为要延时的us数.		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//时间加载	  		 
	SysTick->VAL=0x00;        					//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;      					 //清空计数器	 
}
//延时nms
//注意nms的范围
//SysTick->LOAD为24位寄存器,所以,最大延时为:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK单位为Hz,nms单位为ms
//对72M条件下,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;				//时间加载(SysTick->LOAD为24bit)
	SysTick->VAL =0x00;							//清空计数器
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL =0X00;       					//清空计数器	  	    
} 









