#include "Touch.h"
	
u16 vx=15242,vy=11131;  //比例因子，此值除以1000之后表示多少个AD值代表一个像素点
u16 chx=3898,chy=145;   //默认像素点坐标为0时的AD起始值

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
SPI写数据  作者：陈开放
注：上升沿有效
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
SPI读数据  作者：陈开放
注：下降沿有效
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
读取adc值      作者：陈开放
注：0X90读Y  0XD0读X
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
去噪读取坐标值   作者：陈开放
注：去掉最低和最高LOST_VAL个数,
     取平均值
***********************************
**********************************/
#define READ_TIMES 10 //读取次数
#define LOST_VAL 3	  //丢弃值
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
	for(i=0;i<READ_TIMES-1; i++)//升序排列
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
滤波读坐标值   作者：陈开放
注：带滤波的坐标读取
    最小值不能少于100.
***********************************
**********************************/
u8 Read_ADS(u16 *x,u16 *y)
{
	u16 xtemp,ytemp;			 	 		  
	xtemp=ADS_Read_XY(CMD_RDX);
	ytemp=ADS_Read_XY(CMD_RDY);	 									   
	if(xtemp<100||ytemp<100)
		return 0;  //读数失败
	
	*x=xtemp;
	*y=ytemp;
	return 1;    //读数成功
}
//2次读取ADS7846,连续读取
//50,满足条件,则认为读数正确,否则读数错误.

	   

/**********************************
***********************************
读取ADC坐标值   作者：陈开放
注：2次读AD值,且两次的偏差不超过20
    该函数能大大提高准确度
***********************************
**********************************/
#define ERR_RANGE 20 //误差范围 
u8 Read_ADS2(TP_PIX *tp_pix) 
{
	u16 x1,y1;
 	u16 x2,y2;
 	u8 flag;    
    flag=Read_ADS(&x1,&y1);   
    if(flag==0)return(0);
    flag=Read_ADS(&x2,&y2);	
    if(flag==0)return(0);   
    if(((x2<=x1&&x1<x2+ERR_RANGE)||(x1<=x2&&x2<x1+ERR_RANGE))//前后两次采样在+-ERR_RANGE内
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
获取坐标      作者：陈开放
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
延时      作者：陈开放
***********************************
**********************************/
void Delay_Touch(u32 nCount)
{
	u32 count;
	for(;nCount>0;nCount--)
	  for(count=1;count>0;count--);
}	

