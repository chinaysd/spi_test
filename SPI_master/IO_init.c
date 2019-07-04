#include "main.h"


void IO_init(void)
{

	PB_DDR = 0xff;
	PB_CR1 = 0xff;
	PB_CR2 = 0x00;
	PB_ODR = 0xff;

}