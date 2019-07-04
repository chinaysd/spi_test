#include "system.h"




void System_Init(void)
{
     Spi_Init();
}

void System_Handle(void)
{
    Protocol_Send(0xfa,0xfb,0x1101);
}
