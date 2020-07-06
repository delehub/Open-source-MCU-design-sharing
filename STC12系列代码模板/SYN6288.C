#include"MAIN.H"
#include"SYN6288.H"

void SYN6288_Play(unsigned char *String )
{
    unsigned char i;
	unsigned char Count;
	unsigned char check=0x00;
	while(String[Count++]);
	

	send_char(0xfd);   //发送帧头
	check^=0xfd;	   //异或校验
	DELAY_nMS(1);

	send_char(0x00);   //发送数据长度高8位
	check^=0x00;
	DELAY_nMS(1);

	send_char(Count+3);	//发送数据长度低8位
	check^=(Count+3);
	 DELAY_nMS(1);

	send_char(0x01);	//发送命令字，发送语音合成命令
	check^=0x01;
	 DELAY_nMS(1);

	send_char(0x00);	 //	发送命令参数
	check^=0x00;
	 DELAY_nMS(1);

	//发送文本内容
	for(i=0;i<Count;i++)
	{
	    send_char(String[i]);
		check^=String[i];
	}

	send_char(check);		//发送校验位

}