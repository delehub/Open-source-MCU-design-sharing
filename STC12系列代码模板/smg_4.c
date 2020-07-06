#include"MAIN.H"
#include "SMG_4.H"

#define		N		12
//共阳数码管
sbit DIO = P1^0;				//串行数据输入
sbit RCLK  = P1^1;				//时钟脉冲信号——上升沿有效
sbit SCLK = P1^2;				//打入信号————上升沿有效

unsigned char code duancode[N] ={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
                   				//  0    1    2    3    4    5    6    7    
                     0x80,0x90,0xff,/*数码管不亮*/0x7f/*小数点*//*0x77,0x7C,0x39,0x5E,0x79,0x71*/};//0~F的段码
unsigned char code Duan_char[N]={'0','1','2','3','4','5','6','7','8','9',' ','.'/*,'a','b','c','d','e','f'*/};//
unsigned char code weicode[4]={0x01,0x02,0x04,0x08};

void LED_OUT(unsigned char X)
{
	unsigned char i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) DIO=1; else DIO=0;
		X<<=1;
		SCLK = 0;
		SCLK = 1;
	}
}
void smg(unsigned char i,unsigned char j)	   //i->位		j->段
{
	LED_OUT(duancode[j]);			
	LED_OUT(weicode[i]);		

	RCLK = 0;
	RCLK = 1;

	DELAY_nUS(100);

}

void smg_string(unsigned char k,unsigned char *string)//k位字符显示开始位，字符数不超过4
{
	unsigned char i=0;
	unsigned char j=sizeof(*string);
	while(*string)
	{
		for(i=0;i<N;i++)
		{
			if(*string==Duan_char[i])
			{
				smg(k,i);
				k--;
				break;
			}

		}
		string++;
	}
}
void smg_int(unsigned char k,unsigned int _NUMB)//k从第几位开始显示
{
	unsigned char i,j;
	
	unsigned char Numb_Arry[4];	//定义局部数组，用于存储变量

	Numb_Arry[0]=_NUMB/1000%10+0x30;
	Numb_Arry[1]=_NUMB/100 %10+0x30;
	Numb_Arry[2]=_NUMB/10  %10+0x30;
	Numb_Arry[3]=_NUMB/1   %10+0x30;
	for(i=0;i<4;i++)
	{
		if(Numb_Arry[i]==Duan_char[0])
		{
			
		}
		else
		{
			break;
		}
	}
	if(i==4)
	{
		smg(k,0);
	}
	else
	{
		for(;i<4;i++)
		{
			for(j=0;j<N;j++)							//循环32次，查询数码管字模位置
			{
				if(Duan_char[j]==Numb_Arry[i])	//判断第k个字符的编码是否与输入字符相等
				{
					smg(k,j);
					if(k==0)break;
					k--;
					
	
				}
			}
		}	
	}

}



void smg_float(unsigned char k,float numb) //k从第几位开始显示
{
	unsigned int temp,temp0=1;
	char i=0,flag=1,j=0;
	temp=(unsigned int)numb;
	smg_int(k,temp);
	if(temp>999){i=4;flag=0;j=i;}
	else if(temp>99)
	{
		i=3;
		j=i;
	}
	else if(temp>9)
	{
		i=2;
		j=i;
		for(i=3-i;i>0;i--)
			temp0*=10;

	}
	else 
	{
		i=1;
		j=i;
		for(i=3-i;i>0;i--)
			temp0*=10;
	}
	
	smg(k-j,11);
	if(flag==1)
	{
		temp=(numb-temp+0.005)*temp0;

		smg(k-j,11);
		smg_int(k-j-1,temp);
	}

}




