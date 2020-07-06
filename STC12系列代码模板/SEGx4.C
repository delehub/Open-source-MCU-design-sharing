#include "MAIN.H"
#include "SEGx4.H"
#include "DELAY.H"

unsigned char CODE_1[12]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,
                   		//  0    1    2    3    4    5    6    7    
                     0x80,0x90,0xff,/*数码管不亮*/0x7f/*小数点*//*0x77,0x7C,0x39,0x5E,0x79,0x71*/};//0~F的段码
//  SEGx4 段码 结构体···········································
code struct SEGx4_CODE                      // 结构体名 SEGx4_CODE
{
       unsigned char CHAR;                   // 编码
       unsigned char CODE;                  // 编码段
       unsigned char WWEI;                  // 编码位	    
}
SEGx4_CODE[] =                            // 数据表 
{	
	'0',0xC0,0x00,		//0的编码方式
	'1',0xF9,0x08,		//1的编码方式
	'2',0xA4,0x04,		//2的编码方式
	'3',0xB0,0x02,		//3的编码方式
	'4',0x99,0x01,		//4的编码方式
	
	'5',0x92,0x00,		//5的编码方式
	'6',0x82,0x00,		//6的编码方式
	'7',0xF8,0x00,		//7的编码方式
	'8',0x80,0x00,		//8的编码方式
	'9',0x90,0x00,		//9的编码方式
		
	'.',0x7f,0x00,		//.的编码方式  
	' ',0x00,0x00,		// 的编码方式
	'-',0xBF,0x00,		// 的编码方式
    
    'A',0x88,0x00,       //A的编码方式
    'b',0xB3,0x00,       //b的编码方式
    'C',0xc6,0x00,       //C的编码方式
        
    'd',0xA1,0x00,       //d的编码方式
    'E',0x86,0x00,       //E的编码方式
    'F',0xFF,0x00        //F的编码方式 
};
unsigned char Wang_1[17]={'0','1','2','3','4','5','6','7','8','9','A','b','C','d','E','F','-'};

sbit DIO = P0^0;				//串行数据输入
sbit RCLK  = P0^1;				//时钟脉冲信号——上升沿有效
sbit SCLK = P0^2;				//打入信号————上升沿有效

void LED_OUT(unsigned char X)
{
	unsigned char i;
	for(i=8;i>=1;i--)
	{
		if (X&0x80) DIO=1; else DIO=0;	  //串行发送，检查每一位是为1还是0，低电平点亮
		X<<=1;							  //左移到下一位，
		SCLK = 0;	   
		SCLK = 1;
	}									  //循环结束后，相当于DIO【8】 =  X
}

//指定位置显示字符································
void SEGx4_ShowChar(unsigned char X,unsigned char Char)
{
    unsigned char i;
	unsigned char duan;
        for(i=0;i<sizeof(SEGx4_CODE)/2;i++)
        {
            if(Char == SEGx4_CODE[i].CHAR)
            {
				duan = SEGx4_CODE[i].CODE;				
                break;
            }
        }
		//SEGx4_Show(X,i);
		LED_OUT(duan);
		LED_OUT(SEGx4_CODE[X].WWEI);
		RCLK = 0;
		RCLK = 1;
		delay_nUS(2);
}
//清屏函数·······················································
void SEGx4_Clear(void)
{
    unsigned char i;									
    for(i=1; i<5; i++)
    {
        LED_OUT(0x00);
		LED_OUT(SEGx4_CODE[i].WWEI);
		RCLK = 0;
		RCLK = 1;
		delay_nUS(2);
    }
}

//指定位置显示字符串································
void SEGx4_ShowString(unsigned char X,unsigned char *String)
{
    unsigned char i;
	unsigned char duan;
	while(*String)
    {
        for(i=0;i<sizeof(SEGx4_CODE)/2;i++)
        {
            if(*String == SEGx4_CODE[i].CHAR)
            {
				duan = SEGx4_CODE[i].CODE;				
                break;
            }
        }
		//SEGx4_Show(X,i);
	   	LED_OUT(duan);
		LED_OUT(SEGx4_CODE[X].WWEI);
		RCLK = 0;
		RCLK = 1;
		delay_nUS(2);
//		//delay_nMS(20);
		String++;
        X++;
   }
}
//指定位置显示整数································
void SEGx4_Show_intnumber(unsigned char X,unsigned int Number)
{
	unsigned char i,j,duan;
	unsigned char num_2[4];
    num_2[0]=(Number/1000%10)+0x30;
    num_2[1]=(Number/100)  %10+0x30;
    num_2[2]=(Number/10)   %10+0x30;
    num_2[3]=(Number/1)    %10+0x30; 
				 
	for(i=0;i<4;i++)
	{
		if(num_2[i]==Wang_1[0])
		{
			
		}
		else
		{
			break;
		}
	}
	//SEGx4_ShowString(X,&num_2[i]);
	for(;i<4;i++)
	{
	 for(j=0;j<sizeof(SEGx4_CODE)/2;j++)
        {
            if(num_2[i] == SEGx4_CODE[j].CHAR)
            {
				duan = SEGx4_CODE[j].CODE;				
                break;
            }
        }
	 	LED_OUT(duan);
		LED_OUT(SEGx4_CODE[X].WWEI);
		RCLK = 0;
		RCLK = 1;
		delay_nUS(2);
		X++;
	}
}

void SEGx4_float(unsigned char k,float numb) //k从第几位开始显示
{
	unsigned int temp;
	temp=(unsigned int)numb;
	
	if(temp>999){SEGx4_Show_intnumber(k,temp);}
	else if(temp>99)
	{
		SEGx4_Show_intnumber(k,temp);
		LED_OUT(0x7f);
		LED_OUT(SEGx4_CODE[k+3].WWEI);
		RCLK = 0;
		RCLK = 1;
		delay_nUS(2);
		
	}
	else if(temp>9)
	{
		
		SEGx4_Show_intnumber(k,temp);
		LED_OUT(0x7f);
		LED_OUT(SEGx4_CODE[k+2].WWEI);
		RCLK = 0;
		RCLK = 1;
		delay_nUS(2);

		LED_OUT(CODE_1[((int)(numb*10))%10]);
		LED_OUT(SEGx4_CODE[k+3].WWEI);
		RCLK = 0;
		RCLK = 1;
		delay_nUS(2);
	}
	else if(temp>0) 
	{
		SEGx4_Show_intnumber(k,temp);
		LED_OUT(0x7f);
		LED_OUT(SEGx4_CODE[k+1].WWEI);
		RCLK = 0;
		RCLK = 1;
		delay_nUS(2);

		LED_OUT(CODE_1[((int)(numb*10))%10]);
		LED_OUT(SEGx4_CODE[k+2].WWEI);
		RCLK = 0;
		RCLK = 1;
		delay_nUS(2);
		
		LED_OUT(CODE_1[((int)(numb*100))%10]);
		LED_OUT(SEGx4_CODE[k+3].WWEI);
		RCLK = 0;
		RCLK = 1;
		delay_nUS(2);
	}
	else
	{
	  	SEGx4_Show_intnumber(k,temp);
	  	LED_OUT(0x7f);
		LED_OUT(SEGx4_CODE[k+1].WWEI);
		RCLK = 0;
		RCLK = 1;
		delay_nUS(2);

		LED_OUT(CODE_1[((int)(numb*10))%10]);
		LED_OUT(SEGx4_CODE[k+2].WWEI);
		RCLK = 0;
		RCLK = 1;
		delay_nUS(2);
		
		LED_OUT(CODE_1[((int)(numb*100))%10]);
		LED_OUT(SEGx4_CODE[k+3].WWEI);
		RCLK = 0;
		RCLK = 1;
		delay_nUS(2);
	}
}






