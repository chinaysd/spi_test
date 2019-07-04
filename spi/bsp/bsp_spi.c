#include "bsp_spi.h"
#include "string.h"
#include "bsp_led.h"

unsigned char Rev_Num,Rev_Data,Rev_String[RevBufSIZE];



#if 1
void Spi_Init(void)
{
    SPI_DeInit();
 
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_OUT_PP_LOW_FAST);
 
    GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_IN_PU_NO_IT);
 
    GPIO_Init(GPIOC,GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
 
    SPI_Init(SPI_FIRSTBIT_MSB,SPI_BAUDRATEPRESCALER_2,\
             SPI_MODE_SLAVE, SPI_CLOCKPOLARITY_LOW,\
             SPI_CLOCKPHASE_1EDGE,\
             SPI_DATADIRECTION_2LINES_FULLDUPLEX,\
             SPI_NSS_SOFT,7);
 
    SPI_Cmd(ENABLE);

}

/********************************************************接收部分*************************************************/


static unsigned char Spi_RevByte(void)
{
    static unsigned char byte;
    while(SPI_GetFlagStatus(SPI_FLAG_RXNE)==RESET);
    byte=SPI_ReceiveData();
    return byte;
}

static unsigned char IFComplete(void)
{
    if(Rev_Num & 0x80){
       Rev_Num = 0x00;
       return 1;
    }else{
        return 0;
    }
}

void RevDataProcessHandle(void)
{
    Rev_Data = Spi_RevByte();
    if((Rev_Num & 0x80) == 0){
        if(Rev_Num == 0x40){
           if(Rev_Data == 0x0a){
              Rev_Num = 0x80;
           }else{
              Rev_Num = 0x00;
           }
        }else{
           if(Rev_Data == 0x0d){
              Rev_Num = 0x40;
           }else{
              Rev_String[Rev_Num] = Rev_Data;
              Rev_Num ++;
              if(Rev_String[0] != 0xfa){
                 Rev_Num = 0x00;
              }
              if(Rev_Num > RevBufSIZE){
                 Rev_Num = 0x00;
              }
           }
        }
    }
}

void RevDataHandle(void)
{
    static unsigned int RevTempData;
    if(IFComplete()){
       RevTempData = Get32Bit(Rev_String[2],Rev_String[3]);
       memset(&Rev_String,0,sizeof(Rev_String));
    }
    switch (RevTempData)
    {
       case 0x1101:
            LED_SET(1); 
       break;
       case 0x1102:
            LED_SET(0); 
       break;
       case 0x1104:

       break;
       case 0x1108:

       break;
       default:

       break; 
    }
}




#else


 
/*以下设置为符合我三轴传感器对应配置*/
#define SPI_FIRSTBIT_TYPE       SPI_FirstBit_MSB
#define SPI_SPEED_PRESC         SPI_BaudRatePrescaler_4
#define SPI_MODE                SPI_Mode_Master
#define SPI_CPOL                SPI_CPOL_Low
#define SPI_CPHA                SPI_CPHA_1Edge
#define SPI_DATA_MODE           SPI_Direction_2Lines_FullDuplex
#define SPI_CS_CTRL             SPI_NSS_Soft


void Spi_Init(void){
//开启SPI外设时钟
  CLK_PeripheralClockConfig(CLK_Peripheral_SPI, ENABLE);
  //SPI重置
  SPI_DeInit();
  //SPI相关GPIO初始化
    GPIO_Init(GPIOC, GPIO_PIN_7, GPIO_MODE_IN_PU_NO_IT);

    GPIO_Init(GPIOC, GPIO_PIN_6, GPIO_MODE_OUT_PP_LOW_FAST);

    GPIO_Init(GPIOC,GPIO_PIN_5, GPIO_MODE_OUT_PP_LOW_FAST);
  //SPI初始化
  SPI_Init(SPI_FIRSTBIT_TYPE, SPI_SPEED_PRESC, SPI_MODE, SPI_CPOL, SPI_CPHA,           
  SPI_DATA_MODE, SPI_CS_CTRL);
  //SPI启动
  SPI_Cmd(ENABLE);
}

/*此部分为写入读取数据部分代码，在读取写入数据前后要记得打开及关闭片选信号*/
 
static void spi_write(uint8_t data)
{
    while(SPI_GetFlagStatus(SPI_FLAG_TXE) == RESET);
    SPI_SendData(data);
    //一定不可省略不写，若不接收对应数据，马上去读数据就会造成读到的数据不对。
    while (SPI_GetFlagStatus(SPI_FLAG_RXNE) == RESET);
    u8 dd = SPI_ReceiveData();
}
 
static uint8_t spi_read()
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






#endif



