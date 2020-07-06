

#include "lcd12864.h"	 
#include "delay.h"	

void LCD12864_GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA, ENABLE);
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/****************************************************************
                     �������ݴ���
****************************************************************/
void  SandByte(u8 bye)
{
  u8  t;
  for(t=8;t>0;t--)
  {
	SCLK_Clr();
	if(bye & 0x80) SID_Set();
		     else  SID_Clr();
	bye=bye<<1;
    delay_us(2);
    SCLK_Set();
  }
}
/****************************************************************
                     дָ���
****************************************************************/
void write_com(u8 com)
{
  CS_Set();
  SandByte(0xf8);
  delay_us(10);
  SandByte(com&0xf0);
  delay_us(10);
  SandByte(com << 4);
  delay_us(10);
  CS_Clr();
}
/****************************************************************
                     д���ݺ���
****************************************************************/
void write_data(u8 data)
{
  CS_Set();
  SandByte(0xfa);
  delay_us(10);
  SandByte(data&0xf0);
  delay_us(10);
  SandByte(data << 4);
  delay_us(10);
  CS_Clr();
}
/****************************************************************
                     ��x��y��д����
****************************************************************/
void   lcd_pos(u8 y,u8 x) // x:0~3;y:0~7
{
  switch(y)
  {
    case 0: write_com(0x80+x);break;
	case 1: write_com(0x90+x);break;
    case 2: write_com(0x88+x);break;
	case 3: write_com(0x98+x);break;
  }
}
/****************************************************************
                     д���ֺ��� 
****************************************************************/
void  write_hz(const u8 *str)
{
  while(*str>0)
  {
    write_data(*str);
	str++;
  }
}
/****************************************************************
                     ��ͼ����  ���У�˳��8*16
****************************************************************/
void drawpic(const u8 *p)
{
  u8 i, j ;
  write_com(0x36);
  delay_ms(2);
  write_com(0x36);
  delay_ms(2);
  write_com(0x3e);
  delay_ms(2);
  write_com(0x01);
	
  for(i=0;i<32;i++)  //���ϰ���
  {
	write_com(0x80+i);
	write_com(0x80);
	for(j=0;j<16;j++)
	{
	  write_data(*p++);
	}
  }
	
  for(i=0;i<32;i++)  //���°���
  {
	write_com(0x80+i);
	write_com(0x88);
	for(j=0;j<16;j++)
	{
	  write_data(*p++);
	}
  }
}
/****************************************************************
                     ��ʼ�� LCM
****************************************************************/
void LCD12864_Init(void)
{
  write_com(0x30);  //�����趨��8λ�ӿڿ���λ������ָ�
  delay_us(5);
  write_com(0x0c);  //��ʾ�������ã�������ʾ�����α���ʾ�أ�������ʾ
  delay_us(5);
  write_com(0x01);  //�����ʾ 
  delay_us(5);
}




















