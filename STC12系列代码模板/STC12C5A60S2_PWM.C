#include"MAIN.H"
#include"STC12C5A60S2_PWM.H"

void PWM0_init(unsigned char Duty)
{
    AUXR1 &=0xBF;   // 设置特殊寄存器，PWM由P1不切换到P4口
    CCON = 0;       // PCA控制寄存器（PCA=可编程计数器阵列）    
                    // bit7：CF，PCA溢出标志位清除
                    // bit6：CR，PCA运行控制位清除，关闭PCA
                    // bit1：CFF1，PCA模块1中断清除
                    // bit0：CFF0，PCA模块0中断清除
    CL = 0x00;      // PCA计数器低8位清零 
    CH = 0x00;      // PCA计数器高8位清零
    CMOD=0x00;      // PCA模式寄存器
                    // bit7：CIDL，PCA空闲控制，为0表示空闲模式下，PCA继续工作。
                    // bit3/bit2/bit1：PCA计数脉冲选择，000表示系统时钟Fosc/12
                    // bit0：ECF，PCA计数溢出使能，为0表示禁止使能CCON中的CF位。
    CCAPM0   = 0X42;                                // 8位PWM输出，无中断，允许比较器功能，允许CEX0脚用作脉宽调节输出
    CCAP0L   = 0xFF;                                // PCA模块0，捕获/比较寄存器低位字节，PWM模式下，控制占空比大小
    CCAP0H   = 0xFF - Duty;                        // PCA模块0，捕获/比较寄存器高位字节，PWM模式下，控制占空比大小
    PCA_PWM0 = 0x00;                                // PCA模块0，占空比第9位    

    CR=1;       //PCA启动运行
}

// 占空比 百分比  
// Duty 0~255
// Duty = 0   -> 0%
// Duty = 255 -> 100% 
// 实际占空比 = Duty/255
void PWM0_SetDuty(unsigned char Duty)
{
    CCAP0H=0xFF-Duty;
}












void PWM1_init(unsigned char Duty)
{
    AUXR1 &=0xBF;   // 设置特殊寄存器，PWM由P1不切换到P4口
    CCON = 0;       // PCA控制寄存器（PCA=可编程计数器阵列）    
                    // bit7：CF，PCA溢出标志位清除
                    // bit6：CR，PCA运行控制位清除，关闭PCA
                    // bit1：CFF1，PCA模块1中断清除
                    // bit0：CFF0，PCA模块0中断清除
    CL = 0x00;      // PCA计数器低8位清零 
    CH = 0x00;      // PCA计数器高8位清零
    CMOD=0x00;      // PCA模式寄存器
                    // bit7：CIDL，PCA空闲控制，为0表示空闲模式下，PCA继续工作。
                    // bit3/bit2/bit1：PCA计数脉冲选择，000表示系统时钟Fosc/12
                    // bit0：ECF，PCA计数溢出使能，为0表示禁止使能CCON中的CF位。
   
    CCAPM1   = 0X42;                                // 8位PWM输出，无中断，允许比较器功能，允许CEX0脚用作脉宽调节输出
    CCAP1L   = 0xFF;                                // PCA模块1，捕获/比较寄存器低位字节，PWM模式下，控制占空比大小
    CCAP1H   = 0xFF - Duty;                        // PCA模块1，捕获/比较寄存器高位字节，PWM模式下，控制占空比大小
    PCA_PWM1 = 0x00;                                // PCA模块1，占空比第9位
    
    CR=1;       //PCA启动运行
}





void PWM1_SetDuty(unsigned char Duty)
{
    CCAP1H=0xFF-Duty;
}
