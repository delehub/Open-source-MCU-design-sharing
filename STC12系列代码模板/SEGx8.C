#include"MAIN.H"
#include"SEGx8.H"

sbit LE1=P2^0;
sbit LE2=P2^1;
            // 最终显示的段码内容
unsigned char ShowData[8]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
unsigned char code WeiCode[8] ={0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};


//  SEGx8 段码 
code struct SEGx8_CODE                      // 结构体名 SEGx8_CODE
{
       unsigned char CHAR;                  // 编码
       unsigned char CODE;                  // 编码内容 
} SEGx8_CODE[] =                            // 数据表 
{	  
	'0',0x3F,		//0的编码方式
	'1',0x06,		//1的编码方式
	'2',0x5B,		//2的编码方式
	'3',0x4F,		//3的编码方式
	'4',0x66,		//4的编码方式
	
	'5',0x6D,		//5的编码方式
	'6',0x7D,		//6的编码方式
	'7',0x07,		//7的编码方式
	'8',0x7F,		//8的编码方式
	'9',0x6F,		//9的编码方式	

	' ',0x00,		// 的编码方式
    
    'q',0x67,                       // q的编码方式
    'd',0x5E,                       // d的编码方式
    'c',0x58,                       // c的编码方式

    'H',0x76,                       // H的编码方式
    'L',0x38,                       // L的编码方式
    'P',0x73                        // P的编码方式
    
 
};

// Wei 指的是 位置 0~7
// Duan 指的是 具体段码
void SEGx8_Show(unsigned char Wei)
{
    if(Wei>7) Wei=7;
    


	P1=0x00;  // 消影 
    LE2=1;             
    LE2=0;           
    
    // 写位码操作
    P1=WeiCode[Wei];    // 0x00=0000 0000,即选通数码管的全部8位 
    LE1=1;              // 锁存位 
    LE1=0;              // 断开锁存,位选573的Q7~Q0仍为0x00
    // 写段码操作
    P1=ShowData[Wei];  // 0x79为"E"的编码 
    LE2=1;              // 锁存段码 
    LE2=0;              // 断开锁存,段选573的Q7~Q0仍为0x79
    
 
}

void SEGx8_ShowString(unsigned char X,unsigned char *String)
{
    unsigned char i;
    while(*String)
    {
        for(i=0;i<sizeof(SEGx8_CODE)/2;i++)
        {
            if(*String == SEGx8_CODE[i].CHAR)
            {
                ShowData[X]= SEGx8_CODE[i].CODE;
                break;
            }
        }
        String++;
        X++;
    }
}
void SEGx8_ShowIntNumber(int Number)
{
    unsigned char NumbArray[6]={0};    // 定义局部数组，用于数据存储
    if(Number<0)
    {
        Number=0-Number;
        ShowData[0]=0x40;  //-
    }
    else
    {
        ShowData[0]=0x00;
    }
    NumbArray[0]=(Number/10000) %10+0x30; 
    NumbArray[1]=(Number/1000) %10+0x30;
    NumbArray[2]=(Number/100)  %10+0x30;
    NumbArray[3]=(Number/10)   %10+0x30;
    NumbArray[4]=(Number/1)    %10+0x30; 
    NumbArray[5]= 0;     
    SEGx8_ShowString(1,NumbArray);
}
  
  
void SEGx8_ShowFloatNumber(float Number)
{
    unsigned char NumberArray[11]={0};              // 定义局部数组，用于数据存储
    unsigned char i=1;                              // 定义局部变量，记录整数位数
    long j=1;
    unsigned int Real_Int=0;                        // 定义局部变量，记录整数部分
    unsigned int Real_Dec=0;                        // 定义局部变量，记录小数部分

    double Deci=0;                                  // 定义局部数组，暂存小数数值
    
    //----------------------------------------------------------------------------------------------
    // 判断 浮点数字正负
    //----------------------------------------------------------------------------------------------
    if(Number<0)
    {
        Number=0-Number;
        ShowData[0]=0x40;
		ShowData[7]=0x58;
    }
    else
    {
        ShowData[0]=0x00;
		ShowData[7]=0x58;
    }

    //----------------------------------------------------------------------------------------------
    // 分离 整数位与小数位
    //----------------------------------------------------------------------------------------------
    Real_Int=(int)Number;                           // 取整数部分
    Deci    =Number-Real_Int;                       // 取小数部分
    Real_Dec=(unsigned int)(Deci*1e4);              // 小数变整型数字，1e4科学计数法


    //----------------------------------------------------------------------------------------------
    // 串口输出
    //----------------------------------------------------------------------------------------------
   
    NumberArray[0] = (Real_Int/100)  %10+0x30;
    NumberArray[1] = (Real_Int/10)   %10+0x30;
    NumberArray[2] = ( Real_Int/1)   %10+0x30;             
    NumberArray[3] = (Real_Dec/1000)%10+0x30;
    NumberArray[4] = (Real_Dec/100) %10+0x30;
    NumberArray[5] = (Real_Dec/10)  %10+0x30;
    SEGx8_ShowString(1,NumberArray);
	ShowData[3]=SEGx8_CODE[(Real_Int/1) %10].CODE  |0x80;
}

