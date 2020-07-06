#include"MAIN.H"
#include"STC12C5A60S2_ADC.H"


#define ADC_POWER                   0x80    // ADC 电源控制位；置1为打开A/D转换电源
#define ADC_FLAG                    0x10    // ADC 转换结束完成标志位，转换完成后硬件置1，必须软件清0。
#define ADC_START                   0x08    // ADC 转换启动控制位，设置“1”时，开始转换。转换结束后为“0”。
#define ADC_SPEED                   0x00    // 设为540个时钟周期ADC一次
                                    
#define ADC_SPEEDLL                 0x00    // 540 时钟周期
#define ADC_SPEEDL                  0x20    // 360 时钟周期
#define ADC_SPEEDH                  0x40    // 180 时钟周期
#define ADC_SPEEDHH                 0x60    //  0  时钟周期



// Channel 指的通道组合
// 0x80 0x40 0x20 0x10 0x08 0x04 0x20 0x10
// P1.7 P1.6 P1.5 P1.4 P1.3 P1.2 P1.1 P1.0
// 例如 使用P1.0 与P1.7 则初始化应该为ADC_init(0x10 | 0x80)
void ADC_init(unsigned char Channel)
{
	// 转换结果存储格式：数据的高2位放ADC_RES
	//                   数据的低8位放ADC_RESL
	AUXR1 |= 0x04;	 
    
    P1ASF |= Channel;
}

// Channel  取值范围 0~7 
unsigned int ADC_Converter(unsigned char Channel)
{
    unsigned int DATA;
    
    // 数据储存寄存器清空
	ADC_RES=0;				
    ADC_RESL=0;	

//    // ADC_CONTR配置
//	ADC_CONTR = ( 0
//	            | ADC_POWER		// 打开ADC电源 
//	            | ADC_SPEEDHH	// 选择ADC速率
//	            | Channel	    // 具体ADC通道
//	            | ADC_START		// 启动ADC运行
//				);
                
    // ADC_CONTR配置
	ADC_CONTR = ( 0
	            | 0x80		// 打开ADC电源 
	            | 0x60		// 选择ADC速率
	            | Channel	    // 具体ADC通道
	            | 0x08		// 启动ADC运行
				);
    
	// 延时5个时钟周期左右
	_nop_(); 					
	_nop_();
	_nop_();
	_nop_();
	_nop_();     
	
    // 等待ADC结束 
//	while(!(ADC_CONTR&ADC_FLAG)); 
	while(!(ADC_CONTR&0x10));                        
       
	// 转换结果计算高位结果存储器的低2位 + 低位结果存储器
	DATA=(ADC_RES&0x03)*256 + ADC_RESL; 
//	DATA=(ADC_RES&0x03)<<8 + ADC_RESL;   

    // 清除ADC标志 软件清零操作
//    ADC_CONTR &=~ADC_FLAG;      
    ADC_CONTR &=~0x10;                      
       
    //返回ADC数值
	return DATA; 

}


