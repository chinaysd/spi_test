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
	//������д������
	for(i=0;i<8;i++)
	{
		Data[i]=~(0x01<<i);
	}
	while (1)
	{
		if(dataIndex==8)
		{
		dataIndex=0;
		SPI_CR2|=0x10;//֪ͨSPI�ӿڷ����굱ǰ������һ�����ݺ���CRCУ��Ĵ����е�У����
		//break;
	}
		
		PB_ODR=Data[dataIndex];
		//�жϷ��ͻ������ǿ�ʱ�ȴ�
		while((SPI_SR&0x02)==0);
		//������д�뷢�ͻ�����
		SPI_DR=Data[dataIndex++];
		delay(50000);
	}
}