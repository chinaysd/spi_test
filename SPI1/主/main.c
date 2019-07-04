/******************** 2011���ӿƼ�Э�� ********************
;���� ��SPIͨ��
;����   : ֣Ʒ��
;����   : 07/25/2011
;���� : ������SPIʵ������Ƭ��ͨ�ţ����öŰ��߽�����Ƭ����MOSI��MISO��SPI_CLK
           �����������������⽫������P3^7��PE0���ʹӻ���SPI_NSS�������������⣬������
				  93c46������������Ա߿����оƬ����Ӱ��SPIͨ�ţ�ʹ��ʱ��������е�93c46
					��ȥ
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
    
    PC_DDR=0X6f;        //MISO�����豸�������룬MOSI���豸���������SCL�������
    PC_CR1=0X6f;
    PC_CR2=0X00;
    	
		PD_DDR=0x58;
		PD_CR1=0x38;
		PD_CR2=0x00; 

    PE_DDR=0x01;      //PE0Ϊ���豸�������ţ�NSS��Ϊ��������
		PE_CR1=0x21;
		PE_CR2=0x00;
}

void init_TIM2(void)
{
    TIM2_EGR=0X01;       //������������¼�
    TIM2_PSCR=0X00;     //����Ƶ��ʹƵ��Ϊ2MHz
        
    TIM2_ARRH=0X27;     //���º��������ֵ����ʱ5ms
    TIM2_ARRL=0X10;
        
    TIM2_CR1=0X05;      //����ʱ������
    TIM2_IER=0X01;      //��������ж�
		_asm("rim");       //�����䣬������ʱ��	
}

void init_UART(void)
{
    UART2_BRR2 = 0x00;         // ������9600����Ƶϵ��=2000000/9600=208
	 UART2_BRR1 = 0x0d;              // ��Ӧ��ʮ��������Ϊ00D0��BBR1=0D,BBR2=00
   UART2_CR2 = 0x2C;         // b3 = 1,������    b2 = 1,�������    b5 = 1,������������ж� 
}

void SPI(void)
{
	SPI_CR1=0x14;                     //�ȷ���MSB���ر�SPI��������f/4 ������Ϊ���豸�����е͵�ƽ����һ��ʱ�ӱ�Ե��ʼ���ݲ���
	SPI_NSS=0;                       //�������豸����
	SPI_CR1|=0x40;                   //����SPI
	SPI_CR2=0x00; 	//˫������ģʽ
	a=0x18;
	PD_DDR|=a;
    PD_CR1|=a;
		delay(1000);
	SPI_DR=a;                   	//��Ҫ���͵�a�ŵ�SPI_DR��
	delay(1);                      //��ʱһ��ȴ����ݷ������
	while((SPI_SR|0x80)==0x80);    //�ȴ�ͨ�Ž���
	if((SPI_SR&0x01)==0x01)         //�жϽ������Ƿ�Ϊ�գ����ж��Ƿ���յ�����
	{c=SPI_DR;
   if(c==0x55) 
   PD_DDR=0x48;
    PD_CR1=0x28;
	 
	}                    //�����ܵ����豸���͵����ݸ�ֵ��b
	delay(1000);                       //��ʱһ��ȴ����ݸ�ֵ���
	while((SPI_SR|0x80)==0x80);    //�ȴ�ͨ�Ž���
	SPI_NSS=1;                    //�رմ��豸����
	SPI_CR1|=0xbf;                //�ر�SPI 
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
  while((UART2_SR & 0x80) == 0x00);    // �ȴ�����ת�Ƶ���λ�Ĵ���
  a=UART2_DR;                         // �����յ����ַ��ŵ�a��
}


@far @interrupt void TIM2_UP_IRQHandler (void)         

{
   TIM2_SR1 = 0x00; 
     t++;
}