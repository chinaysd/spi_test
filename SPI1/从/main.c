/******************** 2011���ӿƼ�Э�� ********************
;���� ��SPIͨ��
;����   : ֣Ʒ��
;����   : 07/25/2011
;���� : ��SPI���豸����
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
    
    PC_DDR=0X8f;           //MISO���豸����ܽţ�MOSI���豸 ����
    PC_CR1=0X0f;
    PC_CR2=0X00;
    	
		PD_DDR=0x48;
		PD_CR1=0x28;
		PD_CR2=0x00; 

    PE_DDR=0x00;      //��SPI_NSS����Ϊ��������
		PE_CR1=0x20;
		PE_CR2=0x00;
}

void init_TIM2(void)
{
    TIM2_EGR=0X01;       //������������¼�
    TIM2_PSCR=0X00;     //����Ƶ��ʹƵ��Ϊ2MHz
        
    TIM2_ARRH=0X27;     //���º��������ֵ
    TIM2_ARRL=0X10;
        
    TIM2_CR1=0X05;      //����ʱ������
    TIM2_IER=0X01;     //��������ж�
        _asm("rim");       //�����䣬������ʱ��	
}


void SPI(void)
{ 
	SPI_CR1=0x10;                   //�ȷ���MSB���ر�SPI��������Ϊf/4������Ϊ���豸�����е͵�ƽ����һ��ʱ�ӱ�Ե��ʼ���ݲ���
	SPI_CR1|=0x40;                  //����SPI
	SPI_CR2=0x00;
	PD_DDR=0x48;
  PD_CR1=0x28;
	delay(1000);
	if((SPI_SR&0x01)==0x01)	//�жϽ������Ƿ�Ϊ�գ����ж��Ƿ���յ�����
  	
		{delay(1);
	   a=SPI_DR;
		 PD_DDR|=a;
		 PD_CR1|=a;
	  }
	delay(1000);
	//SPI_DR=00001000;
	while((SPI_SR|0x80)==0x80);    //�ȴ�ͨ�Ž���
	b=0x55;  	//�����ܵ�����ȡ�����͸����豸
	
	 
	SPI_DR=b;                     //��Ҫ���͵�b�ŵ�SPI_DR��
	delay(1000);                      //��ʱһ�ᣬ�ȴ��������
	while((SPI_SR|0x80)==0x80);    //�ȴ�ͨ�Ž��� 
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