#ifndef __DELAY_H__
#define __DELAY_H__

//--------------------------------------------------------------------------------------------------
//  数据变量定义    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  函数调用声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
//  延迟函数 初始化 
void DELAY_Init(void);
//  延迟函数 1毫秒（1MS）级别
void DELAY_nMS(unsigned int Time);
void delay(unsigned int time);
void delay_us(unsigned int t);//T=2*t+5us  

#endif