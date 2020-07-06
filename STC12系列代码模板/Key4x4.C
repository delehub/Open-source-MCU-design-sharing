																				  
/***************************************************************************************/




#include"MAIN.H"
#include"Key4x4.H"
#define GPIO_KEY  P1

//**************************************************************************************************
//矩阵键盘扫描函数
//**************************************************************************************************
unsigned char keyScan(void)  
{
  unsigned char KeyValue;
  unsigned char x,y; 
  GPIO_KEY=0xf0;                              //P0赋值0xf0
  if((GPIO_KEY&0xf0)!=0xf0)                   //判断高4位是否为全1（高4位全1代表没按键按下）

    {
        DELAY_nMS(7);                      //延时去抖动，一般为5ms～10ms（由于机械触点的弹性作用，按键在闭合时不会马上稳定地接通，
	                                    //而在闭合瞬间伴随有一连串的抖动，键抖动会引起一次按键被误读多次）
      if((GPIO_KEY&0xf0)!=0xf0)               //如果还能检测到有键盘按下去 
        {
		  x=GPIO_KEY&0xf0;                    //读取P0口数据
          GPIO_KEY=0x0f;                      //反转，P0赋值0x0f             
          y=GPIO_KEY&0x0f;                    //读取P0口数据
          KeyValue=x|y;                 //得到扫描结果
        }
    }
  return KeyValue;
}                           
//**************************************************************************************************
//矩阵键盘扫描结果处理函数
//**************************************************************************************************
unsigned char GetKey4x4_Value(void)                     
{
  switch(keyScan())
  {
   case 0xee:{return(0);break;}	   //对应按键S1
   case 0xde:{return(1);break;}	   //对应按键S2	
   case 0xbe:{return(2);break;}	   //对应按键S3	
   case 0x7e:{return(3);break;}	   //对应按键S4	
   case 0xed:{return(4);break;}	   //对应按键S5	
   case 0xdd:{return(5);break;}	   //对应按键S6	
   case 0xbd:{return(6);break;}	   //对应按键S7	
   case 0x7d:{return(7);break;}	   //对应按键S8	
   case 0xeb:{return(8);break;}	   //对应按键S9	
   case 0xdb:{return(9);break;}	   //对应按键S10	
   case 0xbb:{return(10);break;}   //对应按键S11	
   case 0x7b:{return(11);break;}   //对应按键S12
   case 0xe7:{return(12);break;}   //对应按键S13	
   case 0xd7:{return(13);break;}   //对应按键S14	
   case 0xb7:{return(14);break;}   //对应按键S15	
   case 0x77:{return(15);break;}   //对应按键S16
   default:{return(100);break;}	
  }
   
}