/************************************************************************************
**                             淮阴工学院 机器人协会                             ****
**                                     大 胡                                     ****
**                              All Rights Reserved                              ****
************************************************************************************/

//最新版本2015.8.3
#include "main.h"


void BUS_16M(void)
{
	//启用外部高速晶振且1分频16MHz
	CLK_SWCR |= 0x02; //开启切换
	CLK_SWR = 0xb4;
	while((CLK_SWCR & 0x01) == 0x01);
	CLK_CKDIVR = 0x00; //1分频
	CLK_SWCR &= (~0x02); //关闭切换
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