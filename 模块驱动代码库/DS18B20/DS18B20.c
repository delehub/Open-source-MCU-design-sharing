/********************************************
*ɽ��������ѧ ��˼ʵ����				    *
*�������ƣ�DS18B20����		     			*
*CPU�ͺ� ��STC89C52					        *
*���������12MHZ			    		    *
*�������ߣ�2009����е2�� ����				*
*��ϵ��ʽ��QQ��610949704				    *
*							                *
********************************************/
#include "DS18B20.h"
uchar TMPL,TMPH;
sbit DQ=P2^3;
#define DQ_L DQ=0
#define DQ_H DQ=1
/*-----------��ֵ��ʱ��������------------------*/
void DS18B20_Delay6us(void);
void DS18B20_Delay10us(void);
void DS18B20_Delay50us(void);
void DS18B20_Delay30us(void);
void DS18B20_Delay700us(void);
void DS18B20_Delay100us(void);
void DS18B20_Delayms(unsigned int z);
/*****************************
DS18B20��λ����
1�����������ߣ�������ʱ��
2�����������ͣ���ʱ480-960UM��
3������������
4����ʱ�ȴ���Ӧ
5�����������ٴ�����
*****************************/
uchar DS18B20_Reset()
{
     uchar x;
	 DQ_H ;                  //����������
	 DQ_L;		             //����������
     DS18B20_Delay700us();   //��ʱ480us-960us
	 DQ_H;					 //����������
	 DS18B20_Delay30us();    //��ʱ15us-60us
	 x=DQ;					 //��ȡ��ʱ�����ߵ�ֵ
 	 while(!DQ);             //ֱ��DQΪ��
     return x;	             //���ظ�λ���
}
/***************************
18B20��һλ���ݺ���
1�������������ߣ���ʱ2΢�
2�������������ͣ���ʱ6΢�
3�������������ߣ���ʱ4΢�
4����������״̬����һ��״̬λ
5����ʱ50΢��
***************************/
uchar DS18B20_ReadBit()
{	bit x ;
	uchar i; 
	DQ_H;		 		//����������
	i++;         		//��ʱ2΢��
    DQ_L;        		//����������
	DS18B20_Delay6us(); //��ʱ6΢�� 
	DQ_H; 		 		//����������
	i++;i++;	 		//��ʱ4΢��
	x=DQ;		 		//��������״̬
	DS18B20_Delay50us();//��ʱ50΢��
	return (x); 		//������ֵ

}
/***********************************
DS18B20дһλ����
1��������������
2����ʱ����1΢�루����дƬ�εļ�϶��
3�������������ͣ���ʼдʱ��	��
4����ʱ����1΢�루дʱ��ĵ͵�ƽ��ʱ����1΢�룩
5��д������ 15΢���ʼ�ɼ�
6����ʱʹд������60-120΢��
***********************************/
void DS18B20_WriteBit(uchar Bit)
{	  uchar i;
	  DQ_H;	         		//������������
	  i++;	         		//��ʱ����1΢��
	  DQ_L;          		//������������
	  i++;	         		//��ʱ����1΢��
	  DQ=Bit;         		//д������
	  DS18B20_Delay100us();	//��ʱʹд������60-120΢��֮��
	  DQ_H;
}
/************************************
DS18B20��һ���ֽں���
************************************/
uchar DS18B20_ReadByte()
{
	uchar i,j,dat;
    dat=0;
    j=1;
	for(i=0;i<8;i++)
	{
		if(DS18B20_ReadBit())
		{
			dat=dat+(j<<i);
		}
	}
	return (dat);
}
/********************************
DS18B20дһ���ֽں���
********************************/
void DS18B20_WriteByte(uchar dat)
{
	uint temp;
	uchar j;
	for(j=0;j<8;j++)
	{	 	
	    temp=dat>>j;
		temp=temp&0x01;
		DS18B20_WriteBit(temp) ;
	}	
	
}
/****************************
DS18B20�����緽ʽ
****************************/
bit DS18B20_PowerMode()
{	
   	bit x;
	while(DS18B20_Reset());  //��λ��ͨ��ǰ���븴λ
	DS18B20_WriteByte(0xcc);
	DS18B20_WriteByte(0xb4); //�����緽ʽ����
    x=DQ;
	DS18B20_Delay10us();
	return x; 
}
/******************************
DS18B20 �������ú���
*****************************/
void DS18B20_SetResolution(unsigned char res)
{ 
    switch (res)
	{
	     case  9:res=0;
		 break; 
		 case 10:res=1;
		 break; 
		 case 11:res=2;
		 break;
		 case 12:res=3;
		 break;  
	}
 DS18B20_Reset();              //��λ��ͨ��ǰ���븴λ
 DS18B20_WriteByte(0x4e);             //д�ݴ���ָ��
 DS18B20_WriteByte(0xff);             //��ֵ��д��TH
 DS18B20_WriteByte(0xff);             //��ֵ��д��TL
 DS18B20_WriteByte(0x1f|(res<<5));    //���þ���  0 res[1-0] 11111
}
/*****************************
DS18B20�¶ȶ�ȡ����
*****************************/
long DS18B20_GetTemperature()
{ 	 long wendu;
     DS18B20_Reset();
	 DS18B20_WriteByte(0xcc);//����ROM
	 DS18B20_WriteByte(0x44);//�¶�ת��
	 DS18B20_Delayms(560);	 //��Ҫ100-750����ת��ʱ��
	 DS18B20_Reset();
	 DS18B20_WriteByte(0xcc);//����ROM
	 DS18B20_WriteByte(0xbe);//���ݴ���
	 TMPL=DS18B20_ReadByte();
	 TMPH=DS18B20_ReadByte();
	 wendu=TMPH<<8|TMPL;
	 wendu=wendu>>4;		//��λ�������
	 return wendu;
}
/*****************************************
ƥ��ROM����
*****************************************/
uchar DS18B20_MatchRom(uchar *rom)
{
	uchar i;
	DS18B20_Reset();
	DS18B20_WriteByte(0x55);
	for(i=0;i<8;i++)
	{
	    
		DS18B20_WriteByte(*rom);
		rom++;
	}
	return 1;
}
 void DS18B20_GetRom(unsigned char *ROM)
 {
  	unsigned char i=0;
    DS18B20_Reset();
	DS18B20_WriteByte(0x33);

	ROM[0]=DS18B20_ReadByte();
	ROM[1]=DS18B20_ReadByte();
	ROM[2]=DS18B20_ReadByte();
	ROM[3]=DS18B20_ReadByte();
	ROM[4]=DS18B20_ReadByte();
	ROM[5]=DS18B20_ReadByte();
	ROM[6]=DS18B20_ReadByte();
	ROM[7]=DS18B20_ReadByte();
}

long DS18B20_ReadTemperature(unsigned char *Rom)
{	long wendu;
 	DS18B20_MatchRom(Rom);
 	DS18B20_WriteByte(0xbe);//���ݴ�������
	TMPL=DS18B20_ReadByte();
	TMPH=DS18B20_ReadByte();
	wendu=TMPH<<8|TMPL;
	wendu=wendu>>4;		//��λ�������
	return wendu;
}
/**********DS18B20ר�ö�ֵ��ʱ����****************/
void DS18B20_Delay6us(void)   //��� -0.574652777778us
{
    unsigned char a;
    for(a=1;a>0;a--);
}
void DS18B20_Delay10us(void)   //��� -0.234375us
{
    unsigned char a;
    for(a=3;a>0;a--);
}
void DS18B20_Delay30us(void)   //��� -0.703125us
{
    unsigned char a;
    for(a=12;a>0;a--);
}
void DS18B20_Delay50us(void)   //��� -0.086805555556us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=20;a>0;a--);
}
void DS18B20_Delay100us(void)   //��� -0.173611111111us
{
    unsigned char a,b;
    for(b=1;b>0;b--)
        for(a=43;a>0;a--);
}
void DS18B20_Delay700us(void)   //��� -0.130208333333us
{
    unsigned char a,b;
    for(b=6;b>0;b--)
        for(a=52;a>0;a--);
}
void DS18B20_Delayms(unsigned int z)
	{
	    unsigned int i,j;
		for(i=z;i>0;i--)
		  for(j=114;j>0;j--);
    }