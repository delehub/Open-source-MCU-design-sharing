#include"MAIN.H"
#include"HX711.H"
sbit HX711_SCL=P3^6;
sbit HX711_SDA=P3^7;

unsigned long int get_ADValue(void)
{
	unsigned char i;
	unsigned long value=0;
	HX711_SDA=1;				//51CPU I/O inputenable
	HX711_SCL=0;				//enable AD
	while(HX711_SDA);
	_nop_();			//delay T1>0.1us
	for(i=0;i<24;i++)
	{
		HX711_SCL=1;
		_nop_();		//delay T3>0.2us
		if(HX711_SDA)
		value++;
		value=value<<1;
		HX711_SCL=0;
		_nop_();		//delay T4>0.2us
	}
	HX711_SCL=1;
	_nop_();			//delay T3>0.2us
	HX711_SCL=0;
	_nop_();			//delay T4>0.2us
	value=value&0x007FFFFF;
	return(value);
}
unsigned int Fact_Value(void)
{
	  unsigned long int Weight;
      unsigned long int Base_Weight=0;
	  Weight=get_ADValue();

	   if( Weight<Base_Weight)
	   {
			Weight=	Base_Weight;
	   }
	   if((Weight>Base_Weight)&&(Weight<(Base_Weight+1000)))
	   {
	
			Weight=	Base_Weight;
	   }
//	  Display_String(0,1,"ÖØÁ¿£º");
//	  Display_Int(3,0,(unsigned int)((float)((Weight-Base_Weight)/100) *0.119));
//	  Display_Char(5,0,'g');
//	  if((Weight-Base_Weight)>0)
//	  {
//		  Array[0]=((Weight-Base_Weight)/1000)%10+0x30;
//		  Array[1]=((Weight-Base_Weight)/100 )%10+0x30;
//		  Array[2]=((Weight-Base_Weight)/10  )%10+0x30;
//		  Array[3]=((Weight-Base_Weight)/1   )%10+0x30;
//		  Array[4]='g';
//		  Array[5]=0x00;
//		  SYN6288_Play(Array);
//	  }
	     return((unsigned int)((float)((Weight-Base_Weight)/100) *0.119));


}




