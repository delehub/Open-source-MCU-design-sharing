#include"MAIN.H"

void main(void)
{	
    init_com();
	 UART_SendString("44444");



	 
    while(1)		 								 
    {
	  UART_SendFloatNumber( Voice());
	  UART_SendLine();
	  UART_SendString("3333");
	  DELAY_nMS(1000);





	}
}





unsigned char Count=0;

void Timer0_IRQS(void) interrupt 1
{
	 Count++;
	 if(Count>100)
	 {
	    Count=0;
//		speed=TH1*256+TL1;	 
		

	 }

	TL0 = (65536-10000)%256;		//设置定时初值 (65536-50000)%256
	TH0 = (65536-10000)/256;		//设置定时初值 (65536-50000)/256
}


////
////unsigned char ReadByte =0x00;
//////
//
//void UART_IRQS(void) interrupt 4
//{
//    
//    if(RI)      // 判断接受标志位
//    {
//        RI=0;   // 清除接受标志位
//       PWM_Duty = SBUF;
//	   UART_SendIntNumber(PWM_Duty);
//       UART_SendLine();
//        // 以下你写的代码
//    }
//}