#include "system.h"

uint8_t WriteString[4],ReadString[4];


void System_Init(void)
{
    Spi_Init();
    Led_Init();
    //Enable_CS();
    enableInterrupts();
}

void System_Handle(void)
{
    #if 1
    //Protocol_Send(0xfa,0xfb,0x0102);
    RevDataProcessHandle();
    RevDataHandle();
    #else
    spi_write2read(&WriteString[1],2,&ReadString[1],2);
    #endif  

    #if 0  
    static unsigned char Cnts;
    ++ Cnts;
    if(Cnts & 0x01){
       LED_SET(1); 
    }else{
       LED_SET(0);
    }
    #endif
}





