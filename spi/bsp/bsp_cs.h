#ifndef _BSP_CS_H_
#define _BSP_CS_H_

#include "stm8s_conf.h"



#define ENABLE_CS_PORT    GPIOA
#define ENABLE_CS_PIN     GPIO_PIN_3
#define ENABLE_CS_SET(X)  ((X)?(GPIO_WriteHigh(ENABLE_CS_PORT,ENABLE_CS_PIN)):(GPIO_WriteLow(ENABLE_CS_PORT,ENABLE_CS_PIN)))





void Enable_CS(void);
void Disable_CS(void);



#endif


