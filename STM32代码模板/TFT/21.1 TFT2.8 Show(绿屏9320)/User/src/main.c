/********************************************************************
//STM32��������2.8��TFT��������ʾ���ֲ��Գ���
//��ʾ���֡��ַ��������Լ�GUI��ͼ�ȹ���
//��ʾֻ��Ҫ������ʾ���ֵĿ����ߺ������ߣ�������user_Config.h�ļ���
********************************************************************/

/********************************************************************
				����ͷ�ļ�
********************************************************************/
#include "stm32f10x.h"                   //STM32�����Ĵ�������ͷ�ļ����������
#include "user_Config.h"                 //�û�����ͷ�ļ�����������Ӳ��������Դ,λ����Ŀ�ļ�����
#include "TFT28.h"											 //TFT��صĺ�������ͷ�ļ�

unsigned int Device_code;                //TFT����IC�ͺţ�2.8��ΪILI9320

GPIO_InitTypeDef GPIO_InitStructure;     //����һ���ṹ�����GPIO_InitStructure�����ڳ�ʼ��GPIO����
ErrorStatus HSEStartUpStatus;

/********************************************************************
				��ͨ��ʱ����
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
				GPIO��ʼ������
********************************************************************/
void GPIO_Config(void)
{
	/* �������ݿڵ�GPIO�ܽ�ģʽ�����ģʽ*/
  	RCC_APB2PeriphClockCmd(RCC_GPIO_TFT, ENABLE); 					//ʹ��GPIOʱ��
  	GPIO_InitStructure.GPIO_Pin = D0|D1|D2|D3|D4|D5|D6|D7; //ʹ��PA0~PA7
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO���������ģʽ
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  	GPIO_Init(GPIO_TFT_DATA, &GPIO_InitStructure);  				//��ص�GPIO�ڳ�ʼ��
		
		/* ���ÿ��Ƶ�GPIO�ܽ�ģʽ�����ģʽ*/
  	RCC_APB2PeriphClockCmd(RCC_GPIO_CTRB, ENABLE); 					//ʹ��GPIOʱ��
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10 |GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13; //ʹ��PB8.9.10.11.12.13
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;				//GPIO���������ģʽ
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  	GPIO_Init(GPIO_CTRB, &GPIO_InitStructure);  						//��ص�GPIO�ڳ�ʼ��
		
		GPIO_ResetBits(GPIO_CTRB,GPIO_Pin_11);
}


/********************************************************************
                      ������
********************************************************************/
int main(void)
{
  u16 i;
	GPIO_Config();															//GPIO��ʼ�����ã����LED�ƽӿ�����
  Device_code=0x9320;                					//TFT����IC�ͺţ�����ʵ�������ͺţ�Ŀǰ��9320��9328����
  TFT_Initial();                     					//��ʼ��LCD	 

  while(1)                           					//ѭ��ִ�г���
   {
		 //5����ɫ����Ļ��Ϊ5������
	   Show_RGB(0,240,0,64,Blue);
	   Show_RGB(0,240,64,128,Green);
	   Show_RGB(0,240,128,192,Magenta);
	   Show_RGB(0,240,192,256,Red);
	   Show_RGB(0,240,256,320,Yellow);
		 
		 //��һ��������ʾ16X16����
		 LCD_PutString(24,16,"  �Ϸ�쿻͵������޹�˾",White,Blue);
     LCD_PutString(24,40,"   �����ѧ  ���򿪷�",White,Blue);
		 
		 //�ڶ���������ʾAscii�ַ��е����ֺͷ���
		 LCD_PutString(80,72,"0123456789",Black,Green);
	   LCD_PutString(16,96,"-)(-/<>;:[]{}\|?-=+*&^%$",Black,Green);
		 
		 //������������ʾAscii�ַ�����ĸ
		 LCD_PutString(16,136,"abcdefghijklmnopqrstuvwxyz",Blue,Magenta);
	   LCD_PutString(16,156,"ABCDEFGHIJKLMNOPQRSTUVWXYZ",Blue,Magenta);
		 
		 //���ĸ�������ʾTFT������IC�ͺ�
		 LCD_PutString(16,200,"The Device IC Of TFT Is:",Black,Red);
	   LCD_PutString(96,224,"ILI",Black,Red);
	   LCD_PutChar(120, 224, 0x30+(Device_code>>12), Black, Red);
	   LCD_PutChar(128, 224, 0x30+((Device_code>>8)&0x000f), Black, Red);
	   LCD_PutChar(136, 224, 0x30+((Device_code>>4)&0x000f), Black, Red);
	   LCD_PutChar(144, 224, 0x30+(Device_code&0x000f), Black, Red);
		 
		 //�����������ʵ�ֻ���
		 for(i=312;i>264;i--){ Put_pixel(68,i,Blue);}
	   for(i=68;i<172;i++) { Put_pixel(i,264,Blue);}
     for(i=264;i<312;i++){ Put_pixel(172,i,Blue);} 
	   for(i=172;i>68;i--) { Put_pixel(i,312,Blue);}
		  
     delay_ms(20000); //��ʾһ��ʱ��
   }  
}


