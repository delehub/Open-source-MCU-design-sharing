
/*2.8��TFT�������ӿڶ���*/
#define GPIO_TFT_DATA                   GPIOA    				         //���ݿ�PA0~PA7
#define RCC_GPIO_TFT                    RCC_APB2Periph_GPIOA

#define GPIO_CTRB			              		GPIOB    				         //���ƿ�PB8~PA13
#define RCC_GPIO_CTRB    								RCC_APB2Periph_GPIOB

#define RS_CLR	        GPIO_ResetBits(GPIO_CTRB, GPIO_Pin_13)     //RS�õ�
#define RS_SET	        GPIO_SetBits(GPIO_CTRB, GPIO_Pin_13)       //RS�ø�

#define RW_CLR	        GPIO_ResetBits(GPIO_CTRB, GPIO_Pin_12)     //RW�õ�
#define RW_SET	        GPIO_SetBits(GPIO_CTRB, GPIO_Pin_12)  		  //RW�ø�

#define RD_CLR	        GPIO_ResetBits(GPIO_CTRB, GPIO_Pin_11)     //E�õ�
#define RD_SET	        GPIO_SetBits(GPIO_CTRB, GPIO_Pin_11)       //E�ø�

#define CS_CLR	        GPIO_ResetBits(GPIO_CTRB, GPIO_Pin_10)     //CS�õ�
#define CS_SET	        GPIO_SetBits(GPIO_CTRB, GPIO_Pin_10)       //CS�ø�

#define RST_CLR	        GPIO_ResetBits(GPIO_CTRB, GPIO_Pin_9)     //RST�õ�
#define RST_SET	        GPIO_SetBits(GPIO_CTRB, GPIO_Pin_9)       //RST�ø�

#define LE_CLR	        GPIO_ResetBits(GPIO_CTRB, GPIO_Pin_8)     //LE�õ�
#define LE_SET	        GPIO_SetBits(GPIO_CTRB, GPIO_Pin_8)       //LE�ø�

#define DataPort        GPIOA                     								//PA��Ϊ���ݿ�

#define D0              GPIO_Pin_0             										//D0ʹ�õ�GPIO�ܽ�
#define D1              GPIO_Pin_1																//D1ʹ�õ�GPIO�ܽ�
#define D2              GPIO_Pin_2  															//D2ʹ�õ�GPIO�ܽ�
#define D3							GPIO_Pin_3																//D3ʹ�õ�GPIO�ܽ�
#define D4					    GPIO_Pin_4             										//D4ʹ�õ�GPIO�ܽ�
#define D5				      GPIO_Pin_5																//D5ʹ�õ�GPIO�ܽ�
#define D6				     	GPIO_Pin_6  															//D6ʹ�õ�GPIO�ܽ�
#define D7				     	GPIO_Pin_7																//D7ʹ�õ�GPIO�ܽ�


/*ȫ�ֱ���-��ɫ����*/

#define White          0xFFFF           													//��ʾ��ɫ����
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

/*����������*/
void RCC_Configuration(void);
void NVIC_Configuration(void);
void Delay(vu32 nCount);

