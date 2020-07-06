#include "dac.h"
#include "math.h"
#include "TIM.h"

u32 Count=0;
extern u16 WAVE_DATA[accuracy];
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����:�¿���
//DAC ����	   
//�޸�����:2017/4/20
//�汾��V2.0
//��Ȩ���У�����ؾ���						  
//////////////////////////////////////////////////////////////////////////////////
//DACͨ��1�����ʼ��
void Dac1_Init(void)
{
  
	GPIO_InitTypeDef GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );	  //ʹ��PORTAͨ��ʱ��
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE );	  //ʹ��DACͨ��ʱ�� 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;				 // �˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN; 		 //ģ������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_SetBits(GPIOA,GPIO_Pin_4)	;//PA.4 �����
					
	DAC_InitType.DAC_Trigger=DAC_Trigger_None;	//��ʹ�ô������� TEN1=0
	DAC_InitType.DAC_WaveGeneration=DAC_WaveGeneration_None;//��ʹ�ò��η���
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude=DAC_LFSRUnmask_Bit0;//���Ρ���ֵ����
	DAC_InitType.DAC_OutputBuffer=DAC_OutputBuffer_Disable ;	//DAC1�������ر� BOFF1=1
  DAC_Init(DAC_Channel_1,&DAC_InitType);	 //��ʼ��DACͨ��1

	DAC_Cmd(DAC_Channel_1, ENABLE);  //ʹ��DAC1
  
  DAC_SetChannel1Data(DAC_Align_12b_R, 0);  //12λ�Ҷ������ݸ�ʽ����DACֵ

}

//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����:�¿���
//���Һ������η���	   
//�޸�����:2017/4/20
//�汾��V2.0
//��Ȩ���У�����ؾ���						  
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
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����:�¿���
//�����������η���	   
//�޸�����:2017/4/20
//�汾��V2.0
//��Ȩ���У�����ؾ���						  
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
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//����:�¿���
//���Ǻ������η���	   
//�޸�����:2017/4/20
//�汾��V2.0
//��Ȩ���У�����ؾ���						  
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

//����ͨ��1�����ѹ
//vol:0~3300,����0~3.3V
void Dac1_Set_Vol(unsigned int vol)
{
	float temp=vol;
	temp/=1000;
	temp=temp*4096/3.3;
	DAC_SetChannel1Data(DAC_Align_12b_R,temp);//12λ�Ҷ������ݸ�ʽ����DACֵ
}

///**********************************
//***********************************
//�ж�DAC   ���ߣ��¿���
//***********************************
//**********************************/
//void TIM6_IRQHandler(void)
//{ 	
//	if(Count<accuracy-1)
//		Count++;
//	else
//		Count=0;
//	
//	DAC_SetChannel1Data(DAC_Align_12b_R,WAVE_DATA[Count]);//����DACֵ
//	
//	TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
//	
//}



















































