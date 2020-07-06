/********************************************
*山东建筑大学 锐思实验室				    *
*函数名称：DS18B20程序		     			*
*CPU型号 ：STC89C52					        *
*晶振参数：12MHZ			    		    *
*程序作者：2009级机械2班 许方超				*
*联系方式：QQ：610949704				    *
*							                *
********************************************/
#include "DS18B20.h"
uchar TMPL,TMPH;
sbit DQ=P2^3;
#define DQ_L DQ=0
#define DQ_H DQ=1
/*-----------定值延时函数声明------------------*/
void DS18B20_Delay6us(void);
void DS18B20_Delay10us(void);
void DS18B20_Delay50us(void);
void DS18B20_Delay30us(void);
void DS18B20_Delay700us(void);
void DS18B20_Delay100us(void);
void DS18B20_Delayms(unsigned int z);
/*****************************
DS18B20复位函数
1、数据线至高（短暂延时）
2、数据线拉低（延时480-960UM）
3、数据线拉高
4、延时等待响应
5、将数据线再次拉高
*****************************/
uchar DS18B20_Reset()
{
     uchar x;
	 DQ_H ;                  //数据线拉高
	 DQ_L;		             //数据线拉低
     DS18B20_Delay700us();   //延时480us-960us
	 DQ_H;					 //数据线拉高
	 DS18B20_Delay30us();    //延时15us-60us
	 x=DQ;					 //读取此时数据线的值
 	 while(!DQ);             //直到DQ为高
     return x;	             //返回复位结果
}
/***************************
18B20读一位数据函数
1、将数据线拉高（延时2微妙）
2、将数据线拉低（延时6微妙）
3、将数据线拉高（延时4微妙）
4、读数据线状态，得一个状态位
5、延时50微秒
***************************/
uchar DS18B20_ReadBit()
{	bit x ;
	uchar i; 
	DQ_H;		 		//数据线拉高
	i++;         		//延时2微秒
    DQ_L;        		//数据线拉低
	DS18B20_Delay6us(); //延时6微秒 
	DQ_H; 		 		//数据线拉高
	i++;i++;	 		//延时4微秒
	x=DQ;		 		//读数据线状态
	DS18B20_Delay50us();//延时50微秒
	return (x); 		//返回数值

}
/***********************************
DS18B20写一位函数
1、将数据线拉高
2、延时大于1微秒（两次写片段的间隙）
3、将数据线拉低（开始写时序	）
4、延时大于1微秒（写时序的低电平延时大于1微秒）
5、写入数据 15微秒后开始采集
6、延时使写周期在60-120微秒
***********************************/
void DS18B20_WriteBit(uchar Bit)
{	  uchar i;
	  DQ_H;	         		//将数据线拉高
	  i++;	         		//延时大于1微秒
	  DQ_L;          		//将数据线拉低
	  i++;	         		//延时大于1微秒
	  DQ=Bit;         		//写入数据
	  DS18B20_Delay100us();	//延时使写周期在60-120微秒之间
	  DQ_H;
}
/************************************
DS18B20读一个字节函数
************************************/
uchar DS18B20_ReadByte()
{
	uchar i,j,dat;
    dat=0;
    j=1;
	for(i=0;i<8;i++)
	{
		if(DS18B20_ReadBit())
		{
			dat=dat+(j<<i);
		}
	}
	return (dat);
}
/********************************
DS18B20写一个字节函数
********************************/
void DS18B20_WriteByte(uchar dat)
{
	uint temp;
	uchar j;
	for(j=0;j<8;j++)
	{	 	
	    temp=dat>>j;
		temp=temp&0x01;
		DS18B20_WriteBit(temp) ;
	}	
	
}
/****************************
DS18B20读供电方式
****************************/
bit DS18B20_PowerMode()
{	
   	bit x;
	while(DS18B20_Reset());  //复位，通信前必须复位
	DS18B20_WriteByte(0xcc);
	DS18B20_WriteByte(0xb4); //读供电方式命令
    x=DQ;
	DS18B20_Delay10us();
	return x; 
}
/******************************
DS18B20 精度设置函数
*****************************/
void DS18B20_SetResolution(unsigned char res)
{ 
    switch (res)
	{
	     case  9:res=0;
		 break; 
		 case 10:res=1;
		 break; 
		 case 11:res=2;
		 break;
		 case 12:res=3;
		 break;  
	}
 DS18B20_Reset();              //复位，通信前必须复位
 DS18B20_WriteByte(0x4e);             //写暂存器指令
 DS18B20_WriteByte(0xff);             //此值被写入TH
 DS18B20_WriteByte(0xff);             //此值被写入TL
 DS18B20_WriteByte(0x1f|(res<<5));    //设置精度  0 res[1-0] 11111
}
/*****************************
DS18B20温度读取函数
*****************************/
long DS18B20_GetTemperature()
{ 	 long wendu;
     DS18B20_Reset();
	 DS18B20_WriteByte(0xcc);//跳过ROM
	 DS18B20_WriteByte(0x44);//温度转换
	 DS18B20_Delayms(560);	 //需要100-750毫秒转换时间
	 DS18B20_Reset();
	 DS18B20_WriteByte(0xcc);//跳过ROM
	 DS18B20_WriteByte(0xbe);//读暂存器
	 TMPL=DS18B20_ReadByte();
	 TMPH=DS18B20_ReadByte();
	 wendu=TMPH<<8|TMPL;
	 wendu=wendu>>4;		//移位代替除法
	 return wendu;
}
/*****************************************
匹配ROM函数
*****************************************/
uchar DS18B20_MatchRom(uchar *rom)
{
	uchar i;
	DS18B20_Reset();
	DS18B20_WriteByte(0x55);
	for(i=0;i<8;i++)
	{
	    
		DS18B20_WriteByte(*rom);
		rom++;
	}
	return 1;
}
 void DS18B20_GetRom(unsigned char *ROM)
 {
  	unsigned char i=0;
    DS18B20_Reset();
	DS18B20_WriteByte(0x33);

	ROM[0]=DS18B20_ReadByte();
	ROM[1]=DS18B20_ReadByte();
	ROM[2]=DS18B20_ReadByte();
	ROM[3]=DS18B20_ReadByte();
	ROM[4]=DS18B20_ReadByte();
	ROM[5]=DS18B20_ReadByte();
	ROM[6]=DS18B20_ReadByte();
	ROM[7]=DS18B20_ReadByte();
}

long DS18B20_ReadTemperature(unsigned char *Rom)
{	long wendu;
 	DS18B20_MatchRom(Rom);
 	DS18B20_WriteByte(0xbe);//读暂存器命令
	TMPL=DS18B20_ReadByte();
	TMPH=DS18B20_ReadByte();
	wendu=TMPH<<8|TMPL;
	wendu=wendu>>4;		//移位代替除法
	return wendu;
}
/**********DS18B20专用定值延时函数****************/
void DS18B20_Delay6us(void)   //误差 -0.574652777778us
{
    unsigned char a;
    for(a=1;a>0;a--);
}
void DS18B20_Delay10us(void)   //误差 -0.234375us
{
    unsigned char a;
    for(a=3;a>0;a--);
}
void DS18B20_Delay30us(void)   //误差 -0.703125us
{
    unsigned char a;
    for(a=12;a>0;a--);
}
void DS18B20_Delay50us(void)   //误差 -0.086805555556us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=20;a>0;a--);
}
void DS18B20_Delay100us(void)   //误差 -0.173611111111us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=43;a>0;a--);
}
void DS18B20_Delay700us(void)   //误差 -0.130208333333us
{
    unsigned char a,b;
    for(b=6;b>0;b--)
        for(a=52;a>0;a--);
}
void DS18B20_Delayms(unsigned int z)
	{
	    unsigned int i,j;
		for(i=z;i>0;i--)
		  for(j=114;j>0;j--);
    }