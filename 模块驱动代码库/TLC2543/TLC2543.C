#include"TLC2543.H"
unsigned char TLC2543_DATA[7];
void TLC2543_Delay10us(void)   
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=10;a>0;a--);
}
/************************************
* 函数名称：TLC2543_ReadData()
* 函数功能：读取ADC0804数据
* 输入参数：无
* 返回参数：电压原始数据值
************************************/
uint16 TLC2543_ReadData(uint8 AX)
{
  
  uint32 Vol=0;
  uint8 i=0;
  TLC2543_CS_L;
  TLC2543_Delay;
  AX=AX<<4;
  for(i=0;i<8;i++)
  { 
  
    TLC2543_CLK_L;
    TLC2543_DIN=AX&0x80;
    AX=AX<<1;
    TLC2543_CLK_H;
    TLC2543_Delay;
    Vol=Vol<<1;
  	Vol=Vol|TLC2543_DOUT;	
  }
  for(i=0;i<4;i++)
  {
    TLC2543_CLK_L;
    TLC2543_Delay;
    TLC2543_CLK_H;
    TLC2543_Delay;   
    Vol=Vol<<1;
  	Vol=Vol|TLC2543_DOUT; 
  }
  TLC2543_CLK_L;
  TLC2543_CS_H; 
  return(Vol);
}
/************************************
* 函数名称：TLC2543_GetVoltage(uchar V)
* 函数功能：获取ADC0804的采集的电压
* 输入参数：参考电压
* 返回参数：电压值*10
************************************/
uint32 TLC2543_GetVoltage(uint8 AX,uint8 Vref)
{
  uint8 i=0;
  uint16 dat=0;
  uint32 temp_V=0,temp_Data;
  dat=TLC2543_ReadData(AX);
  dat=TLC2543_ReadData(AX);
  dat=dat&0x0fff;

  temp_V=((dat*100000)/4096)*Vref;
  temp_Data=temp_V;
  TLC2543_DATA[0]=(unsigned char)(temp_V/100000);
  temp_V=temp_V%100000;
  TLC2543_DATA[1]=(unsigned char)(temp_V/10000);
  temp_V=temp_V%10000;
  TLC2543_DATA[2]=(unsigned char)(temp_V/1000);
  temp_V=temp_V%1000;
  TLC2543_DATA[3]=(unsigned char)(temp_V/100);
  temp_V=temp_V%100;
  TLC2543_DATA[4]=(unsigned char)(temp_V/10);
  temp_V=temp_V%10;
  TLC2543_DATA[5]=(unsigned char)(temp_V);
  return(temp_Data);	

}




