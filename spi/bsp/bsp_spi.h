#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_

#include "stm8s_conf.h"

#define Send_Buf_SIZE     7
#define Hight(x)          ((x>>8)&0xff)
#define Low(x)            ((x)&0xff)

#define RevBufSIZE        7
#define Get32Bit(x,y)     (((x<<8)&0xffff)|y)

typedef struct 
{
    unsigned char ID;
    unsigned char ADDR;
    unsigned char DATA1;
    unsigned char DATA2;
    unsigned char CHECKSUM;
    unsigned char STOP1;
    unsigned char STOP2;
}
DATA_FORMAT_t;


typedef union 
{
    unsigned char Buf[Send_Buf_SIZE];
    DATA_FORMAT_t Data_Format;
}
PROTOCOL_TX;










void Spi_Init(void);

void RevDataProcessHandle(void);
void RevDataHandle(void);

#endif




