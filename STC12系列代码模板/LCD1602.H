#ifndef __LCD1602_H__
#define __LCD1602_H__

//--------------------------------------------------------------------------------------------------
//  数据变量定义    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------------
//  函数调用声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
//  LCD1602 初始化 
void LCD1602_Init(void);

//  LCD1602 清屏函数
void LCD1602_Clear(void);

//  LCD1602 显示字符 字符串 数组
void LCD1602_ShowChar(unsigned char X,unsigned char Y,unsigned char Char);
void LCD1602_ShowString(unsigned char X,unsigned char Y,unsigned char *String);
void LCD1602_ShowArray(unsigned char X,unsigned char Y,unsigned char *Array,unsigned char Count);

//  LCD1602 显示整型数字、浮点型数字、二进制数字
void LCD1602_ShowNumber_Integer(unsigned char X,unsigned char Y,int IntegerNumber,unsigned char Count);
void LCD1602_ShowNumber_Float(unsigned char X,unsigned char Y,float FloatNumber,unsigned char Count1,unsigned char Count2);
void LCD1602_ShowNumber_Binary(unsigned char X,unsigned char Y,unsigned int BinaryNumber,unsigned char Count);

#endif
