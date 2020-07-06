#include "Header.h"

const u8 STOP[]={0x2B,0x2B,0x2B,0x00};
const u8 RST[]={0x41,0x54,0x2B,0x52,0x53,0x54,0x0D,0x0A,0x00};
const u8 CIPSTATUS[]={0x41,0x54,0x2B,0x43,0x49,0x50,0x53,0x54,0x41,0x54,0x55,0x53,0x0D,0x0A,0x00};
const u8 CIPSTART[]={0x41,0x54,0x2B,0x43,0x49,0x50,0x53,0x54,0x41,0x52,0x54,0x3D,0x22,0x54,0x43,0x50,0x22,0x2C,0x22,0x34,0x37,0x2E,0x31,0x30,0x30,0x2E,0x35,0x38,0x2E,0x31,0x30,0x35,0x22,0x2C,0x36,0x30,0x30,0x30,0x0D,0x0A,0x00};
const u8 CIPMODE[]={0x41,0x54,0x2B,0x43,0x49,0x50,0x4D,0x4F,0x44,0x45,0x3D,0x31,0x0D,0x0A,0x00};
const u8 CIPSEND[]={0x41,0x54,0x2B,0x43,0x49,0x50,0x53,0x45,0x4E,0x44,0x0D,0x0A,0x00};
u8 CONNECTED[]={'C','O','N','N','E','C','T','E','D',0};
u8 GAS[]={0xD3,0xD0,0xBA,0xA6,0xC6,0xF8,0xCC,0xE5,0xB1,0xA8,0xBE,0xAF,0};
u8 PM25[]={0x50,0x4D,0x32,0x2E,0x35,0xB3,0xAC,0xB1,0xEA,0xB1,0xA8,0xBE,0xAF,0};
u8 T[10]={'T',':',0,0,0,'.',0,0xA1,0xE6,0};
u8 H[9]={'H',':',0,0,0,'.',0,0x25,0};
u8 P[10]={'P','M','2','.','5',':',0,0,0,0};
u8 G[9]={'G',':',0,0,0,'p','p','m',0};
u8 Send_Buff[19]={'S','J',0};
u16 temperature=0,humidity=0;//保存温湿度
int PM2_5=0,Gas=0;//保存PM2.5及有害气体
int PM2_5_TH=150,Gas_TH=100;//保存PM2.5及有害气体报警阈值
u16 TCP_Len;//WiFi模块接收到的数据长度	
u16 IRQ_Time=0;//定时器中断计数
u32 Dis_Count=0;//命令显示计时
u8 Dis_Flag=0;//命令接收标志
u8 Gas_Flag=0;//有害气体报警发送标志
u8 PM2_5_Flag=0;//PM2.5报警发送标志
u32 Target=3;//调整目标
u8 Dis[4]={0,0,0,0};//显示缓存

void Dis_TH(int data,u8 *buff);

int main()	  
{	
	SystemInit(0X00000);	//参数为向量表的偏移地址	
	delay_init();
  Uart_Init(115200);
	GPIO_Config();
  TFT_Init();
	TIM3_Configuration(71,1000);
	ADC_Configuration();
	DHT11_Init();	//DHT11初始化	
	
	TFT_Clear(BLACK);
  TFT_PutString(10,10,"READY",RED,BLACK);
	Send_Command(STOP);//WiFi初始化停止传输
	delay_ms(2000);
	Send_Command(RST);//WiFi初始化复位
	delay_ms(10000);
  TIM_Cmd(TIM3,ENABLE);//打开WiFi连接超时复位看门狗
	
	while(1)
	{
		Send_Command(CIPSTATUS);
		delay_ms(2000);
		if(USART_RX_STA&0x8000)
		{
			TCP_Len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			if(USART_RX_BUF[TCP_Len-1]==0x32)
			{
				TFT_PutString(30,10,"CONNECTED",RED,BLACK);
				USART_RX_STA=0;
				TIM_Cmd(TIM3,DISABLE);
				break;
			}
			USART_RX_STA=0;
		}
	}
	delay_ms(1000);
	
	Send_Command(CIPSTART);//连接服务器
	delay_ms(1000);
	Send_Command(CIPSTART);
	delay_ms(1000);
	
	Send_Command(CIPMODE);//使能透传模式
	delay_ms(1000);
	
	Send_Command(CIPSEND);//开始传输数据
  delay_ms(1000);
	
  Send_Command(CONNECTED);//向上位机发送已连接
	USART_RX_STA=0;//清除接受状态
	TFT_Clear(BLACK);
	TFT_PutString(5 ,0,"温度:    ℃",RED,BLACK);
  TFT_PutString(25,0,"湿度:    %",RED,BLACK);
  TFT_PutString(45,0,"PM2.5:    ",RED,BLACK);
  TFT_PutString(65,0,"有害气体:   ppm",RED,BLACK);
  TFT_PutString(85,0,"PM2.5_TH:150",RED,BLACK);
	TFT_PutString(105,0,"GAS_TH:100ppm",RED,BLACK);
	Send_Buff[0]='S';
  Send_Buff[1]='J';
	while(1)
	{
		DHT11_Read_Data(&temperature,&humidity);	//读取温湿度值	
		Display_TH(temperature,T);//计算温度
		TFT_PutChar(5, 40, T[3], RED, BLACK);
		TFT_PutChar(5, 48, T[4], RED, BLACK);
		TFT_PutString(5, 56, ".", RED, BLACK);
		TFT_PutChar(5, 64, T[6], RED, BLACK);
		Send_Buff[2]=T[3];
    Send_Buff[3]=T[4];
		Send_Buff[4]=T[5];
		Send_Buff[5]=T[6];
		
		Display_TH(humidity,H);//计算湿度
		TFT_PutChar(25, 40, H[3], RED, BLACK);
		TFT_PutChar(25, 48, H[4], RED, BLACK);
		TFT_PutString(25, 56, ".", RED, BLACK);
		TFT_PutChar(25, 64, H[6], RED, BLACK);
		Send_Buff[6]=H[3];
    Send_Buff[7]=H[4];
		Send_Buff[8]=H[5];
		Send_Buff[9]=H[6];
		
		PM2_5=Get_PM2_5();//获取PM2.5浓度
		PM2_5=PM2_5/10;
		Display_P(PM2_5,P);
		TFT_PutChar(45, 48,  P[6], RED, BLACK);
		TFT_PutChar(45, 56,  P[7], RED, BLACK);
		TFT_PutChar(45, 64,  P[8], RED, BLACK);
		Send_Buff[10]=P[6];
    Send_Buff[11]=P[7];
		Send_Buff[12]=P[8];
		
    Gas=Get_Gas();//获取有害气体浓度
    Gas=ABS(Gas/20);//计算有害气体
		Display_G(Gas,G);
		TFT_PutChar(65, 72,  G[2], RED, BLACK);
		TFT_PutChar(65, 80,  G[3], RED, BLACK);
		TFT_PutChar(65, 88,  G[4], RED, BLACK);		
		Send_Buff[14]=G[2];
    Send_Buff[15]=G[3];
		Send_Buff[16]=G[4];
		
    if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)==0)
		{
			while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11)==0);
		  Target++;
			Target%=2;
			if(Target==0)
			{
			  TFT_PutString(85  ,112 ,"对",RED,BLACK);
				TFT_PutString(105 ,112 ,"对",BLACK,BLACK);
			}
			else if(Target==1)
			{
			  TFT_PutString(85  ,112 ,"对",BLACK,BLACK);
				TFT_PutString(105 ,112 ,"对",RED,BLACK);			
			}
		}
		if(Target==0)//调整PM2.5阈值
		{
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)==0)//加阈值
			{
				while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)==0);
				PM2_5_TH+=10;
				if(PM2_5_TH>900)
					PM2_5_TH=900;
				
				Dis_TH(PM2_5_TH,Dis);
        TFT_PutString(85, 72, Dis, RED, BLACK);		
			}
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0)//减阈值
			{
				while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0);
				PM2_5_TH-=10;
				if(PM2_5_TH<=0)
					PM2_5_TH=0;
				
				Dis_TH(PM2_5_TH,Dis);
				TFT_PutString(85, 72, Dis, RED, BLACK);		
			}				
		}
		else if(Target==1)//调整有害气体阈值
		{
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)==0)//加阈值
			{
				while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10)==0);
				Gas_TH+=10;
				if(Gas_TH>900)
					Gas_TH=900;
								
				Dis_TH(Gas_TH,Dis);
        TFT_PutString(105, 56, Dis, RED, BLACK);		
			}
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0)//减阈值
			{
				while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_1)==0);
				Gas_TH-=10;
				if(Gas_TH<=0)
					Gas_TH=0;

				Dis_TH(Gas_TH,Dis);
        TFT_PutString(105, 56, Dis, RED, BLACK);					
			}				
		}
		
	  if(Gas>Gas_TH||PM2_5>PM2_5_TH)//超量报警
		{
			if(Gas>Gas_TH&&Gas_Flag==0)
			{
				Send_Buff[17]='1';

				Gas_Flag=1;
			}
			if(PM2_5>PM2_5_TH&&PM2_5_Flag==0)
			{
				Send_Buff[13]='1';
				PM2_5_Flag=1;
			}
		  GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_SET);
		}
		else//取消报警
		{
      GPIO_WriteBit(GPIOB,GPIO_Pin_0,Bit_RESET);			
		}
		
		if(Gas<=Gas_TH)
		{
			Send_Buff[17]='0';
			Gas_Flag=0;
		}
		if(PM2_5<=PM2_5_TH)
		{
			Send_Buff[13]='0';
			PM2_5_Flag=0;
		}	
		
		Send_Data(Send_Buff,18);
		delay_ms(1000);
	}
}

void Dis_TH(int data,u8 *buff)//显示阈值
{
	*(buff+0)=data/100+0x30;
	*(buff+1)=data%100/10+0x30;
	*(buff+2)=data%100%10+0x30;
}
void TIM3_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	
	IRQ_Time++;
	if(IRQ_Time==30000)
	{
	  IRQ_Time=0;
	  Send_Command(RST);
	}
}
