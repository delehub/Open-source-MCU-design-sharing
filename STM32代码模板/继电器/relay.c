
#include "Relay.h"


/*******************************************************************************
** ��������: jdq_init
** ��������: 
** ����˵��: None
** ����˵��: None
** ������Ա: temp_duan
** ��������: 2019-07-09
**------------------------------------------------------------------------------
** �޸���Ա:
** �޸�����:
** �޸�����:
**------------------------------------------------------------------------------
********************************************************************************/
void Relay_init(void)
{

    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);//ʹ��PB,PE�˿�ʱ��

    GPIO_InitStructure.GPIO_Pin    =  GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Mode   =  GPIO_Mode_Out_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed  =  GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��


    Relay_OFF;

}

