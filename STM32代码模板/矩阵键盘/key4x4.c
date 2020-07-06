/******************** (C) COPYRIGHT 2013 CEPARK�๦�ܿ���ѧϰ��********************
 * �ļ���  ��key4x4.c
 * ����    ������Ӧ�ú�����        
 * ʵ��ƽ̨��CEPARK�๦�ܿ���ѧϰ��
 * Ӳ�����ӣ�-------------------------
 *          | PB8  - H4          |
 *          | PB9  - H3			     |
 *          | PB10 - H2          |
 *          | PB11 - H1		       |
 *          | PB12 - L4          |
 *          | PB13 - L3		       |
 *          | PB14 - L2          |
 *          | PB15 - L1			     |
 *           -------------------------
 * ��汾  ��ST3.5.0
**********************************************************************************/

#include "key4x4.h" 
#include "delay.h" 

 /*
 * ��������Key_GPIO_Config
 * ����  �����ð����õ���I/O��
 * ����  ����
 * ���  ����
 */
void Key4x4_GPIO_Config(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
  	
  	/*���������˿ڵ�ʱ��*/
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15; 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 
		GPIO_Init(GPIOB, &GPIO_InitStructure);

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;	
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;       
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

u8 Key_Scan(void)
{
	u16 temp;
	u8 ucBackValue=0;
	//====ɨ���һ��==========
	GPIO_Write(GPIOB,0xfe00); 
	temp=GPIO_ReadInputData(GPIOB); //���������ڵõ���ֵ
	temp=temp&0xf000;    //���ε�4λ
	if (temp!=0xf000)      //�����4λ��ȫ��1
	{ 
		delay_ms(20);      // ��ʱ�����ٶ�
		temp=GPIO_ReadInputData(GPIOB); 
		temp=temp&0xf000;
		if (temp!=0xf000)     //����������ٴθ�4λȷ������ȫ1
		{ 
			temp=GPIO_ReadInputData(GPIOB)&0xff00; //�����˴ΰ�����ֵ
			switch(temp)
			{ 
				case 0xee00:
				ucBackValue = 1;break;
				case 0xde00:
				ucBackValue = 5;break;
				case 0xbe00:
				ucBackValue = 9;break;
				case 0x7e00:
				ucBackValue = 13;break;
				default:break;
			}
			while(temp!=0xf000)   //�ȴ������ſ�����ʼ��Ȼ��ִ��
			{ 
				temp=GPIO_ReadInputData(GPIOB); 
				temp=temp&0xf000;
			}

		}
	}

	//====�ڶ�����0==========
	GPIO_Write(GPIOB,0xfd00); 
	temp=GPIO_ReadInputData(GPIOB); //���������ڵõ���ֵ
	temp=temp&0xf000;    //���ε�4λ
	if (temp!=0xf000)      //�����4λ��ȫ��1
	{ 
		delay_ms(20);      // ��ʱ�����ٶ�
		temp=GPIO_ReadInputData(GPIOB); 
		temp=temp&0xf000;
		if (temp!=0xf000)     //����������ٴθ�4λȷ������ȫ1
		{ 
			temp=GPIO_ReadInputData(GPIOB)&0xff00; //�����˴ΰ�����ֵ
			switch(temp)
			{ 
				case 0xed00:
					ucBackValue = 2; break;
				case 0xdd00:
					ucBackValue = 6; break;
				case 0xbd00:
					ucBackValue = 10; break;
				case 0x7d00:
					ucBackValue = 14; break;
				default:break;
		}
			while(temp!=0xf000)   //�ȴ������ſ�
			{ 
				temp=GPIO_ReadInputData(GPIOB); 
				temp=temp&0xf000;
			}
		}
	}
	//====��3����0==========
	GPIO_Write(GPIOB,0xfb00); 
	temp=GPIO_ReadInputData(GPIOB); //���������ڵõ���ֵ
	temp=temp&0xf000;    //���ε�4λ
	if (temp!=0xf000)      //�����4λ��ȫ��1
	{ 
		delay_ms(20);      // ��ʱ�����ٶ�
		temp=GPIO_ReadInputData(GPIOB); 
		temp=temp&0xf000;
		if (temp!=0xf000)     //����������ٴθ�4λȷ������ȫ1
		{ 
			temp=GPIO_ReadInputData(GPIOB)&0xff00; //�����˴ΰ�����ֵ
			switch(temp)
			{ 
				case 0xeb00:
				ucBackValue = 3; break;
				case 0xdb00:
				ucBackValue = 7; break;
				case 0xbb00:
				ucBackValue = 11; break;
				case 0x7b00:
				ucBackValue = 15; break;
				default:break;
		}
		while(temp!=0xf000)   //�ȴ������ſ�
		{ 
			temp=GPIO_ReadInputData(GPIOB); 
			temp=temp&0xf000;
		}
		}
	}
	//====��4����0==========
	GPIO_Write(GPIOB,0xf700); 
	temp=GPIO_ReadInputData(GPIOB); //���������ڵõ���ֵ
	temp=temp&0xf000;    //���ε�4λ
	if (temp!=0xf000)      //�����4λ��ȫ��1
	{ 
		delay_ms(20);       // ��ʱ�����ٶ�
		temp=GPIO_ReadInputData(GPIOB); 
		temp=temp&0xf000;
		if (temp!=0xf000)     //����������ٴθ�4λȷ������ȫ1
		{ 
			temp=GPIO_ReadInputData(GPIOB)&0xff00; 
			switch(temp)
			{ 
				case 0xe700:
				ucBackValue = 4; break;
				case 0xd700:
				ucBackValue = 8; break;
				case 0xb700:
				ucBackValue = 12; break;
				case 0x7700:
				ucBackValue = 16; break;
				default:break;
			}
			while(temp!=0xf000)   //�ȴ������ſ�
			{ 
				temp=GPIO_ReadInputData(GPIOB); 
				temp=temp&0xf000;
			}
		}
	}
	return ucBackValue;
}

