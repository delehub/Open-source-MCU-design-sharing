/******************************************
 通用型1602液晶显示函数
 编写人：许方超	QQ 610949704   1135079828
 本人也是单片机爱好者希望能和喜欢单片机的人互相学习
 ************************************************/ 
#include "LCD1602.H"
#define LCD1602_DATA P0
sbit LCD1602_RS=P2^0; //数据命令选择端（4）：L为命令；H为数据
sbit LCD1602_RW=P2^1; //读写选择端（5）：L为写模式；H为读模式
sbit LCD1602_EN=P2^2; //使能信号（6）：高脉冲完成数据指令读写
#define LCD1602_RS_L LCD1602_RS=0
#define LCD1602_RS_H LCD1602_RS=1
#define LCD1602_RW_L LCD1602_RW=0
#define LCD1602_RW_H LCD1602_RW=1
#define LCD1602_EN_L LCD1602_EN=0
#define LCD1602_EN_H LCD1602_EN=1
/*********************************
延时50微妙
********************************/
void LCD1602_Delayus()
{
    unsigned char a,b;
    for(b=1;b>0;b--)
    for(a=22;a>0;a--);
}
/********************************
延时10毫秒
********************************/
void LCD1602_Delayms()
{
    unsigned int i,j;
	for(i=10;i>0;i--)
	for(j=113;j>0;j--);
}
/******************************
1602写命令函数
*****************************/
void LCD1602_WriteCmd(uchar cmd)
{	
    LCD1602_DATA=cmd;
	LCD1602_RW_L;
	LCD1602_RS_L;//RS拉低，选择写命令	
	
	LCD1602_EN_H;//恢复初始化
	LCD1602_Delayus();   //短暂延时
	LCD1602_EN_L;//使能端上升沿完成操作
	LCD1602_Delayus();   //短暂延时
}

void LCD1602_MoveCursor(uchar dir)
{	
   uchar temp_dir;
   temp_dir=0x10+dir*4;
   LCD1602_WriteCmd(temp_dir);
}
void LCD1602_MoveScreen(uchar dir)
{	
   uchar temp_dir;
   temp_dir=0x18+dir*4;
   LCD1602_WriteCmd(temp_dir);
}
/*****************************
1602写数据函数
*****************************/
void LCD1602_WriteData(uchar dat)
{	  
      LCD1602_DATA=dat;
	  LCD1602_RW_L;
	  LCD1602_RS_H; //RS拉高选择写数据
	  LCD1602_EN_H; //使能端上升沿完成操作
	  LCD1602_Delayus() ;
	  LCD1602_EN_L; //使能端恢复初始化
}

/*****************************
1602写数据函数
*****************************/
uchar LCD1602_ReadStatus()
{	  
      LCD1602_DATA=0xFF;
	  LCD1602_RS_L; //RS拉高选择写数据
	  LCD1602_RW_H; //使能端上升沿完成操作
	  LCD1602_Delayus() ;
	  LCD1602_EN_H;
	  LCD1602_EN_L; //使能端恢复初始化
	  LCD1602_Delayus() ;
	  while(LCD1602_DATA&0x80);
	  return(LCD1602_DATA);
}
/*****************************
1602写数据函数
*****************************/
uchar LCD1602_ReadData()
{	  
      
	  LCD1602_RS_H; //RS拉高选择写数据
	  LCD1602_RW_H; //使能端上升沿完成操作
	  LCD1602_Delayus() ;
	  LCD1602_EN_H;
	  LCD1602_EN_L; //使能端恢复初始化
	  LCD1602_Delayus() ;
	  return(LCD1602_DATA);
}
/*********************************
1602 液晶初始化函数
********************************/
void LCD1602_Init(uchar d,uchar c,uchar b)
{
	uchar temp_cmd;
	temp_cmd=0x08+d*4+c*2+b;
	LCD1602_EN_L;//拉低使能信号端
	LCD1602_Delayms();
	LCD1602_WriteCmd(0x38);//显示模式设置：设置16x2显示，5x7点阵，8位数据接口
	LCD1602_Delayms();
	LCD1602_WriteCmd(0x38);
	LCD1602_Delayms();
	LCD1602_WriteCmd(0x38);
	LCD1602_Delayms();
	LCD1602_WriteCmd(0x38);
	LCD1602_WriteCmd(temp_cmd);/*0 0 0 0 1 D C B 
	                  		D=1开显示、D=0关显示
			 		  		C=1显光标、C=0关光标
			 				B=1开闪烁、B=0关闪烁*/ 
	LCD1602_WriteCmd(0x06);//写一个字符后地址指针自动加1
	LCD1602_WriteCmd(0x01);//显示清屏

	
}
/********************************************************************
* 名称 : LCD1602_DisplayChar(uchar hang,uchar lie,char sign)
* 功能 : 改变液晶中某位的值，如果要让第一行，第五个字符显示"b" 
         调用该函数如LCD1602_DisplayCharI(1,5,b的ascii码)
		 或LCD1602_DisplayChar(1,5,'b')
* 输入 : 行列坐标和需要显示字符的ASCII码值
* 输出 : 无
***********************************************************************/
void LCD1602_DisplayChar(uchar hang,uchar lie,uchar ascii) 

{
	uchar temp_addr=0;
	if(hang == 1) temp_addr = 0x80;	//第一行开始地址
	if(hang == 2) temp_addr = 0xc0;	//第二行开始地址
	temp_addr = temp_addr + lie - 1;
	
	LCD1602_WriteCmd(temp_addr); //写入地址命令
    LCD1602_WriteData(ascii);	 //写入数据
}
/********************************************************************
* 名称 : LCD1602_DisplayString(uchar hang,uchar lie,uchar *sign)
* 功能 : 改变液晶中某位的值，如果要让第一行，第五个字符开始显示"ab cd ef" ，
         调用该函数如LCD1602_DisplayString(1,5,"ab cd ef;")
* 输入 : 行，列，需要输入1602的数据
* 输出 : 无
***********************************************************************/
void LCD1602_DisplayString(uchar hang,uchar lie,uchar *str)
{
	uchar temp_addr=0;
	if(hang == 1) temp_addr = 0x80;//第一行开始地址
	if(hang == 2) temp_addr = 0xc0;//第二行开始地址
	temp_addr = temp_addr + lie - 1;
	
	LCD1602_WriteCmd(temp_addr);	  //写入开始位地址
	while(1)
	{
		if(*str == '\0')break; //检测到空字符时跳出循环	
		LCD1602_WriteData(*str);//写入数据
		str++;				  //指针变量自加
	}
}
void LCD1602_PrintHZ(unsigned char sta,unsigned char *hz)
{
	unsigned char i,tempH,tempL,temp_addr;
	tempH=0;
	for(i=0;i<8;i++)
	{
	 tempH=hz[i*2]>>5;
	 tempL=hz[i*2]&0x1f;
	 LCD1602_WriteCmd(0x40+i);
	 LCD1602_WriteData(tempH);
	 LCD1602_WriteCmd(0x48+i);
	 LCD1602_WriteData(tempL);
	 tempH=hz[i*2+1]>>5;
	 tempL=hz[i*2+1]&0x1f;
	 LCD1602_WriteCmd(0x56+i);
	 LCD1602_WriteData(tempH);
	 LCD1602_WriteCmd(0x64+i);
	 LCD1602_WriteData(tempL);
	}
		for(i=8;i<16;i++)
	{
	 tempH=hz[i*2]>>5;
	 tempL=hz[i*2]&0x1f;
	 LCD1602_WriteCmd(0x72+i);
	 LCD1602_WriteData(tempH);
	 LCD1602_WriteCmd(0x80+i);
	 LCD1602_WriteData(tempL);
	 tempH=hz[i*2+1]>>5;
	 tempL=hz[i*2+1]&0x1f;
	 LCD1602_WriteCmd(0x88+i);
	 LCD1602_WriteData(tempH);
	 LCD1602_WriteCmd(0x92+i);
	 LCD1602_WriteData(tempL);
	}
	
     LCD1602_DisplayChar(1,sta,0x00);
     LCD1602_DisplayChar(1,sta+1,0x01); //固定位置 单引号内可以写任意的数字或字母
	 LCD1602_DisplayChar(1,sta+2,0x02);
	 LCD1602_DisplayChar(1,sta+3,0x03);
	 LCD1602_DisplayChar(2,sta,0x04);
     LCD1602_DisplayChar(2,sta+1,0x05); //固定位置 单引号内可以写任意的数字或字母
	 LCD1602_DisplayChar(2,sta+2,0x06);
	 LCD1602_DisplayChar(2,sta+3,0x07);

}

void LCD1602_DefineCGRAM(uchar *sign)
{
 uchar i,j,k,temp_addr;
 k=0;temp_addr=0x40;
 for(j=0;j<8;j++)
 {	for(i=0;i<8;i++)
	{
		LCD1602_WriteCmd(temp_addr+i);
		LCD1602_WriteData(sign[k]);
		k++;		
	}
	temp_addr=temp_addr+8;
 }

}

