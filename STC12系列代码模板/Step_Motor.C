#include"MAIN.H"
#include"Step_Motor.H"
sbit SA=P2^0;
sbit SB=P2^1;
sbit SC=P2^2;
sbit SD=P2^3;
void Step_MotorFoword(void)
{
   	  SA=1;
	  SB=0;
	  SC=0;
	  SD=0;
	  DELAY_nMS(10);
	  SA=0;
	  SB=1;
	  SC=0;
	  SD=0;
	  DELAY_nMS(10);
	  SA=0;
	  SB=0;
	  SC=1;
	  SD=0;
	  DELAY_nMS(10);
	  SA=0;
	  SB=0;
	  SC=0;
	  SD=1;
	  DELAY_nMS(10);

}
//x=512  360 
//x=256  180
void Step_Motor(unsigned int x)
{
   	 unsigned int i;
	 for(i=0;i<x;i++)
	 {
	   	Step_MotorFoword();
	 }

}
