#include "AD.h"

void Delay(u32 Delayms);
/**********************************
***********************************
ADC初始化  作者：陈开放
***********************************
**********************************/
void ADC_Configuration(void)
{
	ADC_InitTypeDef ADC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;			

	//ADC采集口
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_2;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
	ADC_InitStructure.ADC_Mode=ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode=ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode=DISABLE;
	ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign=ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel=2;
	ADC_Init(ADC1,&ADC_InitStructure);
   
	ADC_ExternalTrigInjectedConvConfig(ADC1,ADC_ExternalTrigInjecConv_None); 
	ADC_InjectedSequencerLengthConfig(ADC1, 2);
	ADC_InjectedChannelConfig(ADC1,ADC_Channel_0, 1, ADC_SampleTime_239Cycles5);
	ADC_InjectedChannelConfig(ADC1,ADC_Channel_2 , 2, ADC_SampleTime_239Cycles5);
	ADC_SetInjectedOffset(ADC1,ADC_InjectedChannel_1,0);
	ADC_SetInjectedOffset(ADC1,ADC_InjectedChannel_2,0);
	
	ADC_Cmd(ADC1,ENABLE);
}

/**********************************
***********************************
获取有害气体  
***********************************
**********************************/
u16 Get_Gas()
{
	u16 Gas_Buff=0;
	
	ADC_SoftwareStartInjectedConvCmd(ADC1,ENABLE);
	while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
	Gas_Buff=ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_2);//读取有害气体值
	
	return Gas_Buff;
}
/**********************************
***********************************
获取PM2.5  
***********************************
**********************************/
u16 Get_PM2_5()
{
	u8 count=0;
	u32 PM_25_Buff=0;
	
	for(count=0;count<5;count++)
	{
		GPIO_BitWrite(GPIOA,GPIO_Pin_1,1);
		delay_us(280);
		ADC_SoftwareStartInjectedConvCmd(ADC1,ENABLE);
		while(!ADC_GetFlagStatus(ADC1,ADC_FLAG_EOC));
		PM_25_Buff=ADC_GetInjectedConversionValue(ADC1, ADC_InjectedChannel_1)+PM_25_Buff;//读取有害气体值
		delay_us(40);
		GPIO_BitWrite(GPIOA,GPIO_Pin_1,0);
		delay_us(9680);
	}
	return (u16)(PM_25_Buff/5);
}






