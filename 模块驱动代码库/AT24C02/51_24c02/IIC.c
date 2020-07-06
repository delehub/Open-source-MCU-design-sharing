#include "IIC.h"
 
/******************************
 I^2C总线初始化函数
 将总线都拉高以释放总线
******************************/
void IIC_init()
{
	SDA=1;
	_nop_();
	_nop_();
    _nop_();
	_nop_();
	_nop_();
	SCL=1;
	_nop_();
    _nop_();
	_nop_();
	_nop_();
	_nop_();

}
/******************************
I^2C总线启动信号
SCL在高电平期间，
SDA一个下降沿启动信号
******************************/
void IIC_start()
{
	SDA=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SCL=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SDA=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
/****************************
I^2C总线应答信号
SCL在高电平期间，SDA被硬件设备
拉为低电平表示应答
***************************/
void IIC_respons()
{
	uchar i;
	SCL=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	while((SDA==1)&&(i<255))
	  {
	   i++;
	  }
    SCL=0;
    _nop_();
    _nop_();
	_nop_();
	_nop_();
	_nop_();
}
/*********************************************************************
 - 功能描述：主设备发出应答
 - 隶属模块：IIC模块
 - 函数属性：外部，供用户使用
 - 参数说明：无      
 - 返回说明：无
 - 注：主设备(比如单片机)，从从设备(比如PCF8563、AT24C64)读取字节后，如果
       要继续读取，就要给从设备一个ACK(即所谓的“应答”，数据位SDA为0)
 *********************************************************************/

void IIC_ack() 
{
 SDA=0;
 _nop_();
 _nop_();
 _nop_();
 _nop_();
 _nop_();   
 SCL=1; 
  _nop_();
 _nop_();
 _nop_();
 _nop_();
 _nop_();  
 SCL=0; 
  _nop_();
 _nop_();
 _nop_();
 _nop_();
 _nop_();  
}

/*********************************************************************
 - 功能描述：主设备发出无应答
 - 隶属模块：IIC模块
 - 函数属性：外部，供用户使用
 - 参数说明：无      
 - 返回说明：无
 - 注：主设备(比如单片机)，从从设备(比如PCF8563、AT24C64)读取字节后，如果不再
       进行读取，就要给从设备一个NACK(即所谓的“无应答”，数据位SDA为1)
 *********************************************************************/

void IIC_nack() 
{
 SDA=1; 
  _nop_();
 _nop_();
 _nop_();
 _nop_();
 _nop_();  
 SCL=1;
  _nop_();
 _nop_();
 _nop_();
 _nop_();
 _nop_();   
 SCL=0;
  _nop_();
 _nop_();
 _nop_();
 _nop_();
 _nop_();  
}
/**************************
I^2C总线停止信号
SCL在高电平期间
SDA一个上升沿信号
*************************/
void IIC_stop()
{
	SDA=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SCL=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SDA=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	_nop_();
}
/***********************
I^2C总线写一个字节函数
将8位左移，将最高位移入
寄存器CY，然后将CY赋给SDA
进而在SCL的控制下发送出去
***********************/
void IIC_writebyte(uchar date)
{
	uchar i,j;
	j=date;
	for(i=0;i<8;i++)
	{
		j=j<<1;
		SCL=0;
		_nop_();
		_nop_();
		_nop_();
 	    _nop_();
		SDA=CY;
		_nop_();
		_nop_();
		_nop_();
	    _nop_();
		SCL=1;
		_nop_();
		_nop_();
		_nop_();
	    _nop_();
	} 
	SCL=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SDA=1;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
} 
/*************************
I^2C总线读一个字节函数
通过或运算，将数据一位一位
的接受
************************/
uchar IIC_readbyte()
{
	uchar i,j,k;
	SCL=0;
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	SDA=1;
	for(i=0;i<8;i++)
	{
	    _nop_();
		_nop_();
		_nop_();
	    _nop_();
		SCL=1;
		_nop_();
		_nop_();
		_nop_();
		_nop_();
		if(SDA == 1)
		{
			j = 1;
		}
		else j = 0;

		k=(k<<1)|j;
		SCL=0;
		_nop_();
		_nop_();
		_nop_();
	    _nop_();
	}
	_nop_();
	_nop_();
	_nop_();
	_nop_();
	return k;
}
