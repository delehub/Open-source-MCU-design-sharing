/********************************************
*山东建筑大学 锐思实验室                    *
*函数名称：LCD12864程序                     *
*CPU型号：STC89C52                          *
*晶振参数：12MHZ                            *
*程序作者：2009级        许方超             *
*联系方式：QQ：610949704                    *
*我的淘宝：yy3q.taobao.com欢饮点击攒人气    *
********************************************/
#include "LCD12864.h"

void Delay_40US(void)   
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=17;a>0;a--);
}
/**************************************
为加速逻辑运算而设置的掩码表，
这是以牺牲空间而换取时间的办法
***************************************/
code unsigned int LcdMaskTab[]=
{0x0001,0x0002,0x0004,0x0008,
 0x0010,0x0020,0x0040,0x0080,
 0x0100,0x0200,0x0400,0x0800,
 0x1000,0x2000,0x4000,0x8000};
/*************
测试LCD是否处于忙
**************/
void LCD12864_CheckBusy(void)
{
    unsigned char Busy,num;
	LcdData=0xff;
	num=100;
    LCD12864_RS_L;
    LCD12864_RW_H;
    LCD12864_EN_H;
    Delay_40US();  
    Busy=LcdData&0x80;
    LCD12864_EN_L;
    while(Busy&num--);
}

/*********************************
向LCD写入字节数据
**********************************/
void LCD12864_WriteData(unsigned char Data)
{  
	LCD12864_CheckBusy();
	LCD12864_RS_H;
	LCD12864_RW_L;
	LCD12864_EN_L;
	LcdData=Data;
    Delay_40US();   
	LCD12864_EN_H;
    Delay_40US();    
	LCD12864_EN_L;
}

/***********************************
从LCD中读出数据
************************************/
unsigned char LCD12864_ReadData(void)
{
	unsigned char Temp;
	LCD12864_CheckBusy();
 	LcdData=0xff;
    LCD12864_RS_H;
	LCD12864_RW_H;
	LCD12864_EN_H;
    Delay_40US();  
	Temp=LcdData;
	LCD12864_EN_L;
   	return Temp;
}

/*************************************
向LCD中写入指令代码
**************************************/
void LCD12864_WriteCmd(unsigned char CmdCode)
{  
    LCD12864_CheckBusy();
   	LCD12864_RS_L;
   	LCD12864_RW_L;
   	LCD12864_EN_L;
    Delay_40US();   
   	LcdData=CmdCode;
    Delay_40US();   
   	LCD12864_EN_H;
    Delay_40US();   
   	LCD12864_EN_L;
}
/***********************
 12864设定初始显示位置
 X为行的数目
 Y为列的数目
 ***********************/
 void LCD12864_SetPoint(uchar X,uchar Y)
 {
 	uchar pos;
	LCD12864_WriteCmd(0x30);
	if     (X==1){X=0x80;}
	else if(X==2){X=0x90;}
    else if(X==3){X=0x88;}
	else if(X==4){X=0x98;}
	pos=X+Y;
	LCD12864_WriteCmd(pos);
 }
 /*****************************************
 设置图像显示模式
 select=0时，关闭图形显示模式
 Select=1时，开启图形显示模式
 LCD_EXTEND_FUNCTION为 扩展指令集
 LCD_GRAPH_ON	打开绘图模式命令
 LCD_GRAPH_OFF	关闭绘图模式命令
 ******************************************/
void LCD12864_SetMode(unsigned char Select)
{
	LCD12864_WriteCmd(LCD_EXTEND_FUNCTION);	   
	if(Select){LCD12864_WriteCmd(LCD_GRAPH_ON);} 
	else      {LCD12864_WriteCmd(LCD_GRAPH_OFF);}      
}
/*************************************
向LCD指定起始位置写入一个字符串
*************************************/
void LCD12864_DisplayString(unsigned char x,unsigned char y,unsigned char *Str)
{	  
	if((y>4)||(x>8)) return;
	LCD12864_SetPoint(x,y);	
	while(*Str>0)
	{ LCD12864_WriteData(*Str); Str++;}
}
 /*******************************************
 按页显示，同时显示四行
 *******************************************/
void LCD12864_DisplayPage( uchar code *adder1)
 {
	    unsigned char i;
        LCD12864_WriteCmd(0x80);  
	    for(i=0;i<32;i++)
		{LCD12864_WriteData(*adder1);adder1++;}
		LCD12864_WriteCmd(0x90);
	    for(i=32;i<64;i++)
		{LCD12864_WriteData(*adder1);adder1++;}

}
/*********************************************
向LCD写入一个8位的ASCII码
以显示相应的字符
**********************************************/																		
void LCD12864_SendASCII(uchar hang,uchar lie,char sign) 
{

	LCD12864_SetPoint(hang,lie);		 
    LCD12864_WriteData(sign);	 
	 
}
/*********************************************
向LCD写入一个16位的GB2312码
以显示相应的字符
**********************************************/
void LCD12864_SendGB2312(uchar hang,uchar lie,unsigned int sign) 
{
	unsigned char templ, temph;
	templ=sign&0x00ff;
	temph=sign>>8 ;
	LCD12864_WriteCmd(0x30);
	LCD12864_SetPoint(hang,lie);
    LCD12864_WriteData(temph);
	Delay_40US();
	LCD12864_WriteData(templ);	 
	 
}
/***************************************
向LCD指定坐标写入一个象素,象素颜色有两种，
0代表白（无显示），1代表黑（有显示）
****************************************/
void LCD12864_WritePixel(unsigned char x,unsigned char y,unsigned char color)
{

    unsigned char x_Dyte,y_Dyte,x_bite;				//定义列地址的字节位，及在字节中的哪1位 
	unsigned char GDRAM_hbit,GDRAM_lbit;				//定义为上下两个屏(取值为0，1)，行地址(取值为0~31)

 x_Dyte=x/16;
 x_bite=x&0x0f;
 if(y<32)
 	{
		y_Dyte=y;
	}
 else
 	{
 		y_Dyte=y-32;
 		x_Dyte=x_Dyte+8;
 	}
 LCD12864_WriteCmd(LCD_EXTEND_FUNCTION);
 LCD12864_WriteCmd(LCD_GRAPH_ON);
 LCD12864_WriteCmd(0x80+y_Dyte);
 LCD12864_WriteCmd(0x80+x_Dyte);
 LCD12864_ReadData();
 GDRAM_hbit=LCD12864_ReadData();
 GDRAM_lbit=LCD12864_ReadData();
if(x_bite<8)
  	{
  	switch(color)
		{
	 		case 0 :GDRAM_hbit&=(~(1<<(7-x_bite)));break;
	 		case 1 :GDRAM_hbit|=(1<<(7-x_bite));   break;
	 		case 2 :GDRAM_hbit^=(1<<(7-x_bite));	break;
	 		default :break;
		}
	}
else 
	{
	  	switch(color)
		{
	 		case 0 :GDRAM_lbit&=(~(1<<(15-x_bite)));break;
	 		case 1 :GDRAM_lbit|=(1<<(15-x_bite));   break;
	 		case 2 :GDRAM_lbit^=(1<<(15-x_bite));	break;
	 		default :break;
		}

	

	}
 LCD12864_WriteCmd(0x80+y_Dyte);
 LCD12864_WriteCmd(0x80+x_Dyte);
 LCD12864_WriteData(GDRAM_hbit);
 LCD12864_WriteData(GDRAM_lbit);
 LCD12864_WriteCmd(LCD_EXTEND_FUNCTION);
 LCD12864_WriteCmd(LCD_GRAPH_OFF);
}
/*********************************
清空LCD的DRAM
*********************************/
void LCD12864_ClearDRAM(void)
{	unsigned char i,j;
    LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x30);
	for(i=1;i<5;i++)
	for(j=1;j<9;j++) 
	LCD12864_SendGB2312(i,j,0xB0A0);
}
/*****************************************
清除Lcd全屏，如果清除模式Mode为0，则为全屏清除为颜色0（无任何显示）
否则为全屏清除为颜色1(全屏填充显示)
******************************************/
void LCD12864_ClearGRAM(unsigned char Mode)
{
	unsigned char x,y,ii;
	unsigned char Temp;
	if(Mode%2==0)Temp=0x00;	
	else Temp=0xff;	
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x36);//扩充指令 绘图显示
	for(ii=0;ii<9;ii+=8)   
		for(y=0;y<0x20;y++)     
			for(x=0;x<8;x++)
			{ 	
				
				LCD12864_WriteCmd(y+0x80);        //行地址
				LCD12864_WriteCmd(x+0x80+ii);     //列地址     
				LCD12864_WriteData(Temp); //写数据 D15－D8 
				LCD12864_WriteData(Temp); //写数据 D7－D0 
			
			}

}
/**********************************************
清空LCD中的GRAM 和 ＤＲＡＭ
**********************************************/
void LCD12864_ClearGDRAM(void)
{
	 LCD12864_ClearDRAM();
	 LCD12864_ClearGRAM(0);
	
} 
/***********************************************************
函数名：  dispU_picture
函数说明： 上半屏显示一幅128*32的图画
传入参数：图形指针*img
传出参数：无
返回值：  无
**********************************************************/
void LCD12864_DisplayPicup(unsigned char *img)
{
  unsigned char i,j;
  LCD12864_SetMode(0);
  for(j=0;j<32;j++)
  {
    for(i=0;i<8;i++)
    {
      LCD12864_WriteCmd(0x34);
      LCD12864_WriteCmd(0x80+j);
      LCD12864_WriteCmd(0x80+i);
      LCD12864_WriteCmd(0x30);
      LCD12864_WriteData(img[j*16+i*2]);
      LCD12864_WriteData(img[j*16+i*2+1]);
    }
  }
  LCD12864_SetMode(1);
}
/***********************************************************
函数名：  dispD_picture
函数说明： 下半屏显示一幅128*32的图画
传入参数：图形指针*img
传出参数：无
返回值：  无
**********************************************************/
void LCD12864_DisplayPicdown(unsigned char *img)
{
  unsigned char i,j;
  LCD12864_SetMode(0);
  for(j=0;j<32;j++)
  {
    for(i=0;i<8;i++)
    {
      LCD12864_WriteCmd(0x34);
      LCD12864_WriteCmd(0x80+j);
      LCD12864_WriteCmd(0x80+(i+8));
      LCD12864_WriteCmd(0x30);
      LCD12864_WriteData(img[j*16+i*2]);
      LCD12864_WriteData(img[j*16+i*2+1]);
    }
  }
  LCD12864_SetMode(1);
}

/***********************************************************
函数名：  disp_picture
函数说明： 显示一幅128*64的图画
传入参数：图形指针*img
传出参数：无
返回值：  无
**********************************************************/
void LCD12864_DisplayPicAll(unsigned char *img)
{
  unsigned char i,j;
  LCD12864_SetMode(1);
  for(j=0;j<32;j++)
  {
    for(i=0;i<8;i++)
    {
      LCD12864_WriteCmd(0x34);
      LCD12864_WriteCmd(0x80+j);
      LCD12864_WriteCmd(0x80+i);
      LCD12864_WriteCmd(0x30);
      LCD12864_WriteData(img[j*16+i*2]);
      LCD12864_WriteData(img[j*16+i*2+1]);
    }
  }
  for(j=32;j<64;j++)
  {
    for(i=0;i<8;i++)
    { LCD12864_WriteCmd(0x34);
      LCD12864_WriteCmd(0x80+j-32);
      LCD12864_WriteCmd(0x80+(i+8));
      LCD12864_WriteCmd(0x30);
      LCD12864_WriteData(img[j*16+i*2]);
      LCD12864_WriteData(img[j*16+i*2+1]);
    }
  }
  LCD12864_SetMode(1);
}


/******************************************
从LCD指定坐标读取象素颜色值
*******************************************/
unsigned char LCD12864_ReadPixel(unsigned char x,unsigned char y)
{
	unsigned char z,w;
	unsigned int Temp;
	if(x>=128||y>=64) return 0;
	w=15-x%16;		 //确定对这个字的第多少位进行操作
	x=x/16;          //确定为一行上的第几字
	if(y<32)z=0x80;  //如果为上页	
	else z=0x88;     //否则如果为下页
	y=y%32;	
	LCD12864_WriteCmd(0x36);
	LCD12864_WriteCmd(y+0x80);        //行地址
	LCD12864_WriteCmd(x+z);           //列地址 
	Temp=LCD12864_ReadData();                 //先空读一次
	Temp=(unsigned int)LCD12864_ReadData()<<8;//再读出高8位
	Temp|=(unsigned int)LCD12864_ReadData();  //再读出低8位
	if((Temp&&LcdMaskTab[w])==0)return 0;	
	else return 1;
		
}

/***************************************
向LCD指定位置画一条长度为Length的指定颜色的水平线
****************************************/
void LCD12864_DrawLineH(unsigned char x,unsigned char y,unsigned char Length,unsigned char Color)
{
	unsigned char count;
	if(Length==0)return;
	LCD12864_SetMode(0);	
	for(count=0;count<Length;count++)
	{LCD12864_WritePixel(x+count,y,Color);}
	LCD12864_SetMode(1);	
}



/***************************************
向LCD指定位置画一条长度为Length的指定颜色的垂直线
****************************************/
void LCD12864_DrawLineV(unsigned char x,unsigned char y,unsigned char Length,unsigned char Color)
{
	unsigned char count;
	if(Length==0)	return;
	for(count=0;count<Length;count++)
	{LCD12864_WritePixel(x,y+count,Color);}	
}
/*******************************************
向LCD指定起始坐标和结束坐标之间画一条指定颜色的直线
********************************************/
void LCD12864_DrawLineR(unsigned char x1,unsigned char y1,unsigned char x2,unsigned char y2,unsigned char Color)
{
	unsigned int x,y; 
	unsigned int d_x,d_y;
	int err=0;
	unsigned char temp=0;
	if(y2<y1)
	{x=x1;y=y1;x1=x2;y1=y2;x2=x;y2=y;}
	d_y=y2-y1;	
	if (d_y==0)
	{
		if (x1>x2) 
		{x=x1;x1=x2;x2=x;}
		for (x=x1;x<=x2;x++) 
		LCD12864_WritePixel(x,y1,Color);			
	}
	else
	{
		if(x2>=x1)
		{temp=1;d_x=x2-x1;}
		else {d_x=x1-x2;}	
		x=x1;y=y1;	
		LCD12864_WritePixel(x,y,1);		
		if(temp&&(d_y<=d_x))
		while(x!=x2)
			{
				if(err<0)
				{x=x+1;err=err+(y2-y);}
				else 
				{ x=x+1;y=y+1;err=err+(y2-y)-(x2-x);}	
				LCD12864_WritePixel(x,y,Color);
			}

		else if(temp&&(d_y>d_x))
			while(y!=y2)
			{ d_x=x2-x;d_y=y2-y; 
				if(err<0)
				{ x=x+1;y=y+1;err=err+d_y-d_x;}
				else 
				{ y=y+1;err=err-d_x;}
				LCD12864_WritePixel(x,y,Color);
			}

		else if(!temp&&(d_y<=d_x))
			while(x!=x2)
			{  d_x=x-x2;d_y=y2-y;
				if(err<0)
				{ x=x-1;err=err+d_y;}
				else 
				{ x=x-1;y=y+1;err=err+d_y-d_x;}
				LCD12864_WritePixel(x,y,Color);
			}

		else if(!temp &&(d_y>d_x))
			while(y!=y2)
			{d_x=x-x2; d_y=y2-y;
				if(err<0)
				{x=x-1;y=y+1;err=err+d_y-d_x;}
				else 
				{y=y+1;err=err-d_x;	}
				LCD12864_WritePixel(x,y,Color);	
			}
	}
}

/*******************************************
向LCD指定左上角坐标和右下角坐标画一个指定颜色的矩形
********************************************/
void LCD12864_DrawRectangle(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char Color)
{
	unsigned char Temp;
	if(x0>x1) {Temp=x0;x0=x1;x1=Temp;}
	if(y0>y1) {Temp=y0;y0=y1;y1=Temp;}	
	LCD12864_DrawLineV(x0,y0,y1-y0+1,Color);
	LCD12864_DrawLineV(x1,y0,y1-y0+1,Color);
	LCD12864_DrawLineH(x0,y0,x1-x0+1,Color);
	LCD12864_DrawLineH(x0,y1,x1-x0+1,Color);	
}
/****************************************
对称法画圆的8个镜像点
*****************************************/
void LCD12864_DrawCircleDot(unsigned char x,unsigned char y,char xx,char yy,unsigned char Color)//内部函数，对称法画圆的8个镜像点
{

	LCD12864_WritePixel((x+yy),(y+xx),Color);//第 1 个 8 分圆
	LCD12864_WritePixel((x+xx),(y+yy),Color);//第 2 个 8 分圆
	LCD12864_WritePixel((x-xx),(y+yy),Color);//第 3 个 8 分圆
	LCD12864_WritePixel((x-yy),(y+xx),Color);//第 4 个 8 分圆
	LCD12864_WritePixel((x-yy),(y-xx),Color);//第 5 个 8 分圆
	LCD12864_WritePixel((x-xx),(y-yy),Color);//第 6 个 8 分圆
	LCD12864_WritePixel((x+xx),(y-yy),Color);//第 7 个 8 分圆
	LCD12864_WritePixel((x+yy),(y-xx),Color);//第 8 个 8 分圆
	
}

/******************************************
向LCD指定圆心坐标画一个半径为r的指定颜色的圆
*******************************************/
void LCD12864_DrawCircle(unsigned char x,unsigned char y,unsigned char r,unsigned char Color)//中点法画圆
{//中点法画圆
	unsigned char xx,yy;
	char deltax,deltay,d;
	xx=0;
	yy=r;
	deltax=3;
	deltay=2-r-r;
	d=1-r;
	LCD12864_DrawCircleDot(x,y,xx,yy,Color);//对称法画圆的8个镜像点
	while (xx<yy)
	{
		if (d<0){ d+=deltax;deltax+=2;xx++;}
		else
		{ d+=deltax+deltay;	deltax+=2;deltay+=2;xx++;yy--;}
		LCD12864_DrawCircleDot(x,y,xx,yy,Color);//对称法画圆的8个镜像点
	}
}



/***************
0x01为待机模式
0x02为睡眠模式
0x0c脱离睡眠
*******************/
void LCD12864_SetStatus(unsigned char cmd)
{  
	
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(cmd);

}
/****************************************
LCD初始化
*****************************************/
void LCD12864_Init()
{   
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x30);       //选择基本指令集
	LCD12864_WriteCmd(0x0c);       //开显示(无游标、不反白)
	LCD12864_WriteCmd(0x01);       //清除显示，并且设定地址指针为00H
	LCD12864_WriteCmd(0x06);       //指定在资料的读取及写入时，设定游标的移动方向及指定显示的移位
}


/*--以下为protues里面液晶驱动程序--*/
/****************************************
LCD初始化
*****************************************/
void LCD12864_Init1()
{  
	LCD12864_RET=0;
	LCD12864_RET=1;
	LCD12864_CS1=1;
    LCD12864_CS2=1;
  	LCD12864_WriteCmd(Disp_Off);
  	LCD12864_WriteCmd(Page_Add+0);
  	LCD12864_WriteCmd(Start_Line+0);
  	LCD12864_WriteCmd(Col_Add+0);
  	LCD12864_WriteCmd(Disp_On);
}

void LCD12864_DisplayImg(unsigned char code *img)
 {
  unsigned char j,k;
  for(k=0;k<8;k++)
   {
    LCD12864_CS2=1;
	LCD12864_CS1=0;
    LCD12864_WriteCmd(Page_Add+k);
    LCD12864_WriteCmd(Col_Add+0);
    for(j=0;j<64;j++) 
	LCD12864_WriteData(img[k*128+j]);
    LCD12864_CS2=0;
	LCD12864_CS1=1;
    LCD12864_WriteCmd(Page_Add+k);
    LCD12864_WriteCmd(Col_Add+0);
    for(j=64;j<128;j++) 
	LCD12864_WriteData(img[k*128+j]);
   }
 }

 void LCD12864_DisplayChar(unsigned char pag,unsigned char col, unsigned char code *szk)
 {
  unsigned char j=0,i=0;
  for(j=0;j<2;j++)
   {
    LCD12864_WriteCmd(Page_Add+pag+j);
    LCD12864_WriteCmd(Col_Add+col);
    for(i=0;i<16;i++) 
	LCD12864_WriteData(szk[16*j+i]);
   }
 }

 /*------------------------清显示屏--------------------------------*/
void LCD12864_ClearScreen()
 {
  	unsigned char j,k;
  	LCD12864_CS2=1;
	LCD12864_CS1=0;             // 清左半屏 //
   {
    LCD12864_WriteCmd(Page_Add+0);
    LCD12864_WriteCmd(Col_Add+0);
    for(k=0;k<4;k++)               // 清左上半屏 //
     {
      for(j=0;j<64;j++)
	  LCD12864_WriteData(0x00);
     }
    for(k=0;k<4;k++)               // 清左下半屏 //
     {
      LCD12864_WriteCmd(Page_Add+4);
      for(j=0;j<64;j++)
	  LCD12864_WriteData(0x00);
     }
   }
  	LCD12864_CS2=0;
	LCD12864_CS1=1;                    // 清右半屏 //
   {
   	LCD12864_WriteCmd(Page_Add+0);
    LCD12864_WriteCmd(Col_Add+0);
    for(k=0;k<4;k++)               // 清右上半屏 //
     {
      for(j=0;j<64;j++)
	  LCD12864_WriteData(0x00);
     }
    for(k=0;k<4;k++)               // 清右下半屏 //
     {
	  LCD12864_WriteCmd(Page_Add+4);
      for(j=0;j<64;j++)
	  LCD12864_WriteData(0x00);
     }
   }
 }
void  LCD12864_SelectScreen(unsigned char Scr)
{
  if(Scr==1)
  {
    LCD12864_CS1=1;
    LCD12864_CS2=0;
  }
  else
  {
    LCD12864_CS1=0;
    LCD12864_CS2=1;
  }

}