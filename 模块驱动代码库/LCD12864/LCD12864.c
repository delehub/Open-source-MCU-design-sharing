/********************************************
*ɽ��������ѧ ��˼ʵ����                    *
*�������ƣ�LCD12864����                     *
*CPU�ͺţ�STC89C52                          *
*���������12MHZ                            *
*�������ߣ�2009��        ����             *
*��ϵ��ʽ��QQ��610949704                    *
*�ҵ��Ա���yy3q.taobao.com�������������    *
********************************************/
#include "LCD12864.h"

void Delay_40US(void)   
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=17;a>0;a--);
}
/**************************************
Ϊ�����߼���������õ������
�����������ռ����ȡʱ��İ취
***************************************/
code unsigned int LcdMaskTab[]=
{0x0001,0x0002,0x0004,0x0008,
 0x0010,0x0020,0x0040,0x0080,
 0x0100,0x0200,0x0400,0x0800,
 0x1000,0x2000,0x4000,0x8000};
/*************
����LCD�Ƿ���æ
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
��LCDд���ֽ�����
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
��LCD�ж�������
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
��LCD��д��ָ�����
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
 12864�趨��ʼ��ʾλ��
 XΪ�е���Ŀ
 YΪ�е���Ŀ
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
 ����ͼ����ʾģʽ
 select=0ʱ���ر�ͼ����ʾģʽ
 Select=1ʱ������ͼ����ʾģʽ
 LCD_EXTEND_FUNCTIONΪ ��չָ�
 LCD_GRAPH_ON	�򿪻�ͼģʽ����
 LCD_GRAPH_OFF	�رջ�ͼģʽ����
 ******************************************/
void LCD12864_SetMode(unsigned char Select)
{
	LCD12864_WriteCmd(LCD_EXTEND_FUNCTION);	   
	if(Select){LCD12864_WriteCmd(LCD_GRAPH_ON);} 
	else      {LCD12864_WriteCmd(LCD_GRAPH_OFF);}      
}
/*************************************
��LCDָ����ʼλ��д��һ���ַ���
*************************************/
void LCD12864_DisplayString(unsigned char x,unsigned char y,unsigned char *Str)
{	  
	if((y>4)||(x>8)) return;
	LCD12864_SetPoint(x,y);	
	while(*Str>0)
	{ LCD12864_WriteData(*Str); Str++;}
}
 /*******************************************
 ��ҳ��ʾ��ͬʱ��ʾ����
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
��LCDд��һ��8λ��ASCII��
����ʾ��Ӧ���ַ�
**********************************************/																		
void LCD12864_SendASCII(uchar hang,uchar lie,char sign) 
{

	LCD12864_SetPoint(hang,lie);		 
    LCD12864_WriteData(sign);	 
	 
}
/*********************************************
��LCDд��һ��16λ��GB2312��
����ʾ��Ӧ���ַ�
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
��LCDָ������д��һ������,������ɫ�����֣�
0����ף�����ʾ����1����ڣ�����ʾ��
****************************************/
void LCD12864_WritePixel(unsigned char x,unsigned char y,unsigned char color)
{

    unsigned char x_Dyte,y_Dyte,x_bite;				//�����е�ַ���ֽ�λ�������ֽ��е���1λ 
	unsigned char GDRAM_hbit,GDRAM_lbit;				//����Ϊ����������(ȡֵΪ0��1)���е�ַ(ȡֵΪ0~31)

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
���LCD��DRAM
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
���Lcdȫ����������ģʽModeΪ0����Ϊȫ�����Ϊ��ɫ0�����κ���ʾ��
����Ϊȫ�����Ϊ��ɫ1(ȫ�������ʾ)
******************************************/
void LCD12864_ClearGRAM(unsigned char Mode)
{
	unsigned char x,y,ii;
	unsigned char Temp;
	if(Mode%2==0)Temp=0x00;	
	else Temp=0xff;	
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x36);//����ָ�� ��ͼ��ʾ
	for(ii=0;ii<9;ii+=8)   
		for(y=0;y<0x20;y++)     
			for(x=0;x<8;x++)
			{ 	
				
				LCD12864_WriteCmd(y+0x80);        //�е�ַ
				LCD12864_WriteCmd(x+0x80+ii);     //�е�ַ     
				LCD12864_WriteData(Temp); //д���� D15��D8 
				LCD12864_WriteData(Temp); //д���� D7��D0 
			
			}

}
/**********************************************
���LCD�е�GRAM �� �ģң���
**********************************************/
void LCD12864_ClearGDRAM(void)
{
	 LCD12864_ClearDRAM();
	 LCD12864_ClearGRAM(0);
	
} 
/***********************************************************
��������  dispU_picture
����˵���� �ϰ�����ʾһ��128*32��ͼ��
���������ͼ��ָ��*img
������������
����ֵ��  ��
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
��������  dispD_picture
����˵���� �°�����ʾһ��128*32��ͼ��
���������ͼ��ָ��*img
������������
����ֵ��  ��
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
��������  disp_picture
����˵���� ��ʾһ��128*64��ͼ��
���������ͼ��ָ��*img
������������
����ֵ��  ��
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
��LCDָ�������ȡ������ɫֵ
*******************************************/
unsigned char LCD12864_ReadPixel(unsigned char x,unsigned char y)
{
	unsigned char z,w;
	unsigned int Temp;
	if(x>=128||y>=64) return 0;
	w=15-x%16;		 //ȷ��������ֵĵڶ���λ���в���
	x=x/16;          //ȷ��Ϊһ���ϵĵڼ���
	if(y<32)z=0x80;  //���Ϊ��ҳ	
	else z=0x88;     //�������Ϊ��ҳ
	y=y%32;	
	LCD12864_WriteCmd(0x36);
	LCD12864_WriteCmd(y+0x80);        //�е�ַ
	LCD12864_WriteCmd(x+z);           //�е�ַ 
	Temp=LCD12864_ReadData();                 //�ȿն�һ��
	Temp=(unsigned int)LCD12864_ReadData()<<8;//�ٶ�����8λ
	Temp|=(unsigned int)LCD12864_ReadData();  //�ٶ�����8λ
	if((Temp&&LcdMaskTab[w])==0)return 0;	
	else return 1;
		
}

/***************************************
��LCDָ��λ�û�һ������ΪLength��ָ����ɫ��ˮƽ��
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
��LCDָ��λ�û�һ������ΪLength��ָ����ɫ�Ĵ�ֱ��
****************************************/
void LCD12864_DrawLineV(unsigned char x,unsigned char y,unsigned char Length,unsigned char Color)
{
	unsigned char count;
	if(Length==0)	return;
	for(count=0;count<Length;count++)
	{LCD12864_WritePixel(x,y+count,Color);}	
}
/*******************************************
��LCDָ����ʼ����ͽ�������֮�仭һ��ָ����ɫ��ֱ��
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
��LCDָ�����Ͻ���������½����껭һ��ָ����ɫ�ľ���
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
�ԳƷ���Բ��8�������
*****************************************/
void LCD12864_DrawCircleDot(unsigned char x,unsigned char y,char xx,char yy,unsigned char Color)//�ڲ��������ԳƷ���Բ��8�������
{

	LCD12864_WritePixel((x+yy),(y+xx),Color);//�� 1 �� 8 ��Բ
	LCD12864_WritePixel((x+xx),(y+yy),Color);//�� 2 �� 8 ��Բ
	LCD12864_WritePixel((x-xx),(y+yy),Color);//�� 3 �� 8 ��Բ
	LCD12864_WritePixel((x-yy),(y+xx),Color);//�� 4 �� 8 ��Բ
	LCD12864_WritePixel((x-yy),(y-xx),Color);//�� 5 �� 8 ��Բ
	LCD12864_WritePixel((x-xx),(y-yy),Color);//�� 6 �� 8 ��Բ
	LCD12864_WritePixel((x+xx),(y-yy),Color);//�� 7 �� 8 ��Բ
	LCD12864_WritePixel((x+yy),(y-xx),Color);//�� 8 �� 8 ��Բ
	
}

/******************************************
��LCDָ��Բ�����껭һ���뾶Ϊr��ָ����ɫ��Բ
*******************************************/
void LCD12864_DrawCircle(unsigned char x,unsigned char y,unsigned char r,unsigned char Color)//�е㷨��Բ
{//�е㷨��Բ
	unsigned char xx,yy;
	char deltax,deltay,d;
	xx=0;
	yy=r;
	deltax=3;
	deltay=2-r-r;
	d=1-r;
	LCD12864_DrawCircleDot(x,y,xx,yy,Color);//�ԳƷ���Բ��8�������
	while (xx<yy)
	{
		if (d<0){ d+=deltax;deltax+=2;xx++;}
		else
		{ d+=deltax+deltay;	deltax+=2;deltay+=2;xx++;yy--;}
		LCD12864_DrawCircleDot(x,y,xx,yy,Color);//�ԳƷ���Բ��8�������
	}
}



/***************
0x01Ϊ����ģʽ
0x02Ϊ˯��ģʽ
0x0c����˯��
*******************/
void LCD12864_SetStatus(unsigned char cmd)
{  
	
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(cmd);

}
/****************************************
LCD��ʼ��
*****************************************/
void LCD12864_Init()
{   
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x34);
	LCD12864_WriteCmd(0x30);       //ѡ�����ָ�
	LCD12864_WriteCmd(0x0c);       //����ʾ(���αꡢ������)
	LCD12864_WriteCmd(0x01);       //�����ʾ�������趨��ַָ��Ϊ00H
	LCD12864_WriteCmd(0x06);       //ָ�������ϵĶ�ȡ��д��ʱ���趨�α���ƶ�����ָ����ʾ����λ
}


/*--����Ϊprotues����Һ����������--*/
/****************************************
LCD��ʼ��
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

 /*------------------------����ʾ��--------------------------------*/
void LCD12864_ClearScreen()
 {
  	unsigned char j,k;
  	LCD12864_CS2=1;
	LCD12864_CS1=0;             // ������� //
   {
    LCD12864_WriteCmd(Page_Add+0);
    LCD12864_WriteCmd(Col_Add+0);
    for(k=0;k<4;k++)               // �����ϰ��� //
     {
      for(j=0;j<64;j++)
	  LCD12864_WriteData(0x00);
     }
    for(k=0;k<4;k++)               // �����°��� //
     {
      LCD12864_WriteCmd(Page_Add+4);
      for(j=0;j<64;j++)
	  LCD12864_WriteData(0x00);
     }
   }
  	LCD12864_CS2=0;
	LCD12864_CS1=1;                    // ���Ұ��� //
   {
   	LCD12864_WriteCmd(Page_Add+0);
    LCD12864_WriteCmd(Col_Add+0);
    for(k=0;k<4;k++)               // �����ϰ��� //
     {
      for(j=0;j<64;j++)
	  LCD12864_WriteData(0x00);
     }
    for(k=0;k<4;k++)               // �����°��� //
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