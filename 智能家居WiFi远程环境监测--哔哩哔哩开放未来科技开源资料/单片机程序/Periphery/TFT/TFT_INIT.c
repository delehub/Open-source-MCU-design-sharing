#include "TFT.H"

void Delay_TFT(u32 Delayms);

/**********************************
***********************************
TFT初始化   作者：陈开放
***********************************
**********************************/
void TFT_Init(void)
{
  uchar a=1;

	GPIO_InitTypeDef GPIO_InitStructure;
	//TFT_Contrl//PA10_TFT_CS//PA9_TFT_REST//PA8_TFT_DC 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;														   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10;	
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	//TFT_SPI//PA7_TFT_SDI//PA5_TFT_SCK
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
  //调用一次这些函数，免得编译的时候提示警告
  GPIO_SetBits(TFT_GPIO,TFT_CS);
	if(a==0)
	{
	   TFT_WR_REG_DATA(0,0);
	   Draw_Circle(1,1,1);
	   TFT_DrawLine(1, 1, 10, 10,RED);
	   TFT_DrawPoint_big(0,0,BLACK);

 	 }
	 GPIO_SetBits(TFT_GPIO,TFT_REST);    	
	 GPIO_ResetBits(TFT_GPIO,TFT_REST);

	 GPIO_SetBits(TFT_GPIO,TFT_REST); 
	 GPIO_SetBits(TFT_GPIO,TFT_CS); 

	 GPIO_ResetBits(TFT_GPIO,TFT_CS);  //打开片选使能
	 
//		TFT_WR_REG(0x11); //Sleep out
//		Delay_TFT(120); //Delay 120ms
//		//------------------------------------ST7735S Frame Rate-----------------------------------------//
//		TFT_WR_REG(0xB1);
//		TFT_WR_DATA8(0x05);
//		TFT_WR_DATA8(0x3C);
//		TFT_WR_DATA8(0x3C);
//		TFT_WR_REG(0xB2);
//		TFT_WR_DATA8(0x05);
//		TFT_WR_DATA8(0x3C);
//		TFT_WR_DATA8(0x3C);
//		TFT_WR_REG(0xB3);
//		TFT_WR_DATA8(0x05);
//		TFT_WR_DATA8(0x3C);
//		TFT_WR_DATA8(0x3C);
//		TFT_WR_DATA8(0x05);
//		TFT_WR_DATA8(0x3C);
//		TFT_WR_DATA8(0x3C);
//		//------------------------------------End ST7735S Frame Rate-----------------------------------------//
//		TFT_WR_REG(0xB4); //Dot inversion
//		TFT_WR_DATA8(0x03);
//		TFT_WR_REG(0xC0);
//		TFT_WR_DATA8(0x28);
//		TFT_WR_DATA8(0x08);
//		TFT_WR_DATA8(0x04);
//		TFT_WR_REG(0xC1);
//		TFT_WR_DATA8(0XC0);
//		TFT_WR_REG(0xC2);
//		TFT_WR_DATA8(0x0D);
//		TFT_WR_DATA8(0x00);
//		TFT_WR_REG(0xC3);
//		TFT_WR_DATA8(0x8D);
//		TFT_WR_DATA8(0x2A);
//		TFT_WR_REG(0xC4);
//		TFT_WR_DATA8(0x8D);
//		TFT_WR_DATA8(0xEE);
//		//---------------------------------End ST7735S Power Sequence-------------------------------------//
//		TFT_WR_REG(0xC5); //VCOM
//		TFT_WR_DATA8(0x1A);
//		TFT_WR_REG(0x36); //MX, MY, RGB mode
//		TFT_WR_DATA8(0xC0);
//		//------------------------------------ST7735S Gamma Sequence-----------------------------------------//
//		TFT_WR_REG(0xE0);
//		TFT_WR_DATA8(0x04);
//		TFT_WR_DATA8(0x22);
//		TFT_WR_DATA8(0x07);
//		TFT_WR_DATA8(0x0A);
//		TFT_WR_DATA8(0x2E);
//		TFT_WR_DATA8(0x30);
//		TFT_WR_DATA8(0x25);
//		TFT_WR_DATA8(0x2A);
//		TFT_WR_DATA8(0x28);
//		TFT_WR_DATA8(0x26);
//		TFT_WR_DATA8(0x2E);
//		TFT_WR_DATA8(0x3A);
//		TFT_WR_DATA8(0x00);
//		TFT_WR_DATA8(0x01);
//		TFT_WR_DATA8(0x03);
//		TFT_WR_DATA8(0x13);
//		TFT_WR_REG(0xE1);
//		TFT_WR_DATA8(0x04);
//		TFT_WR_DATA8(0x16);
//		TFT_WR_DATA8(0x06);
//		TFT_WR_DATA8(0x0D);
//		TFT_WR_DATA8(0x2D);
//		TFT_WR_DATA8(0x26);
//		TFT_WR_DATA8(0x23);
//		TFT_WR_DATA8(0x27);
//		TFT_WR_DATA8(0x27);
//		TFT_WR_DATA8(0x25);
//		TFT_WR_DATA8(0x2D);
//		TFT_WR_DATA8(0x3B);
//		TFT_WR_DATA8(0x00);
//		TFT_WR_DATA8(0x01);
//		TFT_WR_DATA8(0x04);
//		TFT_WR_DATA8(0x13);
//		//------------------------------------End ST7735S Gamma Sequence-----------------------------------------//
//		TFT_WR_REG(0x3A); //65k mode
//		TFT_WR_DATA8(0x05);
//		TFT_WR_REG(0x29); //Display on


	      TFT_WR_REG(0xCB);  
        TFT_WR_DATA8(0x39); 
        TFT_WR_DATA8(0x2C); 
        TFT_WR_DATA8(0x00); 
        TFT_WR_DATA8(0x34); 
        TFT_WR_DATA8(0x02); 
        Delay_TFT(10);
	 
        TFT_WR_REG(0xCF);  
        TFT_WR_DATA8(0x00); 
        TFT_WR_DATA8(0XC1); 
        TFT_WR_DATA8(0X30); 
        Delay_TFT(10);
				
        TFT_WR_REG(0xE8);  
        TFT_WR_DATA8(0x85); 
        TFT_WR_DATA8(0x00); 
        TFT_WR_DATA8(0x78); 
				Delay_TFT(10);
 
        TFT_WR_REG(0xEA);  
        TFT_WR_DATA8(0x00); 
        TFT_WR_DATA8(0x00); 
				Delay_TFT(10);
 
        TFT_WR_REG(0xED);  
        TFT_WR_DATA8(0x64); 
        TFT_WR_DATA8(0x03); 
        TFT_WR_DATA8(0X12); 
        TFT_WR_DATA8(0X81);
        Delay_TFT(10);				

        TFT_WR_REG(0xF7);  
        TFT_WR_DATA8(0x20);
        Delay_TFT(10);			
  
        TFT_WR_REG(0xC0);    //Power control 
        TFT_WR_DATA8(0x23);   //VRH[5:0] 
        Delay_TFT(10);
				
        TFT_WR_REG(0xC1);    //Power control 
        TFT_WR_DATA8(0x10);   //SAP[2:0];BT[3:0] 
        Delay_TFT(10);
				
        TFT_WR_REG(0xC5);    //VCM control 
        TFT_WR_DATA8(0x3e); //对比度调节
        TFT_WR_DATA8(0x28); 
        Delay_TFT(10);
				
        TFT_WR_REG(0xC7);    //VCM control2 
        TFT_WR_DATA8(0x86);  //--
        Delay_TFT(10);
				
        TFT_WR_REG(0x36);    // Memory Access Control 
        TFT_WR_DATA8(0x08); //重要寄存器
        Delay_TFT(10);
				
        TFT_WR_REG(0x3A);    
        TFT_WR_DATA8(0x55); 
        Delay_TFT(10);
				 
        TFT_WR_REG(0xB1);    
        TFT_WR_DATA8(0x00);  
        TFT_WR_DATA8(0x18);
        Delay_TFT(10);				
 
        TFT_WR_REG(0xB6);    // Display Function Control 
        TFT_WR_DATA8(0x08); 
        TFT_WR_DATA8(0x82);
        TFT_WR_DATA8(0x27);  
        Delay_TFT(10);
 
        TFT_WR_REG(0xF2);    // 3Gamma Function Disable 
        TFT_WR_DATA8(0x00);
				Delay_TFT(10);
 
        TFT_WR_REG(0x26);    //Gamma curve selected 
        TFT_WR_DATA8(0x01); 
        Delay_TFT(10);
 
        TFT_WR_REG(0xE0);    //Set Gamma 
        TFT_WR_DATA8(0x0F); 
        TFT_WR_DATA8(0x31); 
        TFT_WR_DATA8(0x2B); 
        TFT_WR_DATA8(0x0C); 
        TFT_WR_DATA8(0x0E); 
        TFT_WR_DATA8(0x08); 
        TFT_WR_DATA8(0x4E); 
        TFT_WR_DATA8(0xF1); 
        TFT_WR_DATA8(0x37); 
        TFT_WR_DATA8(0x07); 
        TFT_WR_DATA8(0x10); 
        TFT_WR_DATA8(0x03); 
        TFT_WR_DATA8(0x0E); 
        TFT_WR_DATA8(0x09); 
        TFT_WR_DATA8(0x00); 
				Delay_TFT(10);
				
        TFT_WR_REG(0XE1);    //Set Gamma 
        TFT_WR_DATA8(0x00); 
        TFT_WR_DATA8(0x0E); 
        TFT_WR_DATA8(0x14); 
        TFT_WR_DATA8(0x03); 
        TFT_WR_DATA8(0x11); 
        TFT_WR_DATA8(0x07); 
        TFT_WR_DATA8(0x31); 
        TFT_WR_DATA8(0xC1); 
        TFT_WR_DATA8(0x48); 
        TFT_WR_DATA8(0x08); 
        TFT_WR_DATA8(0x0F); 
        TFT_WR_DATA8(0x0C); 
        TFT_WR_DATA8(0x31); 
        TFT_WR_DATA8(0x36); 
        TFT_WR_DATA8(0x0F); 
				Delay_TFT(10);
 
        TFT_WR_REG(0x11);    //Exit Sleep 
				Delay_TFT(10);
				
        TFT_WR_REG(0x29);    //Display on 
        TFT_WR_REG(0x2c); 
				Delay_TFT(10);
}

void Delay_TFT(u32 Delayms)
{
	u32 delay;
  for(;Delayms>0;Delayms--)
    for(delay=2000;delay>0;delay--);

}






