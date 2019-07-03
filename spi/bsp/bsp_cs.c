#include "bsp_cs.h"




void Enable_CS(void)
{
    GPIO_Init(ENABLE_CS_PORT,ENABLE_CS_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    ENABLE_CS_SET(1);
}




void Disable_CS(void)
{
    GPIO_Init(ENABLE_CS_PORT,ENABLE_CS_PIN,GPIO_MODE_OUT_PP_HIGH_FAST);
    ENABLE_CS_SET(0);
}



