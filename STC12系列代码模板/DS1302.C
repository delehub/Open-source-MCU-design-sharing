																				  
/***************************************************************************************/
#include"MAIN.H"
#include"DS1302.H"



sbit DS1302_SCLK =P1^0;  //时钟
sbit DS1302_IO   =P1^1;  //数据输入输出
sbit DS1302_RST  =P1^2;  //复位/片选线

S_TIME TIME={24,14,10,10,5,4,18};//初始化时间参数

/******************************************************************** 
//函数名称: DS1302_WByte
//函数功能: 往DS1302 写入 1 Byte 数据
//输入值:   ndata: 寄存器的数据或地址
//返回值:   无
***********************************************************************/
  void DS1302_WByte(unsigned char ndata) 
{  
  unsigned char i;
  for(i=8; i>0; i--)                   //循环8次写入8位数据
  {
    DS1302_IO = (bit)(ndata&0x01);     //取最低位数据，从0位至7位依次传送
    DS1302_SCLK = 1;                   //给一个脉冲，将数据写入1302                 
    _nop_();
    DS1302_SCLK = 0;                   
    ndata>>=1;                         //即ndata = ndata >> 1; 
  } 
}
/******************************************************************** 
//函数名称: DS1302_RByte 
//函数功能: 从DS1302读取 1 Byte数据
//输入值:   无
//返回值:   ndata:读取的数据
***********************************************************************/
  unsigned char DS1302_RByte(void) 
{ 
   unsigned char i;
   unsigned char ndata=0;
   for(i=8;i>0;i--)                 //循环8次读出8位数据 
	{
	 DS1302_IO=1;                   //初始化数据IO
	 ndata>>=1; 			        //即ndata = ndata >> 1; 
	 if(DS1302_IO) ndata|=0x80;     //从数据口读取1位数据
     DS1302_SCLK = 1;               //给一个脉冲
     _nop_();
     DS1302_SCLK = 0;                     

	 }
     return (ndata);                //返回结果
}
/******************************************************************** 
//函数名称: DS1302_Wdata 
//函数功能: 往DS1302某地址写入某数据
//输入值:   nAddr: DS1302地址, ndata: 要写的数据
//返回值:   无
***********************************************************************/
void DS1302_Wdata(unsigned char nAddr, unsigned char ndata)
{
  DS1302_RST=0;              
  DS1302_SCLK=0;
  DS1302_RST=1;
  DS1302_WByte(nAddr);       // 写1Byte地址
  DS1302_WByte(ndata);       // 写1Byte数据 
  DS1302_SCLK=1;
  DS1302_RST=0;
} 
/******************************************************************** 
//函数名称: DS1302_Rdata 
//函数功能: 从DS1302某地址读取数据
//输入值:   nAddr: DS1302地址
//返回值:   ndata: 读取的数据
***********************************************************************/
unsigned char DS1302_Rdata(unsigned char nAddr)
{
    unsigned char ndata;
 	DS1302_RST=0;
	DS1302_SCLK=0;
	DS1302_RST=1;
    DS1302_WByte(nAddr);       /* 地址，命令 */
    ndata = DS1302_RByte();    /* 读1Byte数据 */
    DS1302_SCLK=1;
	DS1302_RST=0;
    return(ndata);
}
/******************************************************************** 
//函数名称: InitDS1302
//函数功能: DS1302初始时间设定
//输入值:   无
//返回值:   无
***********************************************************************/
void InitDS1302(void)
{
DS1302_Wdata(0x8e,0x00); //控制命令,WP=0,写操作
DS1302_Wdata(0x90,0xa5);  
/*
地址0x90为充电寄存器，可以对充电电流进行限制，写入
内容高4位固定为1010（其他组合均不能充电），低4
位的首2位是选择内部降压二极管的个数的，01代表在
充电回路串入1个二极管，10代表串入2个；最后2位可
设定串入的电阻的数值：01为2k欧，10为4k欧，11为8k欧。
*/
DS1302_Wdata(0x80,TIME.SEC);  //秒
DS1302_Wdata(0x82,TIME.MIN);  //分
DS1302_Wdata(0x84,TIME.HR);   //时
DS1302_Wdata(0x86,TIME.DATE); //日
DS1302_Wdata(0x88,TIME.MONTH);//月
DS1302_Wdata(0x8a,TIME.DAY);  //星期
DS1302_Wdata(0x8c,TIME.YEAR); //年

DS1302_Wdata(0x8e,0x80); //控制命令,WP=1,写保护
}
/******************************************************************** 
//函数名称: GetDS1302
//函数功能: DS1302当前时间读取
//输入值:   无
//返回值:   无
***********************************************************************/
/******************************************************************** 
//函数名称: GetDS1302
//函数功能: DS1302当前时间读取
//输入值:   无
//返回值:   无
***********************************************************************/
void GetDS1302_TIME(void)
{
    unsigned char Temp;
    
    Temp = DS1302_Rdata(0x81);    //从DS1302读取秒数据
    TIME.SEC = (Temp>>4)*10 + (Temp&0x0F);      

    Temp = DS1302_Rdata(0x83);    //从DS1302读取分数据
    TIME.MIN = (Temp>>4)*10 + (Temp&0x0F);

    Temp = DS1302_Rdata(0x85);    //从DS1302读取时数据
    TIME.HR = (Temp>>4)*10 + (Temp&0x0F);

}
void GetDS1302_DATE(void)
{
     unsigned char Temp;
	Temp = DS1302_Rdata(0x87);    //从DS1302读取天数据
    TIME.DATE = (Temp>>4)*10 + (Temp&0x0F);      


}

void SetDS1302_TIME(void)
{
    unsigned char Temp;
    
    // 写保护解除命令
    DS1302_Wdata(0x8E,0x00);
    
    Temp = (TIME.SEC/10%10)<<4  + (TIME.SEC/1 %10);
    DS1302_Wdata(0x81,Temp);    //从DS1302写秒数据
    
    Temp = (TIME.MIN/10%10)<<4  + (TIME.MIN/1 %10);
    DS1302_Wdata(0x83,Temp);    //从DS1302写分数据
    
    Temp = (TIME.HR/10%10)<<4  + (TIME.HR/1 %10);
    DS1302_Wdata(0x85,Temp);    //从DS1302写时数据

    // 写保护保留命令
    DS1302_Wdata(0x8E,0x80);
}
void SetDS1302_DATE(void)
{
    unsigned char Temp;
    
    // 写保护解除命令
    DS1302_Wdata(0x8E,0x00);
    
    Temp = (TIME.DATE/10%10)<<4  + (TIME.DATE/1 %10);
    DS1302_Wdata(0x87,Temp);    //从DS1302写秒数据
   

    // 写保护保留命令
    DS1302_Wdata(0x8E,0x80);
}



