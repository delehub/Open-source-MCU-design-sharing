 #include<reg52.h>
 sbit TLC2543_DIN=P1^2;
 sbit TLC2543_DOUT=P1^3;
 sbit TLC2543_CS=P1^4;
 sbit TLC2543_CLK=P1^1;
 sbit TLC2543_EOC=P1^0;
 extern unsigned char TLC2543_DATA[7];
 #define TLC2543_Delay TLC2543_Delay10us()
 #define uint8 unsigned char
 #define uint16 unsigned int
 #define uint32 unsigned long
 #define TLC2543_CS_L   TLC2543_CS=0
 #define TLC2543_CS_H   TLC2543_CS=1
 #define TLC2543_CLK_H  TLC2543_CLK=1
 #define TLC2543_CLK_L  TLC2543_CLK=0
 #define TLC2543_DOUT_H TLC2543_DOUT=1
 #define TLC2543_DOUT_L TLC2543_DOUT=0
 #define TLC2543_EOC_H  TLC2543_EOC=1
 #define TLC2543_A0     0X00
 #define TLC2543_A1     0X10
 #define TLC2543_A2     0X20
 #define TLC2543_A3     0X30
 #define TLC2543_A4     0X40
 #define TLC2543_A5     0X50
 #define TLC2543_A6     0X60
 #define TLC2543_A7     0X70
 #define TLC2543_A8     0X80
 #define TLC2543_A9     0X90
 #define TLC2543_A10    0XA0
 #define TLC2543_TEST1   0XB0
 #define TLC2543_TEST2   0XC0
 #define TLC2543_TEST3   0XD0
 #define TLC2543_SLEEP   0XE0
 #define TLC2543_8BIT    0x04
 #define TLC2543_12BIT   0x08
 #define TLC2543_16BIT   0x0C
 #define TLC2543_SinPolar   0x00
 #define TLC2543_DouPolar   0x01
 uint16 TLC2543_ReadData(uint8 AX);
 uint32 TLC2543_GetVoltage(uint8 AX,uint8 Vref);
