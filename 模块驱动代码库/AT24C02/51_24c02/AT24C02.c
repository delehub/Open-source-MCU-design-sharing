#include "AT24C02.h"
/******************************************************************
 - 功能描述：向AT24C02的地址为addr的单元上写入一个字节dat
 - 参数说明：addr:AT24C02的单元地址
             dat:要写入的字节     
 - 注：AT24C02的地址是字节级地址，即最小存储单元是字节，地址范围 
       是0~8191
 ******************************************************************/

void IIC_AT24C02_writebyte(uint addr,uchar dat) 
{
 IIC_start();             //启动IIC传输
 IIC_writebyte(0xa0);      //1010 A2 A1 A0 R/W [A2:A0]是AT24C02的芯片地址，0~7，即同一条IIC总线上可以挂接8个芯片；R/W是读/写选择位，0为写操作，1为读操作
 IIC_respons();
 IIC_writebyte(addr);      //写入地址字节
 IIC_respons();
 IIC_writebyte(dat);       //写入一个字节的数据
 IIC_respons();
 IIC_stop();               //IIC传输结束，AT24C64开始执行，即将这一个字节写入EEPROM中
 Delay_ms(4);              //等待AT24C64操作完成，最大5ms
}

/******************************************************************
 - 功能描述：写页操作
 - 参数说明：addr:页开始地址
             pbuf:指向数据缓冲区的指针    
 - 返回说明：无
 - 注：向AT24C02芯片addr地址后面连续写入32个字节，即写页操作，
       这些数据存放在pbuf中
 ******************************************************************/

void IIC_AT24C02_writepage(uint addr,uchar length,unsigned char *pbuf) 
{
 unsigned char i;
 IIC_start();             //启动IIC传输
 IIC_writebyte(0xa0);     //1010 A2 A1 A0 R/W [A2:A0]是AT24C64的芯片地址，0~7，即同一条IIC总线上可以挂接8个芯片；R/W是读/写选择位，0为写操作，1为读操作
 IIC_respons();
 IIC_writebyte(addr);     //写入地址字节
 IIC_respons();
 for(i=0;i<length;i++)
 {
  IIC_writebyte(pbuf[i]); //将pbuf中的32个字节写入AT24C64的数据缓冲区
  IIC_respons();
 }
 IIC_stop();               //IIC传输结束，AT24C64开始执行，即将这32个字节写入EEPROM中
 Delay_ms(4);              //等待AT24C64操作完成，最大5ms
}

/******************************************************************
 - 功能描述：从当前地址连续读取length个字节，放入pbuf指向的数据缓冲区
 - 隶属模块：AT24C02模块
 - 函数属性：外部，供用户使用
 - 参数说明：length:要读取的数据长度
             pbuf:指向数据缓冲区的指针    
 - 返回说明：无
 - 注：从当前的地址上读取数据，所以此函数中没有写入地址的操作
 ******************************************************************/

void IIC_AT24C02_readpage(uint addr,uint length,unsigned char *pbuf) 
{
 unsigned char i;
 IIC_start();                   //启动传输，这里再次启动传输，因为下面要写入“读操作”的指令码，即0xa1
 IIC_writebyte(0xa1);           //写入0xa1，从AT24C64中读取数据
 IIC_respons();
 for(i=0;i<length-1;i++)
 {
  pbuf[i]=IIC_readbyte();       //读取length-1个字节
  IIC_ack();			        //前length-1个字节，每读完一个字节要向AT24C64提供ACK，即告诉其继续提供下面的数据，读取操作还未完毕
 }
 pbuf[i]=IIC_readbyte();        //读取最后一个字节，即第length个字节
 IIC_nack();                    //读取最后一个字节后，要向AT24C64发出NACK，告诉其读取操作结束，不再向下读了
 IIC_stop();                    //传输结束  
}
/***************************
从24C02中读出数据
（地址）从该地址中读出存储的
数据
**************************/
uchar  IIC_AT24C02_readbyte(uchar address)
{
	uchar cc;
	IIC_start();
	IIC_writebyte(0xa0);
	IIC_respons();
	IIC_writebyte(address);
	IIC_respons();
	IIC_start();
	IIC_writebyte(0xa1);
	IIC_respons();
	cc=IIC_readbyte();
	IIC_stop();
	return cc;
} 
