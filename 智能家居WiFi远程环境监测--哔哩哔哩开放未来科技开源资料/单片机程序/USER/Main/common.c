#include "common.h"

static u8  fac_us=0;							//us��ʱ������			   
static u16 fac_ms=0;							//ms��ʱ������,��ucos��,����ÿ�����ĵ�ms��

/**********************************
***********************************
����ȡ����ƽ��ֵ    ���ߣ��¿���
ע��adcȡADC_1��ADC_2
    star���鿪ʼλ
    end�������λ
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
����ȡ����������   ���ߣ��¿���
ע��adcȡADC_1��ADC_2
    star���鿪ʼλ
    end�������λ
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
����ȡ��  ���ߣ��¿���
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
�����λ��ʾ����С   ���ߣ��¿���
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
�����λ��ʾ����С   ���ߣ��¿���
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
�����λ��ʾ����С   ���ߣ��¿���
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
��ʱ      ���ߣ��¿���
***********************************
**********************************/
void delay(u32 nCount)
{
	u32 count;
	for(;nCount>0;nCount--)
	  for(count=1000;count>0;count--);
}

/********************************************************************
				��ʱus,ms
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
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8);	//ѡ���ⲿʱ��  HCLK/8
	fac_us=SystemCoreClock/8000000;				//Ϊϵͳʱ�ӵ�1/8  
	fac_ms=(u16)fac_us*1000;					
}	 
//��ʱnus
//nusΪҪ��ʱ��us��.		    								   
void delay_us(u32 nus)
{		
	u32 temp;	    	 
	SysTick->LOAD=nus*fac_us; 					//ʱ�����	  		 
	SysTick->VAL=0x00;        					//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����	  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;      					 //��ռ�����	 
}
//��ʱnms
//ע��nms�ķ�Χ
//SysTick->LOADΪ24λ�Ĵ���,����,�����ʱΪ:
//nms<=0xffffff*8*1000/SYSCLK
//SYSCLK��λΪHz,nms��λΪms
//��72M������,nms<=1864 
void delay_ms(u16 nms)
{	 		  	  
	u32 temp;		   
	SysTick->LOAD=(u32)nms*fac_ms;				//ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL =0x00;							//��ռ�����
	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL =0X00;       					//��ռ�����	  	    
} 









