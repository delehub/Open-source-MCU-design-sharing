#ifndef __MMA7455_H__
#define __MMA7455_H__
#include "IIC.H"
#define uchar unsigned char
#define uint  unsigned int
#define IIC_READ  0x1D      //定义读指令
#define IIC_WRITE 0x1D      //定义写指令
#define MMA7455_ADDER_WRITE 0x3A //0x1D 左移，后边补一写位 0 ，得到0x3A
#define MMA7455_ADDER_READ 0x3B  //0x1D 左移，后边补一读位 1 ，得到0x3B
#define MMA7455_Mode_Control_Register 0x16
#define MMA7455_WHOAMI 0X0F
#define MMA7455_2G_Measurement_Mode 0x05
#define MMA7455_READ_X 0x06   //读 8bits X轴数据地址
#define MMA7455_READ_Y 0x07   //读 8bits y轴数据地址
#define MMA7455_READ_Z 0x08   //读 8bits y轴数据地址
#define MMA7455_READ_STATUS 0x09   // 8位状态寄存器
#define MMA7455_RW_XOFFL 0x10  //X轴补偿低字节
#define MMA7455_RW_YOFFL 0x12  //Y轴补偿低字节、
#define MMA7455_RW_ZOFFL 0x14  //Z轴补偿低字节
void IIC_MMA7455_init();
void IIC_MMA7455_writedata(uchar byte_add,uchar wdata);//函数功能：按地址写入一字节数据
unsigned char IIC_MMA7455_readdata(uchar byte_add);	   //函数功能：按地址读出一字节数据
unsigned char IIC_MMA7455_test();
unsigned char IIC_MMA7455_calibrate_X();
unsigned char IIC_MMA7455_calibrate_Y();
unsigned char IIC_MMA7455_calibrate_Z();
unsigned char IIC_MMA7455_getvalue(unsigned char address_byte);
unsigned char IIC_MMA7455_getaverage(unsigned char address_byte);
unsigned char IIC_MMA7455_getacceleration(unsigned char address_byte);
#endif
