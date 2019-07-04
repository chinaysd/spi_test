/************************************************************************************
**                             ������ѧԺ ������Э��                             ****
**                                     �� ��                                     ****
**                              All Rights Reserved                              ****
************************************************************************************/

//���°汾2015.8.3
#include "main.h"


void BUS_16M(void)
{
	//�����ⲿ���پ�����1��Ƶ16MHz
	CLK_SWCR |= 0x02; //�����л�
	CLK_SWR = 0xb4;
	while((CLK_SWCR & 0x01) == 0x01);
	CLK_CKDIVR = 0x00; //1��Ƶ
	CLK_SWCR &= (~0x02); //�ر��л�
}

void Delay1ms(unsigned int time)
{
	unsigned int i,j;
	for (i=0; i<time; i++)
	{
		for (j=0; j<1000; j++)
		{
			_asm("nop");_asm("nop");
		}
	}
}

void Delay1us(unsigned int time)
{
	unsigned int i;
	for (i=0; i<time; i++)
	{
		_asm("nop");
	}
}