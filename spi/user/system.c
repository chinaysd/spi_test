#include "system.h"
#include "stddef.h"

uint8_t WriteString[4]={0XFA,0XFB,0X01,0X0A},ReadString[4]={0};

unsigned char RevReadTempData;

void System_Init(void)
{
    Spi_Init();
    Led_Init();
    Enable_CS();
}

void Delay_MS(unsigned int Time)
{
    static unsigned int i,j;
    for(i = Time; i > 0 ; i--)
    {
        for(j = 200; j > 0 ; j --);
    }
}
#if 0
u8 spi_rw(u8 byte)
{
    ENABLE_CS_SET(0);
    while(SPI_GetFlagStatus(SPI_FLAG_TXE)==RESET);
 
    SPI_SendData(byte);
    Delay_MS(1000);
    while(SPI_GetFlagStatus(SPI_FLAG_RXNE)==RESET);
 
    byte=SPI_ReceiveData();
    Delay_MS(1000);
    while(SPI_GetFlagStatus(SPI_FLAG_RXNE)==RESET);
    Delay_MS(10);
    ENABLE_CS_SET(1);
    return byte;
}
#else
u8 spi_rw(u8 byte)
{
    ENABLE_CS_SET(0);
    while(SPI_GetFlagStatus(SPI_FLAG_TXE)==RESET);
 
    SPI_SendData(byte);

    while(SPI_GetFlagStatus(SPI_FLAG_RXNE)==RESET);
 
    byte=SPI_ReceiveData();
    ENABLE_CS_SET(1);
    return byte;
}
#endif





/*此部分为写入读取数据部分代码，在读取写入数据前后要记得打开及关闭片选信号*/
 
void spi_write(uint8_t data)
{
    while(SPI_GetFlagStatus(SPI_FLAG_TXE) == RESET);
    SPI_SendData(data);
    //一定不可省略不写，若不接收对应数据，马上去读数据就会造成读到的数据不对。
    while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
    u8 dd = SPI_ReceiveData();
}
 
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
 
//写入数据并读取需要的数据
void spi_write2read(uint8_t *wdata, uint8_t wlen, uint8_t *rdata, uint8_t rlen)
{
    uint8_t i;
    if (wdata == NULL || rdata == NULL) {
        return;
    }
    //写数据
    for (i = 0; i < wlen; i++) {
        spi_write(wdata[i]);
    }
    //读数据
    for (i = 0; i < rlen; i++) {
        rdata[i] = spi_read();
    }
}





void System_Handle(void)
{
    #if 1
    //Protocol_Send(0xfa,0xfb,0x0102);
    //RevDataProcessHandle();
    //RevDataHandle();
    //spi_write2read(&WriteString[1],4,&ReadString[1],4);
    #if 1
    RevReadTempData = spi_read();
    if(RevReadTempData == 0x01){
       LED_SET(1);
    }
    #else
    spi_rw(0x01);
    #endif
    #if 0
    RevReadTempData = spi_rw(0x55);
    if(RevReadTempData == 0x55){
       LED_SET(1);
    }
    #endif
    //spi_rw(0x55);
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





