/******************** 2011电子科技协会 ********************
;名称 ：SPI通信
;作者   : 郑品洪
;日期   : 07/25/2011
;描述 : ；SPI从设备程序
;***********************************************************/
#include <stm8s105s4.h> 
#define uchar unsigned char 
#define uint unsigned int
_Bool MOSI @PC_ODR:6;
_Bool MISO @PC_ODR:7;
_Bool SPI_CLK @PC_ODR:5;
_Bool SPI_NSS @PE_ODR:5;
uchar table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
uchar a,b,t,n;
uchar H,L;
void delay(uint s)
{
 uchar i;
 for(s;s>0;s--)
   for(i=0;i<100;i++);
}

void init_IO(void)
{
    PB_DDR=0XFF;
    PB_CR1=0XFF;
    PB_CR2=0X00;
    
    PC_DDR=0X8f;           //MISO从设备输出管脚，MOSI从设备 输入
    PC_CR1=0X0f;
    PC_CR2=0X00;
    	
		PD_DDR=0x48;
		PD_CR1=0x28;
		PD_CR2=0x00; 

    PE_DDR=0x00;      //将SPI_NSS配置为上拉输入
		PE_CR1=0x20;
		PE_CR2=0x00;
}

void init_TIM2(void)
{
    TIM2_EGR=0X01;       //允许产生更新事件
    TIM2_PSCR=0X00;     //不分频，使频率为2MHz
        
    TIM2_ARRH=0X27;     //更新后计数器的值
    TIM2_ARRL=0X10;
        
    TIM2_CR1=0X05;      //允许定时器工作
    TIM2_IER=0X01;     //允许更新中断
        _asm("rim");       //汇编语句，启动定时器	
}


void SPI(void)
{ 
	SPI_CR1=0x10;                   //先发送MSB，关闭SPI，波特率为f/4，配置为从设备，空闲低电平，第一个时钟边缘开始数据采样
	SPI_CR1|=0x40;                  //开启SPI
	SPI_CR2=0x00;
	PD_DDR=0x48;
  PD_CR1=0x28;
	delay(1000);
	if((SPI_SR&0x01)==0x01)	//判断接收区是否为空，即判断是否接收到数据
  	
		{delay(1);
	   a=SPI_DR;
		 PD_DDR|=a;
		 PD_CR1|=a;
	  }
	delay(1000);
	//SPI_DR=00001000;
	while((SPI_SR|0x80)==0x80);    //等待通信结束
	b=0x55;  	//将接受到的数取反后发送给主设备
	
	 
	SPI_DR=b;                     //将要发送的b放到SPI_DR中
	delay(1000);                      //延时一会，等待发送完毕
	while((SPI_SR|0x80)==0x80);    //等待通信结束 
	delay(1);
}

void display(void)
{
	H=a/16;
	L=a%16; 
	if((t%2)==0)
	{
    PC_ODR=0x02;	
    PB_ODR=table[H];	
	}
    
	if((t%2)!=0)
	{
    PC_ODR=0x00;	
    PB_ODR=table[L];	
	} 
}

void main()
{
	init_IO();
	init_TIM2();
    while(1)
  {
    SPI();
		display();
	}
}

@far @interrupt void TIM2_UP_IRQHandler (void)         

{
   TIM2_SR1 = 0x00; 
     t++;
}