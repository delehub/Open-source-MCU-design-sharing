#include "Touch.h"
	
u16 vx=15242,vy=11131;  //�������ӣ���ֵ����1000֮���ʾ���ٸ�ADֵ����һ�����ص�
u16 chx=3898,chy=145;   //Ĭ�����ص�����Ϊ0ʱ��AD��ʼֵ

void Touch_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
		
	//TFT_Touch//PC6_IRQ//PC7_DOUT//PC9_DIN//PC10_CS//PC11_DCLK
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;														   
	GPIO_InitStructure.GPIO_Pin =GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;	 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}
/**********************************
***********************************
SPIд����  ���ߣ��¿���
ע����������Ч
***********************************
**********************************/
void WriteCharTo7843(unsigned char date)          
{
	unsigned char count=0;
	REDCLK;
	for(count=0;count<8;count++)
	{
	if((0X80>>count)&date)
		 DIN;        //GPIOE,GPIO_Pin_12//DIN
	else
		 REDIN;      //GPIOE,GPIO_Pin_12//DIN
	REDCLK;  Delay_Touch(1);           
	DCLK;    Delay_Touch(1);    
  }
}

/**********************************
***********************************
SPI������  ���ߣ��¿���
ע���½�����Ч
***********************************
**********************************/
u16 ReadFromCharFrom7843(void)           
{
	u8 count=0;
	u16 Num=0;
	for(count=0;count<12;count++)
	{
		Num<<=1;		
		DCLK;    Delay_Touch(1);          
		REDCLK;  Delay_Touch(1);  
		if(DOUT)
			Num|=1;	
	}
	
  return(Num);
}	
	  
/**********************************
***********************************
��ȡadcֵ      ���ߣ��¿���
ע��0X90��Y  0XD0��X
***********************************
**********************************/
u16 ADS_Read_AD(unsigned char CMD)          
{
	u16 l;
	RECS;
	WriteCharTo7843(CMD);       
	DCLK;   Delay_Touch(1);  
	REDCLK; Delay_Touch(1); 
	l=ReadFromCharFrom7843();
	CS;
	
	return l;
}	

/**********************************
***********************************
ȥ���ȡ����ֵ   ���ߣ��¿���
ע��ȥ����ͺ����LOST_VAL����,
     ȡƽ��ֵ
***********************************
**********************************/
#define READ_TIMES 10 //��ȡ����
#define LOST_VAL 3	  //����ֵ
u16 ADS_Read_XY(u8 CMD)
{
	u16 i, j;
	u16 buf[READ_TIMES];
	u16 sum=0;
	u16 temp;
	for(i=0;i<READ_TIMES;i++)
	{				 
		buf[i]=ADS_Read_AD(CMD);	    
	}
	for(i=0;i<READ_TIMES-1; i++)//��������
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	
 
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)
	   sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	
	return temp;   
} 

/**********************************
***********************************
�˲�������ֵ   ���ߣ��¿���
ע�����˲��������ȡ
    ��Сֵ��������100.
***********************************
**********************************/
u8 Read_ADS(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=ADS_Read_XY(CMD_RDX);
	ytemp=ADS_Read_XY(CMD_RDY);	 									   
	if(xtemp<100||ytemp<100)
		return 0;  //����ʧ��
	
	*x=xtemp;
	*y=ytemp;
	return 1;    //�����ɹ�
}
//2�ζ�ȡADS7846,������ȡ
//50,��������,����Ϊ������ȷ,�����������.

	   

/**********************************
***********************************
��ȡADC����ֵ   ���ߣ��¿���
ע��2�ζ�ADֵ,�����ε�ƫ�����20
    �ú����ܴ�����׼ȷ��
***********************************
**********************************/
#define ERR_RANGE 20 //��Χ 
u8 Read_ADS2(TP_PIX *tp_pix) 
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=Read_ADS(&x1,&y1);   
    if(flag==0)return(0);
    flag=Read_ADS(&x2,&y2);	
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//ǰ�����β�����+-ERR_RANGE��
    &&((y2<=y1&&y1<y2+ERR_RANGE)||(y1<=y2&&y2<y1+ERR_RANGE)))
    {
        tp_pix->x=(x1+x2)>>1;
        tp_pix->y=(y1+y2)>>1;		
        return 1;
    }
		else return 0;	  
}   
	   
/**********************************
***********************************
��ȡ����      ���ߣ��¿���
***********************************
**********************************/
u8 Convert_Pos(TP_PIX *tp_pix)
{		 	 
	u8 l=0; 
	if(Read_ADS2(tp_pix))
	{
		l=1;
		tp_pix->x=tp_pix->x>chx?((u32)tp_pix->x-(u32)chx)*1000/vx:((u32)chx-(u32)tp_pix->x)*1000/vx;
		tp_pix->y=tp_pix->y>chy?((u32)tp_pix->y-(u32)chy)*1000/vy:((u32)chy-(u32)tp_pix->y)*1000/vy;
		tp_pix->x=240-tp_pix->x;
	}
	return l;
}

/**********************************
***********************************
��ʱ      ���ߣ��¿���
***********************************
**********************************/
void Delay_Touch(u32 nCount)
{
	u32 count;
	for(;nCount>0;nCount--)
	  for(count=1;count>0;count--);
}	

