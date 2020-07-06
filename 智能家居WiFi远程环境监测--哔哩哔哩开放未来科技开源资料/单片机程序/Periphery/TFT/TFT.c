#include "TFT.h"
#include "Ascii_8x16.h"                  //8x16��С�ַ�
#include "Chinese.h"                     //16x16���ش�С�ĺ���
/**********************************
***********************************
��������д��   ���ߣ��¿���
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
д����8λ����    ���ߣ��¿���
***********************************
**********************************/
void TFT_WR_DATA8(uchar date) 
{	
	  GPIO_SetBits(TFT_GPIO,TFT_DC);
	  TFT_Writ_Bus(date);
}
/**********************************
***********************************
д����//16λ����    ���ߣ��¿���
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
д����     ���ߣ��¿���
***********************************
**********************************/
void TFT_WR_REG(uchar date)  	 
{
  GPIO_ResetBits(TFT_GPIO,TFT_DC);
	TFT_Writ_Bus(date);
}

/**********************************
***********************************
д�����д����    ���ߣ��¿���
***********************************
**********************************/
void TFT_WR_REG_DATA(uint reg,uint date) 
{
  TFT_WR_REG(reg);
	TFT_WR_DATA(date);
}

/**********************************
***********************************
������ʼ��ַx1,y1����ֹ��ַx2,y2  
���ߣ��¿���
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
��������Color:Ҫ���������ɫ
���ߣ��¿���
ע������240X320
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
//	ʵ�ֹ��ܣ�	��ʾAscii�ַ�
//  ���������  x ������
//              y ������
//		        c ��Ҫ��ʾ���ַ�
//		        fColor �ַ���ɫ
//		        bColor �ַ�������ɫ
****************************************************************************************************/
void TFT_PutChar(unsigned int x, unsigned int y, char c, unsigned int fColor, unsigned int bColor)
{
 unsigned int i,j;
	
 Address_set(x,y,x+16-1,y+8-1);                    //�����ַ���ʾλ��
 	
 for(i=0; i<16;i++) 
 {                             //ѭ��д��16�ֽڣ�һ���ַ�Ϊ16�ֽ�
		unsigned char m=Font8x16[(c-0x20)*16+i];  //��ȡc�ַ��ĵ�i���ֽ���,c��ȥ0x20������Ascii����е�0~1f��ȥ��
		for(j=0;j<8;j++) 
		{                        //ѭ��д��8λ��һ���ֽ�Ϊ8λ
			if((m&0x80)==0x80)    //�ж����λ�Ƿ�Ϊ1
			{ 
        TFT_WR_DATA(fColor);				//���λΪ1��д���ַ���ɫ      
			}
			else 
			{
				TFT_WR_DATA(bColor);           //���λΪ0��д�뱳����ɫ
			}
			m<<=1;                                //����1λ��׼��д��һλ
		}
	}
}


/****************************************************************************************************
//	ʵ�ֹ��ܣ�	��ʾ16x16����
//  ��������� x ������
//            y ������
//		        g ��Ҫ��ʾ���ַ�����
//		        fColor �ַ���ɫ
//		        bColor �ַ�������ɫ
****************************************************************************************************/

void TFT_Put16x16(unsigned short x, unsigned short  y, unsigned char g[2], unsigned int fColor,unsigned int bColor)
{
	unsigned int i,j,k;
	
	Address_set(x,y,x+16-1,y+16-1);                       //���ú�����ʾλ��

	for (k=0;k<64;k++)                                      //ѭ��64�Σ���ѯ������ģλ��
	{ 
	  if ((ch16[k].GBK[0]==g[0])&&(ch16[k].GBK[1]==g[1]))   //�жϵ�k�����ֵı����Ƿ������뺺��g[2]���
	  { 
    	for(i=0;i<32;i++)                                   //�����ȣ������ҵ�����ʾ��ģλ�ã�ѭ��д��32�ֽ�
		  {
		    unsigned short m=ch16[k].hz16[i];                 	//��ȡ32�ֽ��еĵ�i�ֽ�
		    for(j=0;j<8;j++)                                  	//ѭ��д��8λ����
		    {                                                
			   if((m&0x80)==0x80)
					 TFT_WR_DATA(fColor);     		//�ж����λ�Ƿ�Ϊ1,���λΪ1��д���ַ���ɫ
			   else             
					 TFT_WR_DATA(bColor);      		//���λΪ0��д�뱳����ɫ
		     m<<=1;                                         	//����1λ��׼��д��һλ
	     } 
		  }
      break;			
	  }  
  }
}


/****************************************************************************************************
//	ʵ�ֹ��ܣ�	��ʾ��Ӣ���ַ���
//  ��������� x ������
//            y ������
//		        *s ����ʾ���ַ���,����LCD_PutString(24,16,"123Eee",White,Blue);����"123Eee"�ĵ�һ���ַ���ַ����ָ�����s.
//		        bColor �ַ�������ɫ
****************************************************************************************************/
void TFT_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor) 
{
	 unsigned char l=0;                            	//��ʾ��λ������
	
   while(*s) 
	 {
		if( *s < 0x80)                             		//�ж�sָ����ַ����е�ĳ�ַ��ı���ֵ�Ƿ�С��128,���С��,��ΪASCII�ַ�
		{
			TFT_PutChar(x,y+l*8,*s,fColor,bColor);			//��ʾ���ַ�
		  s++;l++;                              		//ָ���1,λ�ü�1
		}
		else
		{
			TFT_Put16x16(x,y+l*8,(unsigned char*)s,fColor,bColor);		//��ʾ�ú���
		  s+=2;l+=2;                                        	//��Ϊ����Ϊ����Ϊ2�ֽڣ�ָ���2,��ʾ16x16����λ�ü�2
	  }
	 }
}

/**********************************
***********************************
����     ���ߣ��¿���
ע:POINT_COLORΪ�˵����ɫ
***********************************
**********************************/
void TFT_DrawPoint(uint x,uint y,uint POINT_COLOR)
{
	Address_set(x,y,x,y);//���ù��λ�� 
	TFT_WR_DATA(POINT_COLOR); 	    
} 

/**********************************
***********************************
�����     ���ߣ��¿���
ע:POINT_COLORΪ�˵����ɫ
***********************************
**********************************/
void TFT_DrawPoint_big(uint x,uint y,uint POINT_COLOR)
{
	TFT_Fill(x-1,y-1,x+1,y+1,POINT_COLOR);
}


/**********************************
***********************************
��ָ�����������ָ����ɫ
���ߣ��¿���
ע:�����С(xend-xsta)*(yend-ysta)
***********************************
**********************************/
void TFT_Fill(uint xsta,uint ysta,uint xend,uint yend,uint color)
{          
	uint i,j; 
	Address_set(xsta,ysta,xend,yend);      //���ù��λ�� 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)TFT_WR_DATA(color);//���ù��λ�� 	    
	} 					  	    
} 
 
 

/**********************************
***********************************
����      ���ߣ��¿���
***********************************
**********************************/
void TFT_DrawLine(uint x1, uint y1, uint x2, uint y2,uint POINT_COLOR)
 {
	uint t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		TFT_DrawPoint(uRow,uCol,POINT_COLOR);//���� 
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
��ָ��λ�û�һ��ָ����С��Բ
���ߣ��¿���
ע��(x,y):���ĵ�
     r:�뾶
***********************************
**********************************/
void Draw_Circle(uint x0,uint y0,uchar r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
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
		//ʹ��Bresenham�㷨��Բ     
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
��ָ��λ����ʾͼƬ  ���ߣ��¿���
ע��image[]��Ӧdata.c
    iͼƬ�����С
***********************************
**********************************/
void showimage(uchar image[],uint i,uint xs,uint ys,uint xe,uint ye) //��ʾͼƬ
{
	uint index;
	Address_set(xs,ys,xe-1,ye-1);		//��������
	for(index=0;index<i/2;index++)
	{	
			
		TFT_WR_DATA8(image[index*2+1]);	 //������ɫ����
		TFT_WR_DATA8(image[index*2]);					
		
	}
}
 
//��ʼ��lcd
void TFT_Init(void)
{ 

 	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA, ENABLE );//PORTAʱ��ʹ�� 
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOC, ENABLE );//PORTAʱ��ʹ�� 
 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_7 ;	  //Pin_5 sck  pin7 MOSI
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //PA5/7/����������� 
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
	GPIO_ResetBits(TFT_GPIO,TFT_CS);  //��Ƭѡʹ��

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
 



