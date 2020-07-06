#include"ADC0804.H"

void ADC0804_Delay100us(void)   
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=43;a>0;a--);
}
/************************************
* 函数名称：ADC0804_Start()
* 函数功能：启动ADC0804转换
* 输入参数：无
* 返回参数：无
************************************/
void ADC0804_Start()
{
   ADC0804_CS_L;
   ADC0804_WR_L;
   ADC0804_Delay;
   ADC0804_WR_H;
   while(ADC0804_INT);
   ADC0804_CS_H;
} 
/************************************
* 函数名称：ADC0804_ReadData()
* 函数功能：读取ADC0804数据
* 输入参数：无
* 返回参数：电压原始数据值
************************************/
uchar ADC0804_ReadData()
{
  uchar temp_data;
  ADC0804_DATA=0xFF;
  ADC0804_CS_L;
  ADC0804_RD_L;
  ADC0804_Delay;
  temp_data=ADC0804_DATA;
  ADC0804_RD_H;
  ADC0804_CS_H;
  return(temp_data);
}
/************************************
* 函数名称：ADC0804_GetVoltage(uchar V)
* 函数功能：获取ADC0804的采集的电压
* 输入参数：参考电压
* 返回参数：电压值*10
************************************/
uint ADC0804_GetVoltage(uchar V)
{
  uint temp_V,dat;
  ADC0804_Start();
  dat=ADC0804_ReadData()*10;
  temp_V=dat/(0xFF/V);
  return(temp_V);	

}



