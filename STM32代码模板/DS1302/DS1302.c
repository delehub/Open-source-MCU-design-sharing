

#include "DS1302.h"
#include "delay.h"

extern u8 Nian,Yue,Ri,XingQi,Shi,Fen,Miao;


void DS1302_GPIO_Init(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PORTB口时钟 
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;				//PORTB.8-10 推挽输出
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
}  

void DS1302_DATA_OUT(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void DS1302_DATA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void DS1302_init(u8 year,u8 mon,u8 day,u8 shi,u8 fen,u8 miao)           //DS1302 的 初 始 化，将所有参数全清零
{
	DS1302_write(0x8e,0x00); 		//关写保护
	DS1302_write(0x80,0x80); 		//关时间
	DS1302_write(0x80,miao);
	DS1302_write(0x82,fen);
	DS1302_write(0x84,shi);
	DS1302_write(0x86,day);
	DS1302_write(0x88,mon);
	DS1302_write(0x8a,0x00);
  	DS1302_write(0x8c,year);
	DS1302_write(0x8e,0x80);  		//开写保护
}

/*******************************************************************************/


/******************************* DS1302 读 一 个 字 节 ******************************/
u8  DS1302_readByte(void)
{
   	u8 i,temp=0;	
   	DS1302_DATA_IN();    	
	SCLK_OUT(0);	   	
   	for(i=8;i>0;i--)		
   	{		
   	  	temp=temp>>1;	
   	  	if(DS1302_IO_IN)
   	  		temp|=0x80;
   	  	else
   	  		;   	  	
   	  	SCLK_OUT(1);	
		SCLK_OUT(0);							
   	} 
   	return(temp);
}
/*******************************************************************************/

/******************************* DS1302 写 一 个 字 节 ******************************/
void  DS1302_writeByte(u8 tdata)
{
   	u8 i,temp;
   	temp=tdata;
	DS1302_DATA_OUT();	
	SCLK_OUT(0);	
   	for(i=8;i>0;i--)
   	{
   	  	if(temp&0x01)
   	  		IO_OUT(1);
   	  	else
   	  		IO_OUT(0);
   	  	SCLK_OUT(1);
		SCLK_OUT(0);
   	  	temp=temp>>1;
   	}
}
/********************************************************************************/

/******************************* DS1302 写 操 作  **********************************/
void DS1302_write(u8 tadd,u8 tdata)
{
   	RST_OUT(0);
   	SCLK_OUT(0);
   	RST_OUT(1);
   	DS1302_writeByte(tadd);
   	DS1302_writeByte(tdata); 
   	RST_OUT(0);
   	SCLK_OUT(1);
}
/********************************************************************************/

/******************************* DS1302 读 操 作  **********************************/
u8 DS1302_read(u8 tadd)
{  
   	u8 tdata;   
   	RST_OUT(0);
   	SCLK_OUT(0);
   	RST_OUT(1);
   	DS1302_writeByte(tadd);
   	tdata=DS1302_readByte(); 
   	RST_OUT(0);
   	SCLK_OUT(1);
   	return(tdata);
}
/********************************************************************************/

/****************************** DS1302 设 置 时 间 **********************************/
//功能：对已经调节好的时间参数写到DS1302中
/*********************************************************************************/

void DS1302_set_time(void)	 //设置时间
{
	u8 temp;
	DS1302_write(0x8e,0x00); //关写保护
	delay_ms(2);
	DS1302_write(0x80,0x80); //关时间
	delay_ms(2);
	DS1302_write(0x8c,(Nian/10<<4)|(Nian%10));
	DS1302_write(0x8a,(XingQi/10<<4)|(XingQi%10));
	DS1302_write(0x88,(Yue/10<<4)|(Yue%10));
	DS1302_write(0x86,(Ri/10<<4)|(Ri%10));
	DS1302_write(0x84,(Shi/10<<4)|(Shi%10));
	DS1302_write(0x82,(Fen/10<<4)|(Fen%10));
  	DS1302_write(0x80,(Miao/10<<4)|(Miao%10));
	delay_ms(2);
	temp=DS1302_read(0x81);
	temp&=0x7F;
	DS1302_write(0x80,temp);  		//开时间
	delay_ms(2);
	DS1302_write(0x8e,0x80);  //开写保护
	delay_ms(2);
}

/*******************************************************************************/

/****************************** DS1302 读 取 时 间 *********************************/
//功能：读取时钟芯片DS1302的时间参数
/*******************************************************************************/

void DS1302_read_time(void)    //读取时间
{
	Miao  =DS1302_read(0x81);
	Fen   =DS1302_read(0x83);
	Shi   =DS1302_read(0x85);
	Ri    =DS1302_read(0x87);
	Yue   =DS1302_read(0x89);
	XingQi=DS1302_read(0x8b);
	Nian  =DS1302_read(0x8d);
}	


/******************* (C) COPYRIGHT 2013 CEPARK多功能开发学习板*****END OF FILE****/
