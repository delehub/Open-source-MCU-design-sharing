#include "TFT.h"
#include "Ascii_8x16.h"                  //8x16大小字符
#include "Chinese.h"                     //16x16像素大小的汉字
/**********************************
***********************************
串行数据写入   作者：陈开放
***********************************
**********************************/
void Delay_TFT(u32 Delayms)
{
	u32 delay;
  for(;Delayms>0;Delayms--)
    for(delay=2000;delay>0;delay--);
}

void TFT_Writ_Bus(uchar date)
{		
	 SPI_SendByte(date);
}

/**********************************
***********************************
写数据8位数据    作者：陈开放
***********************************
**********************************/
void TFT_WR_DATA8(uchar date) 
{	
	  GPIO_SetBits(TFT_GPIO,TFT_DC);
	  TFT_Writ_Bus(date);
}
/**********************************
***********************************
写数据//16位数据    作者：陈开放
***********************************
**********************************/
void TFT_WR_DATA(uint date) 
{
  GPIO_SetBits(TFT_GPIO,TFT_DC);  
	TFT_Writ_Bus(date>>8);
	TFT_Writ_Bus(date);
}

/**********************************
***********************************
写命令     作者：陈开放
***********************************
**********************************/
void TFT_WR_REG(uchar date)  	 
{
  GPIO_ResetBits(TFT_GPIO,TFT_DC);
	TFT_Writ_Bus(date);
}

/**********************************
***********************************
写命令和写数据    作者：陈开放
***********************************
**********************************/
void TFT_WR_REG_DATA(uint reg,uint date) 
{
  TFT_WR_REG(reg);
	TFT_WR_DATA(date);
}

/**********************************
***********************************
设置起始地址x1,y1；终止地址x2,y2  
作者：陈开放
***********************************
**********************************/
void Address_set(uint x1,uint y1,uint x2,uint y2)
{  
   TFT_WR_REG(0x2a);
   TFT_WR_DATA8(x1>>8);
   TFT_WR_DATA8(x1);
   TFT_WR_DATA8(x2>>8);
   TFT_WR_DATA8(x2);
  
   TFT_WR_REG(0x2b);
   TFT_WR_DATA8(y1>>8);
   TFT_WR_DATA8(y1);
   TFT_WR_DATA8(y2>>8);
   TFT_WR_DATA8(y2);

   TFT_WR_REG(0x2C);
}

/**********************************
***********************************
清屏函数Color:要清屏的填充色
作者：陈开放
注：满屏240X320
***********************************
**********************************/
void TFT_Clear(uint Color)
{
	uchar VH,VL;
	uint i,j;
	VH=Color>>8;
	VL=Color;	
	Address_set(0,0,TFT_W,TFT_H);
  for(i=0;i<TFT_W;i++)
	{
	  for (j=0;j<TFT_H;j++)
	  {
      TFT_WR_DATA8(VH);
			TFT_WR_DATA8(VL);	
	  }
	 }
}

/****************************************************************************************************
//	实现功能：	显示Ascii字符
//  输入参数：  x 横坐标
//              y 纵坐标
//		        c 需要显示的字符
//		        fColor 字符颜色
//		        bColor 字符背景颜色
****************************************************************************************************/
void TFT_PutChar(unsigned int x, unsigned int y, char c, unsigned int fColor, unsigned int bColor)
{
 unsigned int i,j;
	
 Address_set(x,y,x+16-1,y+8-1);                    //设置字符显示位置
 	
 for(i=0; i<16;i++) 
 {                             //循环写入16字节，一个字符为16字节
		unsigned char m=Font8x16[(c-0x20)*16+i];  //提取c字符的第i个字节以,c减去0x20是由于Ascii码库中的0~1f被去掉
		for(j=0;j<8;j++) 
		{                        //循环写入8位，一个字节为8位
			if((m&0x80)==0x80)    //判断最高位是否为1
			{ 
        TFT_WR_DATA(fColor);				//最高位为1，写入字符颜色      
			}
			else 
			{
				TFT_WR_DATA(bColor);           //最高位为0，写入背景颜色
			}
			m<<=1;                                //左移1位，准备写下一位
		}
	}
}


/****************************************************************************************************
//	实现功能：	显示16x16汉字
//  输入参数： x 横坐标
//            y 纵坐标
//		        g 需要显示的字符编码
//		        fColor 字符颜色
//		        bColor 字符背景颜色
****************************************************************************************************/

void TFT_Put16x16(unsigned short x, unsigned short  y, unsigned char g[2], unsigned int fColor,unsigned int bColor)
{
	unsigned int i,j,k;
	
	Address_set(x,y,x+16-1,y+16-1);                       //设置汉字显示位置

	for (k=0;k<64;k++)                                      //循环64次，查询汉字字模位置
	{ 
	  if ((ch16[k].GBK[0]==g[0])&&(ch16[k].GBK[1]==g[1]))   //判断第k个汉字的编码是否与输入汉字g[2]相等
	  { 
    	for(i=0;i<32;i++)                                   //如果相等，既已找到待显示字模位置，循环写入32字节
		  {
		    unsigned short m=ch16[k].hz16[i];                 	//读取32字节中的第i字节
		    for(j=0;j<8;j++)                                  	//循环写入8位数据
		    {                                                
			   if((m&0x80)==0x80)
					 TFT_WR_DATA(fColor);     		//判断最高位是否为1,最高位为1，写入字符颜色
			   else             
					 TFT_WR_DATA(bColor);      		//最高位为0，写入背景颜色
		     m<<=1;                                         	//左移1位，准备写下一位
	     } 
		  }
      break;			
	  }  
  }
}


/****************************************************************************************************
//	实现功能：	显示中英文字符串
//  输入参数： x 横坐标
//            y 纵坐标
//		        *s 待显示的字符串,例如LCD_PutString(24,16,"123Eee",White,Blue);即把"123Eee"的第一个字符地址赋给指针变量s.
//		        bColor 字符背景颜色
****************************************************************************************************/
void TFT_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor) 
{
	 unsigned char l=0;                            	//显示屏位置增量
	
   while(*s) 
	 {
		if( *s < 0x80)                             		//判断s指向的字符串中的某字符的编码值是否小于128,如果小于,即为ASCII字符
		{
			TFT_PutChar(x,y+l*8,*s,fColor,bColor);			//显示该字符
		  s++;l++;                              		//指针加1,位置加1
		}
		else
		{
			TFT_Put16x16(x,y+l*8,(unsigned char*)s,fColor,bColor);		//显示该汉字
		  s+=2;l+=2;                                        	//因为汉字为编码为2字节，指针加2,显示16x16所以位置加2
	  }
	 }
}

/**********************************
***********************************
画点     作者：陈开放
注:POINT_COLOR为此点的颜色
***********************************
**********************************/
void TFT_DrawPoint(uint x,uint y,uint POINT_COLOR)
{
	Address_set(x,y,x,y);//设置光标位置 
	TFT_WR_DATA(POINT_COLOR); 	    
} 

/**********************************
***********************************
画大点     作者：陈开放
注:POINT_COLOR为此点的颜色
***********************************
**********************************/
void TFT_DrawPoint_big(uint x,uint y,uint POINT_COLOR)
{
	TFT_Fill(x-1,y-1,x+1,y+1,POINT_COLOR);
}


/**********************************
***********************************
在指定区域内填充指定颜色
作者：陈开放
注:区域大小(xend-xsta)*(yend-ysta)
***********************************
**********************************/
void TFT_Fill(uint xsta,uint ysta,uint xend,uint yend,uint color)
{          
	uint i,j; 
	Address_set(xsta,ysta,xend,yend);      //设置光标位置 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)TFT_WR_DATA(color);//设置光标位置 	    
	} 					  	    
} 
 
 

/**********************************
***********************************
画线      作者：陈开放
***********************************
**********************************/
void TFT_DrawLine(uint x1, uint y1, uint x2, uint y2,uint POINT_COLOR)
 {
	uint t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		TFT_DrawPoint(uRow,uCol,POINT_COLOR);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}    


/**********************************
***********************************
在指定位置画一个指定大小的圆
作者：陈开放
注：(x,y):中心点
     r:半径
***********************************
**********************************/
void Draw_Circle(uint x0,uint y0,uchar r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		TFT_DrawPoint(x0-b,y0-a,WHITE);             //3           
		TFT_DrawPoint(x0+b,y0-a,WHITE);             //0           
		TFT_DrawPoint(x0-a,y0+b,WHITE);             //1       
		TFT_DrawPoint(x0-b,y0-a,WHITE);             //7           
		TFT_DrawPoint(x0-a,y0-b,WHITE);             //2             
		TFT_DrawPoint(x0+b,y0+a,WHITE);             //4               
		TFT_DrawPoint(x0+a,y0-b,WHITE);             //5
		TFT_DrawPoint(x0+a,y0+b,WHITE);             //6 
		TFT_DrawPoint(x0-b,y0+a,WHITE);             
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
		TFT_DrawPoint(x0+a,y0+b,WHITE);
	}
} 

/**********************************
***********************************
在指定位置显示图片  作者：陈开放
注：image[]对应data.c
    i图片数组大小
***********************************
**********************************/
void showimage(uchar image[],uint i,uint xs,uint ys,uint xe,uint ye) //显示图片
{
	uint index;
	Address_set(xs,ys,xe-1,ye-1);		//设置坐标
	for(index=0;index<i/2;index++)
	{	
			
		TFT_WR_DATA8(image[index*2+1]);	 //发送颜色数据
		TFT_WR_DATA8(image[index*2]);					
		
	}
}
 
//初始化lcd
void TFT_Init(void)
{ 

 	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );//PORTA时钟使能 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );//PORTA时钟使能 
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 ;	  //Pin_5 sck  pin7 MOSI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PA5/7/复用推挽输出 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);//PA4	CS

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC, GPIO_Pin_14);//PB0	LCD_RST
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOC, GPIO_Pin_15);//PC4	DC
 
  SPI_Configuration();	 
	GPIO_ResetBits(TFT_GPIO,TFT_REST);
  Delay_TFT(120); //Delay 120ms
	GPIO_SetBits(TFT_GPIO,TFT_REST); 
	Delay_TFT(200); // delay 20 ms 
	GPIO_ResetBits(TFT_GPIO,TFT_CS);  //打开片选使能

	TFT_WR_REG(0x11); //Sleep out
	Delay_TFT(120); //Delay 120ms
	//------------------------------------ST7735S Frame Rate-----------------------------------------//
	TFT_WR_REG(0xB1);
	TFT_WR_DATA8(0x05);
	TFT_WR_DATA8(0x3C);
	TFT_WR_DATA8(0x3C);
	TFT_WR_REG(0xB2);
	TFT_WR_DATA8(0x05);
	TFT_WR_DATA8(0x3C);
	TFT_WR_DATA8(0x3C);
	TFT_WR_REG(0xB3);
	TFT_WR_DATA8(0x05);
	TFT_WR_DATA8(0x3C);
	TFT_WR_DATA8(0x3C);
	TFT_WR_DATA8(0x05);
	TFT_WR_DATA8(0x3C);
	TFT_WR_DATA8(0x3C);
	//------------------------------------End ST7735S Frame Rate-----------------------------------------//
	TFT_WR_REG(0xB4); //Dot inversion
	TFT_WR_DATA8(0x03);
	TFT_WR_REG(0xC0);
	TFT_WR_DATA8(0x28);
	TFT_WR_DATA8(0x08);
	TFT_WR_DATA8(0x04);
	TFT_WR_REG(0xC1);
	TFT_WR_DATA8(0XC0);
	TFT_WR_REG(0xC2);
	TFT_WR_DATA8(0x0D);
	TFT_WR_DATA8(0x00);
	TFT_WR_REG(0xC3);
	TFT_WR_DATA8(0x8D);
	TFT_WR_DATA8(0x2A);
	TFT_WR_REG(0xC4);
	TFT_WR_DATA8(0x8D);
	TFT_WR_DATA8(0xEE);
	//---------------------------------End ST7735S Power Sequence-------------------------------------//
	TFT_WR_REG(0xC5); //VCOM
	TFT_WR_DATA8(0x1A);
	TFT_WR_REG(0x36); //MX, MY, RGB mode///////////////////////////
	TFT_WR_DATA8(0x58);
	//------------------------------------ST7735S Gamma Sequence-----------------------------------------//
	TFT_WR_REG(0xE0);
	TFT_WR_DATA8(0x04);
	TFT_WR_DATA8(0x22);
	TFT_WR_DATA8(0x07);
	TFT_WR_DATA8(0x0A);
	TFT_WR_DATA8(0x2E);
	TFT_WR_DATA8(0x30);
	TFT_WR_DATA8(0x25);
	TFT_WR_DATA8(0x2A);
	TFT_WR_DATA8(0x28);
	TFT_WR_DATA8(0x26);
	TFT_WR_DATA8(0x2E);
	TFT_WR_DATA8(0x3A);
	TFT_WR_DATA8(0x00);
	TFT_WR_DATA8(0x01);
	TFT_WR_DATA8(0x03);
	TFT_WR_DATA8(0x13);
	TFT_WR_REG(0xE1);
	TFT_WR_DATA8(0x04);
	TFT_WR_DATA8(0x16);
	TFT_WR_DATA8(0x06);
	TFT_WR_DATA8(0x0D);
	TFT_WR_DATA8(0x2D);
	TFT_WR_DATA8(0x26);
	TFT_WR_DATA8(0x23);
	TFT_WR_DATA8(0x27);
	TFT_WR_DATA8(0x27);
	TFT_WR_DATA8(0x25);
	TFT_WR_DATA8(0x2D);
	TFT_WR_DATA8(0x3B);
	TFT_WR_DATA8(0x00);
	TFT_WR_DATA8(0x01);
	TFT_WR_DATA8(0x04);
	TFT_WR_DATA8(0x13);
	//------------------------------------End ST7735S Gamma Sequence-----------------------------------------//
	TFT_WR_REG(0x3A); //65k mode
	TFT_WR_DATA8(0x05);
	TFT_WR_REG(0x29); //Display on
	TFT_Clear(WHITE);
}  
 



