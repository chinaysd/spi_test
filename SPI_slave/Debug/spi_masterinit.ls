   1                     ; C Compiler for STM8 (COSMIC Software)
   2                     ; Parser V4.8.32 - 23 Mar 2010
   3                     ; Generator V4.3.4 - 23 Mar 2010
5147                     ; 11 void SPI_MasterInit(void)
5147                     ; 12 {
5149                     	switch	.text
5150  0000               _SPI_MasterInit:
5154                     ; 13 	PC_DDR|=(1<<5)|(1<<6);
5156  0000 c6500c        	ld	a,_PC_DDR
5157  0003 aa60          	or	a,#96
5158  0005 c7500c        	ld	_PC_DDR,a
5159                     ; 14 	PC_CR1|=(1<<5)|(1<<6)|(1<<7);
5161  0008 c6500d        	ld	a,_PC_CR1
5162  000b aae0          	or	a,#224
5163  000d c7500d        	ld	_PC_CR1,a
5164                     ; 15 	SPI_CR1=0x0c;
5166  0010 350c5200      	mov	_SPI_CR1,#12
5167                     ; 16 	SPI_CR2=0x03;
5169  0014 35035201      	mov	_SPI_CR2,#3
5170                     ; 17 	SPI_CR1|=0x04;
5172  0018 72145200      	bset	_SPI_CR1,#2
5173                     ; 18 }
5176  001c 81            	ret
5189                     	xdef	_SPI_MasterInit
5208                     	end
