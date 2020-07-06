#include "MMA7455.H"
//sbit sda=P2^3;              //I2C 数据传送位
//sbit scl=P2^4;              //I2C 时钟传送位
unsigned char sign_flag;  //输出数据正负标记位
void IIC_MMA7455_init()
{
 IIC_start();
 IIC_writebyte(MMA7455_ADDER_WRITE);     //1. 在IIC总线上寻址MMA7455
 while(IIC_respons());
 IIC_writebyte(MMA7455_Mode_Control_Register);    //2. 模式设置寄存器寻址 
 while(IIC_respons());
 IIC_writebyte(MMA7455_2G_Measurement_Mode);         //3. 模式寄存器数据写入
 while(IIC_respons());
 IIC_stop(); 
 IIC_start();
 IIC_writebyte(MMA7455_ADDER_WRITE);     //1. 在IIC总线上寻址MMA7455
 while(IIC_respons());
 IIC_writebyte(MMA7455_Mode_Control_Register);    //2. 模式设置寄存器寻址 
 while(IIC_respons());
 IIC_writebyte(MMA7455_2G_Measurement_Mode);         //3. 模式寄存器数据写入
 while(IIC_respons());
 IIC_stop(); 

}
void IIC_MMA7455_writedata(uchar byte_add,uchar wdata)//函数功能：按地址写入一字节数据
{
     unsigned char  temp;
	 temp=(IIC_WRITE<<1);
	 IIC_start();
	 IIC_writebyte(temp);
	 while(IIC_respons());
	 IIC_writebyte(byte_add);
	 while(IIC_respons());
     IIC_writebyte(wdata);
	 while(IIC_respons());
	 IIC_stop();
}
unsigned char IIC_MMA7455_readdata(uchar byte_add)	           //函数功能：按地址读出一字节数据
{
     unsigned char temp;
	 char x_y_z ;
	 temp=(IIC_WRITE<<1);
	 IIC_start();
	 IIC_writebyte(0x3A);
	 while(IIC_respons());
	 IIC_writebyte(byte_add);
	 while(IIC_respons());
	 temp=((IIC_READ<<1)|0x01);
	 IIC_start();
	 IIC_writebyte(0x3B);
	 while(IIC_respons());
	 x_y_z=IIC_readbyte();
	 while(IIC_respons());
	 IIC_stop();
	 return x_y_z;
}

unsigned char IIC_MMA7455_test()
{
    unsigned char temp;
	for(temp=255;temp<=1;temp--);
    IIC_MMA7455_writedata(0x16,0x05);
	for(temp=255;temp<=1;temp--);	
    temp=IIC_MMA7455_readdata(0x16);
	if(temp==0x05) {return 1;}
	else{return 0;}	
}
unsigned char IIC_MMA7455_checkbusy()
{
	 unsigned char temp;										
	 temp=IIC_MMA7455_readdata(MMA7455_READ_STATUS);
	 if((temp&0x01)==1)
	 {
	 	return 1;
	 }
	 else 
	 {
	 	return 0;
	 }

}
unsigned char IIC_MMA7455_getvalue(unsigned char address_byte)
{
   unsigned char temp; 
   while(!IIC_MMA7455_checkbusy());
   temp=IIC_MMA7455_readdata(address_byte);
   if((temp&0x80)==0x00)
   {
   	 sign_flag=0;
	 return temp;
   
   }
   else
   {
   	 sign_flag=1;
	 temp=temp-0x01;
	 temp=~temp;
	 return temp;
   }
}
unsigned char IIC_MMA7455_getaverage(unsigned char address_byte)
{
    unsigned char num,temp;
	unsigned int  temps=0x00;
	for(num=50;num>0;num--)
	{
		temp=IIC_MMA7455_getvalue(address_byte);
		temps=temps+temp;	
	}
	temp=temps/50;
	return temp;
}



unsigned char IIC_MMA7455_getacceleration(unsigned char address_byte)
{
	unsigned int temp;
	temp=IIC_MMA7455_getaverage(address_byte);
	temp=temp*200;
	temp=temp>>7;
	return temp;

}
unsigned char IIC_MMA7455_calibrate_X()
{
   unsigned char tempX,time;										
   while(!IIC_MMA7455_checkbusy());
   tempX=IIC_MMA7455_readdata(MMA7455_READ_X);
   for(time=100;time>0;time--)
   {
   if((tempX&0x80)==0x00)
   {
   	 tempX=tempX+tempX;
	 tempX=~tempX+1;
	 IIC_MMA7455_writedata(MMA7455_RW_XOFFL,tempX);   
   }
   else
   {
	 tempX=tempX-1;
	 tempX=~tempX;
	 tempX=tempX+tempX;
	 IIC_MMA7455_writedata(MMA7455_RW_XOFFL,tempX);
   }
   tempX=IIC_MMA7455_readdata(MMA7455_READ_X);
   if((tempX<=10)&&(tempX>=-10)){break;} 
   }
   return 1;
}



unsigned char IIC_MMA7455_calibrate_Y()
{
   unsigned char tempY,time;										
   while(!IIC_MMA7455_checkbusy());
   tempY=IIC_MMA7455_readdata(MMA7455_READ_Y);
   for(time=100;time>0;time--)
   {
   if((tempY&0x80)==0x00)
   {
   	 tempY=tempY+tempY;
	 tempY=~tempY+1;
	 IIC_MMA7455_writedata(MMA7455_RW_XOFFL,tempY);   
   }
   else
   {
	 tempY=tempY-1;
	 tempY=~tempY;
	 tempY=tempY+tempY;
	 IIC_MMA7455_writedata(MMA7455_RW_XOFFL,tempY);
   }
   tempY=IIC_MMA7455_readdata(MMA7455_READ_Y);
   if((tempY<=10)&&(tempY>=-10)){break;} 
   }
   return 1;
}




unsigned char IIC_MMA7455_calibrate_Z()
{
   unsigned char tempZ,time;										
   while(!IIC_MMA7455_checkbusy());
   tempZ=IIC_MMA7455_readdata(MMA7455_READ_Z);
   for(time=100;time>0;time--)
   {
   if((tempZ&0x80)==0x00)
   {
   	
	 tempZ=64-tempZ;
	 if(tempZ==0){break;}
	 if(tempZ>0)
	 {
	 	tempZ=tempZ+tempZ;
	 	tempZ=~tempZ+1;
	 	IIC_MMA7455_writedata(MMA7455_RW_XOFFL,tempZ);
	 } 
	 if(tempZ<0)
	 {
	 	tempZ=tempZ+tempZ;
	 	IIC_MMA7455_writedata(MMA7455_RW_XOFFL,tempZ);
	 }  
   }
   else
   {
	 tempZ=tempZ-1;
	 tempZ=~tempZ;
	 tempZ=64+tempZ;
	 tempZ=tempZ+tempZ;
	 IIC_MMA7455_writedata(MMA7455_RW_XOFFL,tempZ);
   }
   tempZ=IIC_MMA7455_readdata(MMA7455_READ_Z);
   if((tempZ<=70)&&(tempZ>=50)){break;} 
   }
   return 1;
}
