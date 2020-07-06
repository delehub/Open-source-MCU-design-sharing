																				  
/***************************************************************************************/
#include"MAIN.H"
#include"LCD12864.H"
 /***************************************************************************************************    
工程名称：	12864
功能描述：  实现12864液晶显示，液晶第一行显示"  北方蓝芯科技  "，第二行显示" www.hrbnbc.com "
                               
硬件连接：  将12864液晶接口对应插接到P2接口，注意1-20脚不要插反。
维护记录：  2011-8-22
***************************************************************************************************/

sbit RS=P2^5;    //命令/数据选择
sbit RW=P2^4;    //读写口
sbit  E=P2^3;    //锁存控制
sbit RES = P2^0; //复位
sbit PSB = P2^2; //串并选择
//**************************************************************************************************
//查忙
//**************************************************************************************************
void checkbusy(void)           
{
   RS=0;                   //命令/数据选择,为0时选择命令    
   RW=1;                   //读/写选择，为1时选择读
   E=1;                    //使能
   while((P0&0x80)==0x80); //查忙标志位，等待标志位为0，即表示写入完毕
   E=0;                    //关闭读写 
}
//**************************************************************************************************
//向LCD写一命令
//**************************************************************************************************
void wcode(unsigned char cmdcode)
{
   checkbusy();            //查忙
   RS=0;                   //命令/数据选择,为0时选择命令 
   RW=0;                   //读/写选择，为0时选择写
   E=1;                    //使能
   P0=cmdcode;             //送入命令
   delay(10);              //等待写入 
   E=0;                    //关闭读写
}
//**************************************************************************************************
//向LCD写一数据
//**************************************************************************************************
void wdata(unsigned char dispdata)
{
   checkbusy();            //查忙
   RS=1;                   //命令/数据选择,为1时选择数据
   RW=0;                   //读/写选择，为0时选择写
   E=1;                    //使能
   P0=dispdata;            //送入数据
   delay(10);              //等待写入 
   E=0;                    //关闭读写
}
//**************************************************************************************************
//LCD 初始化
//**************************************************************************************************
void InitLCD(void)
   {
   PSB=1;             //设置为8BIT并口工作模式
   RES=0;             //复位
   delay(10);         //延时
   RES=1;             //关复位 
   wcode(0x30);       //选择基本指令集
   wcode(0x0c);       //开显示(无游标、不反白)
   wcode(0x01);       //清除显示，并且设定地址指针为00H
   wcode(0x06);       //指定在资料的读取及写入时，设定游标的移动方向及指定显示的移位	
   }  
//**************************************************************************************************
//任意位置显示字符
//**************************************************************************************************
void Display_Char(unsigned char x,unsigned char y,unsigned char  Char)   
{                                     //x为横坐标，y位纵坐标，*s表示指针，为数据的首地址
 switch(y)                            //选择纵坐标            
     { 
	  case 0: wcode(0x80+x);break;    //第1行
	  case 1: wcode(0x90+x);break;    //第2行
	  case 2: wcode(0x88+x);break;    //第3行
	  case 3: wcode(0x98+x);break;    //第4行
      default:break;
	 }
	 wdata(Char);


}
//**************************************************************************************************
//任意位置显示字符串
//**************************************************************************************************
void Display_String(unsigned char x,unsigned char y,unsigned char  *s)   
{                                     //x为横坐标，y位纵坐标，*s表示指针，为数据的首地址
 switch(y)                            //选择纵坐标            
     { 
	  case 0: wcode(0x80+x);break;    //第1行
	  case 1: wcode(0x90+x);break;    //第2行
	  case 2: wcode(0x88+x);break;    //第3行
	  case 3: wcode(0x98+x);break;    //第4行
      default:break;
	 }
   while(*s>0)                        //写入数据，直到数据为空
     {  
      wdata(*s);                      //写数据
      delay(10);                      //等待写入
      s++;                            //下一字符
     }
}
//*********************************************************************************** 
//LCD12864显示整型数字(只显示5位数）
//*********************************************************************************** 
void Display_Int(unsigned char x,unsigned char y,int Number)
{
//    unsigned char NumbArray[6]={0};    // 定义局部数组，用于数据存储
//    if(Number<0)
//    {
//        Number=0-Number;
//        Display_String(x,y,"-");
//    }
//    else
//    {
//        Display_String(x,y,"+");
//    }
//    
//    NumbArray[0]=(Number/10000)%10+0x30; 
//    NumbArray[1]=(Number/1000) %10+0x30;
//    NumbArray[2]=(Number/100)  %10+0x30;
//    NumbArray[3]=(Number/10)   %10+0x30;
//    NumbArray[4]=(Number/1)    %10+0x30; 
//    NumbArray[5]= 0;
    unsigned char Array[3];
    Array[0]=(Number/10)   %10+0x30;
    Array[1]=(Number/1)    %10+0x30;
	Array[2]=0x00;    
    Display_String(x,y,Array);
}
//*********************************************************************************** 
//LCD12864显示浮点型数字(4位整数，3小数）
//***********************************************************************************
 void Display_Float(unsigned char X,unsigned char Y,float FloatNumber)
{
    unsigned char Number_Integer_Array[8]={0};          // 定义局部数组，用于存储整数位各位数据
//    unsigned char Number_Decimal_Array[3]={0};          // 定义局部数组，用于存储小数位各位数据

    unsigned int  Number_Integer = 0;             // 定义局部变量，表示浮点数的 整数部分
    unsigned int  Number_Decimal = 0;             // 定义局部变量，表示浮点数的 小数部分

    if(FloatNumber < 0)
    {
        FloatNumber= 0 - FloatNumber;
        Display_String(X,Y,"-");
    }
    else
    {
        Display_String(X,Y,"+");
    }

  
    Number_Integer = (unsigned int)(FloatNumber);                                         // 取整数部分
    Number_Decimal = (unsigned short)((FloatNumber - Number_Integer + 0.0005) * 1e3);     // 取小数部分，1e5科学计数法

        // 计算整数部分
    Number_Integer_Array[0] = Number_Integer/ 1000 % 10 + 0x30;
    Number_Integer_Array[1] = Number_Integer/  100 % 10 + 0x30;
    Number_Integer_Array[2] = Number_Integer/   10 % 10 + 0x30;
    Number_Integer_Array[3] = Number_Integer/    1 % 10 + 0x30;
	Number_Integer_Array[4] =0X2E;

    Number_Integer_Array[5] = Number_Decimal/  100 % 10 + 0x30;
    Number_Integer_Array[6] = Number_Decimal/   10 % 10 + 0x30;
    Number_Integer_Array[7] = Number_Decimal/    1 % 10 + 0x30;

    Display_String(X+1,Y,Number_Integer_Array);      // 显示整数位

}

