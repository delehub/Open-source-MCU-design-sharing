/********************************************************************
*程序名称：DS1302驱动程序源文件
*程序作者：许方超
*版本信息：V1.8
*最后更新：2013-7-1
*更新说明：V1.4 修改函数名称，方便阅读，更加规范
*		   V1.5 使用宏定义定义引脚，方便移植
*		   V1.6 加入外部数组DS1302_BUFFER[7]
*		   V1.7 添加时间设置函数
*		   V1.8 修改uchar为uint8
********************************************************************/
#include "DS1302.H"
bdata uint8 DS1302_DATA ;
uint8 DS1302_BUFFER[7];
sbit  DS1302_DATA_0=DS1302_DATA^0;
sbit  DS1302_DATA_7=DS1302_DATA^7;
/********************************************************************
* 函数名称:  DS1302_WriteByte（uint8 dat）
* 函数功能:  往DS1302写入1Byte数据
* 输入参数:  dat 写入的数据
* 输出参数:  无
* 使用说明:	 该函数隶属于DS1302内部驱动函数，一般无需外部调用
*********************************************************************/
void DS1302_WriteByte(uint8 dat)
{
	uint8 i;
	DS1302_RST_H;	             //至高复位端，逻辑控制有效
	DS1302_DATA = dat;	         //将八位数据放入累加器	
	for(i=8; i>0; i--)           //为什么不能for(i=0;i<8;i++)
	{	 
		DS1302_IO = DS1302_DATA_0;//发送最低位 
		DS1302_CLK_H;   		  //时钟上升沿完成操作 	   
		DS1302_CLK_L;	          //初始化时钟
		DS1302_DATA>>=1;           //数据向右移一位
	}
}
/********************************************************************
* 函数名称:  DS1302_ReadByte(void) 
* 函数功能:  读取DS1302一个字节函数
* 输入参数:  无
* 返回参数:  DS1302_DATA
* 使用说明:	 该函数隶属于DS1302内部驱动函数，一般无需外部调用
*********************************************************************/
uint8 DS1302_ReadByte(void) 
{
	uint8 i;
	DS1302_RST_H;
	for(i=8; i>0; i--)
	{
		DS1302_DATA>>=1;
		DS1302_DATA_7=DS1302_IO;
		DS1302_CLK_H;
		DS1302_CLK_L;
	}
	return(DS1302_DATA);
}
/********************************************************************
* 函数名称:   DS1302_WriteData(uint8 Addr, uint8  dat)
* 函数功能:   往DS1302写入数据
* 输入参数:   Addr: DS1302地址, dat: 要写的数据
* 返回参数:   无
* 使用说明:	 该函数隶属于DS1302内部驱动函数，一般无需外部调用
**********************************************************************/
void DS1302_WriteData(uint8 Addr, uint8 dat)
{
	DS1302_RST_L;
	DS1302_CLK_L ;
	DS1302_RST_H;
	DS1302_WriteByte(Addr);   // 写地址 
	DS1302_WriteByte(dat);     // 写1Byte数据
	DS1302_CLK_H;
	DS1302_RST_L;
}
/********************************************************************
* 函数名称:  DS1302_ReadData(uint8 Add)
* 函数功能:  读取DS1302某地址的数据
* 输入参数:  Addr: DS1302地址
* 返回参数:  dat :读取的数据
* 使用说明:	 该函数隶属于DS1302内部驱动函数，一般无需外部调用
*********************************************************************/
uint8 DS1302_ReadData(uint8 Addr)
{
	uint8 dat;
	DS1302_RST_L;
	DS1302_CLK_L ;
	DS1302_RST_H;
 	DS1302_WriteByte(Addr);    //写地址，命令
	dat = DS1302_ReadByte(); //读1Byte数据
	DS1302_CLK_H;
	DS1302_RST_L;
	return(dat);
}
/**************************************************************
* 函数名称: DS1302_dectobcd(uchar Dec)
* 函数功能: DEC码转换为BCD码
* 输入参数: dec码
* 输出参数: bcd码
* 使用说明:	该函数隶属于DS1302内部驱动函数，一般无需外部调用
**************************************************************/
uint8 DS1302_DECtoBCD(uint8 Dec)
{
	uint8 bcd;
	bcd = 0;
	while(Dec >= 10)
	{              
		Dec -= 10;                         
		bcd++;
	} 
	bcd <<= 4;
	bcd |= Dec;
	return (bcd);
}

/********************************************************************
* 函数名称: DS1302_BCDtoDEC(uint8 bcd)
* 函数功能: BCD码转换为DEC码
* 输入参数: bcd码
* 输出参数: dec码
* 使用说明:	 该函数隶属于DS1302内部驱动函数，一般无需外部调用
********************************************************************/
uint8 DS1302_BCDtoDEC(uint8 Bcd)
{
	uint8 temp_dat;
	temp_dat = Bcd & 0x0f;     //取BCD低4位
	Bcd = Bcd & 0x70;          //剔除BCD的最高位和低4位。
	temp_dat += Bcd >> 1;
	temp_dat += Bcd >> 3;      //用位移代替乘法运算
	return (temp_dat);
}
/********************************************************************
* 函数名称: DS1302_initset()
* 函数功能: 往DS1302中写入数据。最开始显示的数据就是在这里设置的。
* 输入参数: 无
* 输出参数: 无
* 使用说明：直接调用即可将DS1302初始化为2012-8-8 7:59:59 星期五
***********************************************************************/
void DS1302_InitSet(void)
{
	DS1302_WriteData(0x8e,0);	    //开写命令
	DS1302_WriteData(0x80,0x50);	//写入秒
	DS1302_WriteData(0x82,0x59);	//写入分
	DS1302_WriteData(0x84,0x07);	//写入小时
	DS1302_WriteData(0x86,0x08);	//写入日
	DS1302_WriteData(0x88,0x08);	//写入月
	DS1302_WriteData(0x8a,0x05);	//写入星期
	DS1302_WriteData(0x8c,0x0c);	//写入年	
}
/***********************************************************************
* 函数名称: DS1302_GetTime() 
* 函数功能: 读出DS1302中的数据，并将数据存入外部数组
* 输入参数: 无
* 输出参数: 无
* 使用说明:	直接调用即可，调用之后，时间信息将会存储在DS1302_BUFFER[]
***********************************************************************/
void DS1302_GetTime()
{
	DS1302_WriteData(0x8f, 0);			                           //开读命令
	DS1302_BUFFER[0] = DS1302_BCDtoDEC(DS1302_ReadData(0x81));	   //读出DS1302中的秒
	DS1302_BUFFER[1] = DS1302_BCDtoDEC(DS1302_ReadData(0x83));	   //读出DS1302中的分
	DS1302_BUFFER[2] = DS1302_BCDtoDEC(DS1302_ReadData(0x85));     //读出DS1302中的小时
	DS1302_BUFFER[3] = DS1302_BCDtoDEC(DS1302_ReadData(0x87));	   //读出DS1302中的日
	DS1302_BUFFER[4] = DS1302_BCDtoDEC(DS1302_ReadData(0x89));     //读出DS1302中的月
	DS1302_BUFFER[5] = DS1302_BCDtoDEC(DS1302_ReadData(0x8d));     //读出DS1302中的年		
} 

/*************************************************************************************************
* 函数名称: DS1302_SetTime(uint8 Year,uint8  Month ,uint8 Day,uint8 Hour,uint8 Minute,uint8 Second) 
* 函数功能: 设置时间，日期等信息
* 输入参数: Year=年；Month=月；Day=天；Hour=小时；Minute=分钟；Second=秒；Week=星期
* 输出参数: 无
**************************************************************************************************/
void DS1302_SetTime(uint8 Year,uint8  Month ,uint8 Day,uint8 Hour,uint8 Minute,uint8 Second,uint8 Week)
{
	DS1302_WriteData(0x8e,0);	                    				//开写命令
	DS1302_WriteData(0x80,DS1302_DECtoBCD(Second));					//写入秒
	DS1302_WriteData(0x82,DS1302_DECtoBCD(Minute));					//写入分
	DS1302_WriteData(0x84,DS1302_DECtoBCD(Hour));					//写入小时
	DS1302_WriteData(0x86,DS1302_DECtoBCD(Day));					//写入日
	DS1302_WriteData(0x88,DS1302_DECtoBCD(Month));					//写入月
	DS1302_WriteData(0x8a,DS1302_DECtoBCD(Week));					//写入星期
	DS1302_WriteData(0x8c,DS1302_DECtoBCD(Year));					//写入年	


}
