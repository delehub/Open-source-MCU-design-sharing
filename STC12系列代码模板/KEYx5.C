
#include"KEYx5.H"
#include"MAIN.H"
//5号引脚代表主持人	
sbit KEYx5_1=P1^3;
sbit KEYx5_2=P1^4;
sbit KEYx5_3=P1^5;
sbit KEYx5_4=P1^6;
sbit KEYx5_5=P1^7;
unsigned char KEYx5_1_Get_value(void)
{

	if(KEYx5_1==0)
	{
		DELAY_nMS(1000);
		if(KEYx5_1==0)
		{
			return 1;
		}
		return 0;
	}
	else
	{									  
		return 0;
	}


}
unsigned char KEYx5_2_Get_value(void)
{

	if(KEYx5_2==0)
	{
		 DELAY_nMS(1000);
		 if(KEYx5_2==0)
		 {
		 return 1;
		 }
		 return 0;
	}
	else
	{									  
	 return 0;
	}


}
unsigned char KEYx5_3_Get_value(void)
{

	if(KEYx5_3==0)
	{
		 DELAY_nMS(1000);
		 if(KEYx5_3==0)
		 {
		 return 1;
		 }
		 return 0;
	}
	else
	{									  
	 return 0;
	}


}
unsigned char KEYx5_4_Get_value(void)
{

	if(KEYx5_4==0)
	{
		 DELAY_nMS(1000);
		 if(KEYx5_4==0)
		 {
		 return 1;
		 }
		 return 0;
	}
	else
	{									  
	 return 0;
	}


}
unsigned char KEYx5_5_Get_value(void)
{

	if(KEYx5_5==0)
	{
		 DELAY_nMS(1000);
		 if(KEYx5_5==0)
		 {
		 return 1;
		 }
		 return 0;
	}
	else
	{									  
	 return 0;
	}


}
	