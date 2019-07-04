#include "system.h"
#include "stddef.h"


unsigned char RevReadTempData;

void System_Init(void)
{
    Spi_Init();
    Led_Init();
    Enable_CS();
}

#if 0
uint8_t spi_read()
{
    //选择一个无效数据发送(自定义，只是为了给从设备提供时钟)，然后读取到对应数据
    uint8_t data = 0xff;
    while (SPI_GetFlagStatus(SPI_FLAG_TXE) == RESET);
    SPI_SendData(data);
    while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
    uint8_t rxdata  = SPI_ReceiveData();
    return rxdata;
}
#endif
 
void System_Handle(void)
{
    #if 0
    RevReadTempData = spi_read();
    if(RevReadTempData == 0x01){
       LED_SET(1);
    }  
    #endif
    RevDataProcessHandle();
    RevDataHandle();
}





