/* MAIN.C file
 * 
 * Copyright (c) 2002-2005 STMicroelectronics
 */

#include "main.h"
uchar Data[8],dataIndex=0;
main()
{
	uchar i;
	IO_init();
	//BUS_16M();
	SPI_MasterInit();
	//将数组写入数组
	for(i=0;i<8;i++)
	{
		Data[i]=~(0x01<<i);
	}
	while (1)
	{
		if(dataIndex==8)
		{
		dataIndex=0;
		SPI_CR2|=0x10;//通知SPI接口发送完当前这个最后一个数据后发送CRC校验寄存器中的校验码
		//break;
	}
		
		PB_ODR=Data[dataIndex];
		//判断发送缓冲区非空时等待
		while((SPI_SR&0x02)==0);
		//将数据写入发送缓冲区
		SPI_DR=Data[dataIndex++];
		delay(50000);
	}
}