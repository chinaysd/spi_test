#include "main.h"


void IO_init(void)
{

	PB_DDR = 0xff;
	PB_CR1 = 0xff;
	PB_CR2 = 0x00;
	PB_ODR = 0xff;
	
	PD_DDR = 0xff;
	PD_CR1 = 0xff;
	PD_CR2 = 0x00;
	PD_ODR = 0xff;

}