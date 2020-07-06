#ifndef __TFT_H
#define __TFT_H

#include "stm32f10x_gpio.h"
#include "SPI.h"
#include "TIM.h"

#define uchar unsigned char
#define uint unsigned int
	
/******************
TFT的IO口定义
******************/
#define TFT_GPIO  GPIOC

#define TFT_CS   GPIO_Pin_13
#define TFT_REST GPIO_Pin_14
#define TFT_DC   GPIO_Pin_15

/*定义LCD的尺寸*/
#define TFT_W 129
#define TFT_H 130

/*定义LCD的背光状态*/
#define LED_ON  Bit_RESET
#define LED_OFF Bit_SET


/*画笔颜色//GUI颜色*/
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F //0000 0000 0001 1111
#define GREEN         	 0x07E0 //0000 0111 1110 0000
#define RED           	 0xF800 //1111 1000 0000 0000
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define BRED             0XF81F
#define MAGENTA       	 0xF81F//品红
#define CYAN          	 0x7FFF//蓝绿色
#define YELLOW        	 0xFFE0//黄色
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色


/*以上三色为PANEL的颜色*/ 
#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色

 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE         0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)

void TFT_Init(void);
void TFT_Writ_Bus(uchar date);
void TFT_WR_DATA8(uchar date);
void TFT_WR_DATA(uint date);
void TFT_WR_REG(uchar date);
void TFT_WR_REG_DATA(uint reg,uint date);
void Address_set(uint x1,uint y1,uint x2,uint y2);
void TFT_Clear(uint Color);					  		 
void TFT_DrawPoint(uint x,uint y,uint POINT_COLOR);
void TFT_DrawPoint_big(uint x,uint y,uint POINT_COLOR);
void TFT_Fill(uint xsta,uint ysta,uint xend,uint yend,uint color);
void TFT_DrawLine(uint x1, uint y1, uint x2, uint y2,uint POINT_COLOR);
void Draw_Circle(uint x0,uint y0,uchar r);
void showimage(uchar image[],uint i,uint xs,uint ys,uint xe,uint ye) ; //显示图片
void TFT_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor);
void TFT_PutChar(unsigned int x, unsigned int y, char c, unsigned int fColor, unsigned int bColor);
void TFT_Put16x16(unsigned short x, unsigned short  y, unsigned char g[2], unsigned int fColor,unsigned int bColor);

#endif  



