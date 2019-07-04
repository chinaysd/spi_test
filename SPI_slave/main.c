/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include "main.h"
uchar Data[8],dataIndex=0;checkFlag=0;
main()
{
	uchar i;
	IO_init();
	//BUS_16M();
	SPI_SlaveInit();
  _asm("rim");//打开总中断，sim为关闭总中断
	while(dataIndex!=8);
	for(i=0;i<8;i++)
{
	if(Data[i]!=~(0x01<<i))
{
	checkFlag++;
}
}
	while (1)
	{
		PD_ODR=~(0x01<<checkFlag);
		
	}
}



@far @interrupt void SPI(void)
{
	//SPI_DR=0xff;//查询用到，写入无效数据以开启SPI传送
/*判断接收缓冲器非空标志位RXNE是否为1*/
	if((SPI_SR&0x01)!=0)
	{
		
	  
	 Data[dataIndex]=SPI_DR;
	 PB_ODR=Data[dataIndex++];
	 if(dataIndex==8)
	 {
		 SPI_CR2|=10;
		dataIndex=0;
   }
	
	}
	if((SPI_SR&0x10)!=0)
	{
		while(1)
	{
		PD_ODR=0xaa;
	}
  }
}