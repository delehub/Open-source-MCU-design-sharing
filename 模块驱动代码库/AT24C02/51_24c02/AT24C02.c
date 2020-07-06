#include "AT24C02.h"
/******************************************************************
 - ������������AT24C02�ĵ�ַΪaddr�ĵ�Ԫ��д��һ���ֽ�dat
 - ����˵����addr:AT24C02�ĵ�Ԫ��ַ
             dat:Ҫд����ֽ�     
 - ע��AT24C02�ĵ�ַ���ֽڼ���ַ������С�洢��Ԫ���ֽڣ���ַ��Χ 
       ��0~8191
 ******************************************************************/

void IIC_AT24C02_writebyte(uint addr,uchar dat) 
{
 IIC_start();             //����IIC����
 IIC_writebyte(0xa0);      //1010 A2 A1 A0 R/W [A2:A0]��AT24C02��оƬ��ַ��0~7����ͬһ��IIC�����Ͽ��Թҽ�8��оƬ��R/W�Ƕ�/дѡ��λ��0Ϊд������1Ϊ������
 IIC_respons();
 IIC_writebyte(addr);      //д���ַ�ֽ�
 IIC_respons();
 IIC_writebyte(dat);       //д��һ���ֽڵ�����
 IIC_respons();
 IIC_stop();               //IIC���������AT24C64��ʼִ�У�������һ���ֽ�д��EEPROM��
 Delay_ms(4);              //�ȴ�AT24C64������ɣ����5ms
}

/******************************************************************
 - ����������дҳ����
 - ����˵����addr:ҳ��ʼ��ַ
             pbuf:ָ�����ݻ�������ָ��    
 - ����˵������
 - ע����AT24C02оƬaddr��ַ��������д��32���ֽڣ���дҳ������
       ��Щ���ݴ����pbuf��
 ******************************************************************/

void IIC_AT24C02_writepage(uint addr,uchar length,unsigned char *pbuf) 
{
 unsigned char i;
 IIC_start();             //����IIC����
 IIC_writebyte(0xa0);     //1010 A2 A1 A0 R/W [A2:A0]��AT24C64��оƬ��ַ��0~7����ͬһ��IIC�����Ͽ��Թҽ�8��оƬ��R/W�Ƕ�/дѡ��λ��0Ϊд������1Ϊ������
 IIC_respons();
 IIC_writebyte(addr);     //д���ַ�ֽ�
 IIC_respons();
 for(i=0;i<length;i++)
 {
  IIC_writebyte(pbuf[i]); //��pbuf�е�32���ֽ�д��AT24C64�����ݻ�����
  IIC_respons();
 }
 IIC_stop();               //IIC���������AT24C64��ʼִ�У�������32���ֽ�д��EEPROM��
 Delay_ms(4);              //�ȴ�AT24C64������ɣ����5ms
}

/******************************************************************
 - �����������ӵ�ǰ��ַ������ȡlength���ֽڣ�����pbufָ������ݻ�����
 - ����ģ�飺AT24C02ģ��
 - �������ԣ��ⲿ�����û�ʹ��
 - ����˵����length:Ҫ��ȡ�����ݳ���
             pbuf:ָ�����ݻ�������ָ��    
 - ����˵������
 - ע���ӵ�ǰ�ĵ�ַ�϶�ȡ���ݣ����Դ˺�����û��д���ַ�Ĳ���
 ******************************************************************/

void IIC_AT24C02_readpage(uint addr,uint length,unsigned char *pbuf) 
{
 unsigned char i;
 IIC_start();                   //�������䣬�����ٴ��������䣬��Ϊ����Ҫд�롰����������ָ���룬��0xa1
 IIC_writebyte(0xa1);           //д��0xa1����AT24C64�ж�ȡ����
 IIC_respons();
 for(i=0;i<length-1;i++)
 {
  pbuf[i]=IIC_readbyte();       //��ȡlength-1���ֽ�
  IIC_ack();			        //ǰlength-1���ֽڣ�ÿ����һ���ֽ�Ҫ��AT24C64�ṩACK��������������ṩ��������ݣ���ȡ������δ���
 }
 pbuf[i]=IIC_readbyte();        //��ȡ���һ���ֽڣ�����length���ֽ�
 IIC_nack();                    //��ȡ���һ���ֽں�Ҫ��AT24C64����NACK���������ȡ�����������������¶���
 IIC_stop();                    //�������  
}
/***************************
��24C02�ж�������
����ַ���Ӹõ�ַ�ж����洢��
����
**************************/
uchar  IIC_AT24C02_readbyte(uchar address)
{
	uchar cc;
	IIC_start();
	IIC_writebyte(0xa0);
	IIC_respons();
	IIC_writebyte(address);
	IIC_respons();
	IIC_start();
	IIC_writebyte(0xa1);
	IIC_respons();
	cc=IIC_readbyte();
	IIC_stop();
	return cc;
} 
