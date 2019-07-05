#ifndef _BSP_SPI_H_
#define _BSP_SPI_H_

#include "stm8s_conf.h"


#define CS_PORT     GPIOA
#define CS_PIN      GPIO_PIN_3


#define RevBufSIZE        7
#define Get32Bit(x,y)     ((((x<<8)&0xffff)|y)&0xffff)









void Spi_Init(void);

void RevDataProcessHandle(void);
void RevDataHandle(void);

#endif




