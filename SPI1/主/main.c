/******************** 2011电子科技协会 ********************
;名称 ：SPI通信
;作者   : 郑品洪
;日期   : 07/25/2011
;描述 : ；利用SPI实现两单片机通信，需用杜邦线将两单片机的MOSI，MISO，SPI_CLK
           互相连接起来，另外将主机的P3^7（PE0）和从机的SPI_NSS连接起来，另外，开发板
				  93c46（即矩阵键盘旁边靠里的芯片）会影响SPI通信，使用时请把主机中的93c46
					拔去
;***********************************************************/
#include <stm8s105s4.h> 
#define uchar unsigned char 
#define uint unsigned int
_Bool MOSI @PC_ODR:6;
_Bool MISO @PC_ODR:7;
_Bool SPI_CLK @PC_ODR:5;
_Bool SPI_NSS @PE_ODR:0;
uchar table[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0x88,0x83,0xc6,0xa1,0x86,0x8e};
uchar a,t,b,n,c;
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
    
    PC_DDR=0X6f;        //MISO，主设备悬空输入，MOSI主设备推挽输出，SCL推挽输出
    PC_CR1=0X6f;
    PC_CR2=0X00;
    	
		PD_DDR=0x58;
		PD_CR1=0x38;
		PD_CR2=0x00; 

    PE_DDR=0x01;      //PE0为从设备控制引脚，NSS设为上拉输入
		PE_CR1=0x21;
		PE_CR2=0x00;
}

void init_TIM2(void)
{
    TIM2_EGR=0X01;       //允许产生更新事件
    TIM2_PSCR=0X00;     //不分频，使频率为2MHz
        
    TIM2_ARRH=0X27;     //更新后计数器的值，定时5ms
    TIM2_ARRL=0X10;
        
    TIM2_CR1=0X05;      //允许定时器工作
    TIM2_IER=0X01;      //允许更新中断
		_asm("rim");       //汇编语句，启动定时器	
}

void init_UART(void)
{
    UART2_BRR2 = 0x00;         // 波特率9600，分频系数=2000000/9600=208
	 UART2_BRR1 = 0x0d;              // 对应的十六进制数为00D0，BBR1=0D,BBR2=00
   UART2_CR2 = 0x2C;         // b3 = 1,允许发送    b2 = 1,允许接收    b5 = 1,允许产生接收中断 
}

void SPI(void)
{
	SPI_CR1=0x14;                     //先发送MSB，关闭SPI，波特率f/4 ，配置为主设备，空闲低电平，第一个时钟边缘开始数据采样
	SPI_NSS=0;                       //开启从设备接收
	SPI_CR1|=0x40;                   //开启SPI
	SPI_CR2=0x00; 	//双向数据模式
	a=0x18;
	PD_DDR|=a;
    PD_CR1|=a;
		delay(1000);
	SPI_DR=a;                   	//将要发送的a放到SPI_DR中
	delay(1);                      //延时一会等待数据发送完毕
	while((SPI_SR|0x80)==0x80);    //等待通信结束
	if((SPI_SR&0x01)==0x01)         //判断接受区是否为空，即判断是否接收到数据
	{c=SPI_DR;
   if(c==0x55) 
   PD_DDR=0x48;
    PD_CR1=0x28;
	 
	}                    //将接受到从设备发送的数据赋值给b
	delay(1000);                       //延时一会等待数据赋值完成
	while((SPI_SR|0x80)==0x80);    //等待通信结束
	SPI_NSS=1;                    //关闭从设备接收
	SPI_CR1|=0xbf;                //关闭SPI 
	delay(1); 
}

void display(void)
{
	H=b/16;
	L=b%16; 
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
	init_UART();
	init_TIM2();

    while(1)
  {
    SPI();
		display();
	}
}

 @far @interrupt void UART2_Receiver(void)
{
  while((UART2_SR & 0x80) == 0x00);    // 等待数据转移到移位寄存器
  a=UART2_DR;                         // 将接收到的字符放到a中
}


@far @interrupt void TIM2_UP_IRQHandler (void)         

{
   TIM2_SR1 = 0x00; 
     t++;
}